#ifndef _NET_SERVER_H
#define _NET_SERVER_H

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <stdlib.h>
#include <string>

#include "net_data.h"
#include "logout.h"

#define BUFFER_SIZE				1024*2
#define LENGTH_OF_LISTEN_QUEUE		20

using namespace std;

class NetServer {
public:
	NetServer(int listen_port) {
		/*
		initial server address
		*/
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = htons(INADDR_ANY);
		server_addr.sin_port = htons(listen_port);
		logOut = new LogOut("NetServer");
		listenPort = listen_port;
	}

	void startListen() {
		/*
		create server_socket
		*/
		server_socket = socket(PF_INET, SOCK_STREAM, 0);
		if (server_socket < 0) {
			logOut->info("Create Socket Failed!");
			exit(1);
		}

		if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr))) {
			logOut->info("Server Bind Port Failed!");
			exit(1);
		}

		if (listen(server_socket, LENGTH_OF_LISTEN_QUEUE)) {
			logOut->info("Server Listen Failed!");
			exit(1);
		}

		/*
		start listen
		busy wait for listen
		*/
		
		
		logOut->info("server start at port " + to_string(listenPort));

		while(true) {
			struct sockaddr_in client_addr;
			socklen_t length = sizeof(client_addr);
			int new_server_socket = accept(server_socket, (struct sockaddr*)&client_addr, &length);
			char buffer[BUFFER_SIZE];
			NetData netData;

			if (new_server_socket < 0){
				logOut->info("Server Accept Failed!");
				continue;
			}

			logOut->info("accept " + string(inet_ntoa(client_addr.sin_addr)));

			length = recv(new_server_socket, buffer, BUFFER_SIZE, 0);

			if (length < 0){
				logOut->info("Server Receive Data Failed!");
				continue;
			}

			string tmp(buffer, buffer + length);
			net::PageRequest pageRequest = netData.PageRequestParseFromString(tmp);

			logOut->info("request id:" + to_string(pageRequest.request_id()));

			net::PageResult pageResult = netData.getRequestResult(pageRequest);

			string response;
			netData.PageResultSerialize2String(pageResult, response);

			if (sendByNet(new_server_socket, response.c_str(), response.length()) < 0){
				logOut->info("Send Client Failed!");
				continue;
			}

			logOut->info("close " + string(inet_ntoa(client_addr.sin_addr)));

			close(new_server_socket);
		}

		close(server_socket);
	}

private:
	struct sockaddr_in server_addr;
	int server_socket;
	int listenPort;
	LogOut *logOut;

	int sendByNet(int socket, const char *buffer, int length) {
		int total = 0;
		int bytesleft = length;
		int n;

		while(total < length) {
			n = send(socket, buffer + total, bytesleft, 0);
			if (n == -1)
				break;
			total += n;
			bytesleft -= n;
		}

		return n == -1 ? -1 : 0;
	}

	string to_string(int msg) {
		char buffer[1024];
		sprintf(buffer, "%d", msg);
		return string(buffer);
	}

};

#endif