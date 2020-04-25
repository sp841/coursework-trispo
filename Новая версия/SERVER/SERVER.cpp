#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include <time.h>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

using namespace std;

SOCKET Connections[100];
int Counter = 0;

int main(int argc, char* argv[]) {
	time_t now = time(0);
	tm* localtm = localtime(&now);
	int operand1, operand2;
	char operation;
	int msg_size;
	string str;
	char* msg;
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		cout << "Error" << std::endl;
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
			cout << "Error #2\n";
		}
		else {
			cout << "Client Connected!\nBy Alesya Lagun\n";
			str = "Enter the first operand: ";
			msg_size = str.size();
			send(newConnection, (char*)&msg_size, sizeof(int), NULL);
			send(newConnection, str.c_str(), msg_size, NULL);

			str = "";
			recv(newConnection, (char*)&msg_size, sizeof(int), NULL);
			msg = new char[msg_size + 1];
			msg[msg_size] = '\0';
			recv(newConnection, msg, msg_size, NULL);
			for (int i = 0; i < msg_size; i++) {
				str += msg[i];
			}
			operand1 = atoi(str.c_str());

			str = "Enter the second operand: ";
			msg_size = str.size();
			send(newConnection, (char*)&msg_size, sizeof(int), NULL);
			send(newConnection, str.c_str(), msg_size, NULL);

			str = "";
			recv(newConnection, (char*)&msg_size, sizeof(int), NULL);
			msg = new char[msg_size + 1];
			msg[msg_size] = '\0';
			recv(newConnection, msg, msg_size, NULL);
			for (int i = 0; i < msg_size; i++) {
				str += msg[i];
			}
			operand2 = atoi(str.c_str());

			str = "Enter the operation(%,*,-,+,/): ";
			msg_size = str.size();
			send(newConnection, (char*)&msg_size, sizeof(int), NULL);
			send(newConnection, str.c_str(), msg_size, NULL);

			str = "";
			recv(newConnection, (char*)&msg_size, sizeof(int), NULL);
			msg = new char[msg_size + 1];
			msg[msg_size] = '\0';
			recv(newConnection, msg, msg_size, NULL);
			operation = *msg;
			switch (operation) {
				case '+': {
					cout << "Result '+': " << operand1 + operand2 << endl << asctime(localtm);
					break;
				}
				case '-': {
					cout << "Result '-': " << operand1 - operand2 << endl << asctime(localtm);
					break;
				}
				case '/': {
					cout << "Result '/': " << operand1 / operand2 << endl << asctime(localtm);
					break;
				}
				case '*': {
					cout << "Result '*': " << operand1 * operand2 << endl << asctime(localtm);
					break;
				}
				case '%': {
					cout << "Result '%': " << operand1 % operand2 << endl << asctime(localtm);
					break;
				}
				default: {
					cout << "Error";
					break;
				}
			}
			Connections[i] = newConnection;
			Counter++;
		}
	}
	system("pause");
	return 0;
}