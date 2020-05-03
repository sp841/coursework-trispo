#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include <ctime>
#pragma warning(disable: 4996)
SOCKET Connection;
void ClientHandler() {
	int msg_size;
	while (true) {
		recv(Connection, (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connection, msg, msg_size, NULL);
		std::cout << msg << std::endl;
		delete[] msg;
		
	}
}

struct RenctangleArea {
	int rencWeight;
	int rencHeight;
};

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
	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		return 1;
	}
	std::cout << "Andrey Burdyak SP-841 connected to the network!\n";
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL,
		NULL, NULL);
	std::string msg1;
	while (true) {
		std::cout << "\nВычисление площади прямоугольника \n";

		RenctangleArea renctangle;

		std::cout << "Ввод ширины прямоугольника: ";
		std::getline(std::cin, msg1);
		renctangle.rencWeight = std::stof(msg1);

		std::cout << "Ввод высоты прямоугольника: ";
		std::getline(std::cin, msg1);
		renctangle.rencHeight = std::stoi(msg1);

		std::cout << "\n";

		send(Connection, (char*)&renctangle, sizeof(renctangle), NULL);
		Sleep(10);
	}
	system("pause");
	return 0;
}