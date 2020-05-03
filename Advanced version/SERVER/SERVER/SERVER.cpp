#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <map>
#include <string>
#include <ctime>
#pragma warning(disable: 4996)
SOCKET Connections[100];
int Counter = 0;
std::map <  std::string, std::string > def = { {"Standard","-sample, standard, model, taken as the source for comparison with other similar objects."},
	{"Standardization","-this is the establishment and application of rules with the aim of streamlining activities in a certain area for the benefit and with the participation of all interested parties."},
	{"Validity","-the validity and suitability of applying the methods and results of the study in specific conditions." }};
void ClientHandler(int index) {
	int msg_size;
	while (true) {
		recv(Connections[index], (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connections[index], msg, msg_size, NULL);
		
		msg_size = def[msg].size() + 1;
			send(Connections[index], (char*)&msg_size, sizeof(def[msg].size() + 1), NULL);
			send(Connections[index], def[msg].c_str(), msg_size, NULL);
			
		
		delete[] msg;
	}
}
int main(int argc, char* argv[]) {
	time_t t;
	t = time(0);
	std::cout << "Burdyak Yuriy SP-841" << std::endl;
	std::cout << puts(ctime(&t));
	//WSAStartup
	
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);
	SOCKET newConnection;
	for (int i = 0; i < 100; i++) {
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
		if (newConnection == 0) {
			std::cout << "Error #2\n";
		}
		else {
			std::cout << "Client Connected!\n";
			
			std::string msg = "Hello. It`s my first network program!";
			int msg_size = msg.size();
			send(newConnection, (char*)&msg_size, sizeof(int), NULL);
			send(newConnection, msg.c_str(), msg_size, NULL);
			Connections[i] = newConnection;
			
				Counter++;
			CreateThread(NULL, NULL,
				(LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
		}
	}
	system("pause");
	return 0;
}