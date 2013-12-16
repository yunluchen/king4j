#ifndef _NET_CLIENT_H
#define _NET_CLIENT_H

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

using namespace std;

class NetClient {
public:
	NetClient(string server_ip, int server_port) {
		/*
		initial client address
		*/
		client_addr.sin_family = AF_INET;
		client_addr.sin_addr.s_addr = htons(INADDR_ANY);
		client_addr.sin_port = htons(0);

		/*
		initial server address
		*/
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = inet_addr(server_ip.c_str());
		server_addr.sin_port = htons(server_port);

		logOut = new LogOut("NetClient");
	}

	net::PageResult sendPageRequest(net::PageRequest &pageRequest) {
		client_socket = socket(AF_INET, SOCK_STREAM, 0);
		if(client_socket < 0) {
			logOut->info("Create Socket Failed!");
			exit(1);
		}

		if(bind(client_socket, (struct sockaddr*)&client_addr, sizeof(client_addr))) {
			logOut->info("Client Bind Port Failed!");
			exit(1);
		}

		socklen_t server_addr_length = sizeof(server_addr);
		if(connect(client_socket, (struct sockaddr*)&server_addr, server_addr_length) < 0) {
			logOut->info("Can Not Connect To Server!");
			exit(1);
		}

		string buffer;
		pageRequest.SerializeToString(&buffer);
		if (sendByNet(client_socket, buffer.c_str(), buffer.length()) < 0) {
			logOut->info("Send Failed!");
			exit(1);
		}

		char receive[BUFFER_SIZE];
		net::PageResult pageResult;
		int length = recv(client_socket, receive, BUFFER_SIZE, 0);
		string tmp(receive, receive + length);
		pageResult.ParseFromString(tmp);
		return pageResult;
	}

private:
	struct sockaddr_in client_addr;
	int client_socket;
	struct sockaddr_in server_addr;
	LogOut* logOut;

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
	
};

#endif