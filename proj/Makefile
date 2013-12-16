.PHONY:	all	client server clean

all: client server

client: test_net_client.cpp net_client.h net_data.h netmessage.pb.h logout.h netmessage.pb.cc
	g++ -o test_client test_net_client.cpp net_client.h net_data.h netmessage.pb.h logout.h netmessage.pb.cc -lpthread -lprotobuf -I/usr/protobuf/include -L/usr/protobuf/lib

server: test_net_server.cpp net_server.h net_data.h netmessage.pb.h logout.h netmessage.pb.cc
	g++ -o test_server test_net_server.cpp net_server.h net_data.h netmessage.pb.h logout.h netmessage.pb.cc -lpthread -lprotobuf -I/usr/protobuf/include -L/usr/protobuf/lib

clean:
	rm -f test_server
	rm -f test_client
	rm -f *~
