#include <iostream>

#include "net_server.h"

using namespace std;

int main(int argc, char **argv) {

	NetServer netServer(33477);
	netServer.startListen();

	return 0;
}
