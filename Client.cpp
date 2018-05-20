#include "VersatileSocket.h"
#include <iostream>
#include <string>
#include <thread>
using namespace std;

void communication(TCPSocket socket) 
{
	cout << "Client receive" << endl;
	while (true) {
		string str = socket.receive(socket.getSockfd());
		cout << str << endl;
	}
}

int main() {
	cout << "Client" << endl;
	TCPSocket socket("127.0.0.1", 9000);
	socket.connect();
	string message;
	std::thread t1(communication, socket);
	while(true)
	{
		//cin >> message;
		std::getline(std::cin, message);
		socket.send(socket.getSockfd(), message);
	}
	return 0;
}	