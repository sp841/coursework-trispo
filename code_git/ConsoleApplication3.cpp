#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
using namespace std;
#pragma warning(disable: 4996)
SOCKET Connection;
int choice;
void ClientHandler() {
	while (true) {

		char definitions[100];
		recv(Connection, definitions, sizeof(definitions), NULL);
		cout << definitions << endl;

	}
}
int main(int argc, char* argv[]) {
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
	std::cout << "Connected!\n";
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL,
		NULL, NULL);

	cout << "enter the number of a defenition" << endl;
	cout << "1 - trispo; 2 - developer; 3 - tester" << endl;

	while (true) {

		cin >> choice;
		while (choice < 0 || choice>3) {
			cout << "no, enter again\n";
			cin >> choice;
		}
		choice--;
		send(Connection, (char*)&choice, sizeof(int), NULL);
		Sleep(10);

	}
	system("pause");
	return 0;
}