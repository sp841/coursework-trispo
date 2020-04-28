#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
using namespace std;
#pragma warning(disable: 4996);
SOCKET Connections[100];
int Counter = 0;
void ClientHandler(int index) {
	int choice;
	while (true) {

		recv(Connections[index], (char*)&choice, sizeof(int), NULL);
		char definitions[3][100] = { "std is standard language library", "developer is a person who develops a software", "int is a type of variable" };
		send(Connections[index], definitions[choice], sizeof(definitions[choice]), NULL);

	}
}
int main(int argc, char* argv[]) {
	
	cout << "developer: Vashkevich Veronika, today is 27 of April, 2020\n";

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

			Connections[i] = newConnection;
			Counter++;
			CreateThread(NULL, NULL,
				(LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
		}
	}
	system("pause");
	return 0;
}
