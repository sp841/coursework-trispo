#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include <exception>
using namespace std;
#pragma warning(disable: 4996)

SOCKET Connection;
int client_choice;

void ClientHandler() {
	while (true) {
		char terms[100];
		recv(Connection, terms, sizeof(terms), NULL);
		cout << terms << endl;
	}
}

int main(int argc, char* argv[]) {

	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		cout << "Error" << endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;
	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		cout << "Error: failed connect to server.\n";
		return 1;
	}
	cout << "Subotko Ekaterina 29.04.2020 Connected!\n\n";
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);

	cout << "Enter the number of term (definition from the Oxford Dictionary):\n1 - House\n2 - Eye\n3 - Mouse\n4 - Berry" << endl << endl;
	while (true) {

		cout << "Number of term: ";
		cin >> client_choice;
		cout << "\n";
		while (client_choice <= 0 || client_choice > 4) {
			cout << "Error, try again\n\n";
			cout << "Numbe of term: ";
			cin >> client_choice;
		}

		client_choice--;
		send(Connection, (char*)&client_choice, sizeof(int), NULL);
		Sleep(10);
	}
	system("pause");
	return 0;
}