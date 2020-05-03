#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#pragma warning(disable: 4996)
SOCKET Connections[100];
int Counter = 0;

struct RenctangleArea {
	int rencWeight;
	int rencHeight;
};

void ClientHandler(int index) {
	int msg_size;
	RenctangleArea renctangle;
	while (true) {
		recv(Connections[index], (char*)&renctangle, sizeof(RenctangleArea), NULL);
		int area  = renctangle.rencWeight * renctangle.rencHeight;

		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << area;

		std::string str = "Площадь прямоугольника: " + stream.str();
		
		int msg_size = strlen(str.c_str());
		send(Connections[index], (char*)&msg_size, sizeof(int), NULL);
		send(Connections[index], str.c_str(), msg_size, NULL);

	}
}
int main(int argc, char* argv[]) {
	time_t t;
	t = time(0);
	std::cout << "Burdyak Andrey SP-841" << std::endl;
	std::cout << puts(ctime(&t));
	setlocale(LC_ALL, "ru");
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
			
			std::string msg = " ";
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