#include <iostream>

#include "net_client.h"

using namespace std;

int main(int argc, char **argv) {
	cout << "test of client" << endl;

	NetClient netClient("211.101.18.110", 33477);
	NetData netData;

	net::PageRequest pageRequest;
	pageRequest.set_request_id(3);
	pageRequest.set_user_id(90);

	net::PageResult pageResult = netClient.sendPageRequest(pageRequest);

	cout << "nutrition_size:" << pageResult.nutrition_result().nutrition_size() << endl;
	cout << "recomment_size:" << pageResult.nutrition_result().recommend_size() << endl;
	
	return 0;
}
