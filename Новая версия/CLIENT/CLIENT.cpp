#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include <time.h>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)
#pragma warning(disable: 4551)
#pragma warning(disable: 4244)

using namespace std;

SOCKET Connection;

int size_oper(string o) {
	int n = atof(o.c_str());
	int k = 1;
	while ((n /= 10) > 0) k++;
	return k;
}

int main(int argc, char* argv[]) {
	int msg_size;
	char* msg;
	string operand1;
	string operand2;
	string operation;
	WSAStartup;
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
	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		return 1;
	}
	cout << "Connected!\nBy Alesya Lagun\n";
	time_t now = time(0);
	tm* localtm = localtime(&now);
	cout << asctime(localtm);
	string msg1;
	while (true) {
		recv(Connection, (char*)&msg_size, sizeof(int), NULL);
		msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connection, msg, msg_size, NULL);
		cout << msg << endl;
		
		cin >> operand1;

		msg_size = size_oper(operand1);
		send(Connection, (char*)&msg_size, sizeof(int), NULL);
		send(Connection, operand1.c_str(), msg_size, NULL);
		
		recv(Connection, (char*)&msg_size, sizeof(int), NULL);
		msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connection, msg, msg_size, NULL);
		cout << msg << endl;

		cin >> operand2;

		msg_size = size_oper(operand2);
		send(Connection, (char*)&msg_size, sizeof(int), NULL);
		send(Connection, operand2.c_str(), msg_size, NULL);

		recv(Connection, (char*)&msg_size, sizeof(int), NULL);
		msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connection, msg, msg_size, NULL);
		cout << msg << endl;

		cin >> operation;

		msg_size = operation.size();
		send(Connection, (char*)&msg_size, sizeof(int), NULL);
		send(Connection, operation.c_str(), msg_size, NULL);
		Sleep(10);
	}
	system("pause");
	return 0;
}