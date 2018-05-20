#include "VersatileSocket.h"
#include <iostream>
#include <string>
#include <thread>

void communication(TCPSocket &socket, SOCKET client)
{
	std::cout << "Thread Created!!" << std::endl;
	socket.sendToAll(-1, std::to_string(client) + " entered in chatting room");
	while (true) 
	{
		std::string str = socket.receive(client);
		std::cout << client << ": " << str << std::endl;
		if (str == "FAIL") 
		{
			std::cout << "Client: " << client << " disconnected" << std::endl;
			if (!socket.removeClient(client)) 
			{
				std::cout << "Removing client failed";
			}
			//socket.showClient();
			socket.sendToAll(0, std::to_string(client)+" disconnected from chatting room");
			break;
		}
		if (!socket.sendToAll(client, str)) 
		{
			std::cout << "Send failed" << std::endl;
		}
	}
}

int main() 
{
	std::cout << "Server" << std::endl;
	TCPSocket socket("127.0.0.1", 9000);
	socket.bind();
	socket.listen();

	int new_sock[MAX_CONN];
	std::thread th[MAX_CONN];
	int num_client = 0;
	while ((new_sock[num_client] = socket.accept()) != -1)
	{	
		th[num_client] = std::thread(communication, std::ref(socket), new_sock[num_client]);
		num_client++;
	}
}