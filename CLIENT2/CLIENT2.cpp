#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
<<<<<<< HEAD
#include <string>
#pragma warning(disable: 4996)
using namespace std;
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
int main(int argc, char* argv[]) {
	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}
=======
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include <cstdlib>
#include <string>


#pragma warning(disable: 4996)

using namespace std;

SOCKET Connection;

void Sending(SOCKET conect, string msg) {
	int msg_size = msg.size();
	send(conect, (char*)&msg_size, sizeof(int), NULL);
	send(conect, msg.c_str(), msg_size, NULL);
}

string Getting(SOCKET conect) {
	string str;
	int msg_size;
	recv(conect, (char*)&msg_size, sizeof(int), NULL);
	char* msg = new char[msg_size + 1];
	msg[msg_size] = '\0';
	recv(conect, msg, msg_size, NULL);
	for (int i = 0; i < msg_size; i++) {
		str += msg[i];
	}
	return str;
}

void ClientHandler() {
	string percent_str;
	string days_str;
	string sum_str;
	while (true) {
		cout << Getting(Connection) << endl;
		cin >> percent_str;
		Sending(Connection, percent_str);

		cout << Getting(Connection) << endl;
		cin >> days_str;
		Sending(Connection, days_str);

		cout << Getting(Connection) << endl;
		cin >> sum_str;
		Sending(Connection, sum_str);

		cout << Getting(Connection) << endl;
	}
}



int main(int argc, char* argv[]) {
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);

	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		cout << "Error" << endl;
		exit(1);
	}

>>>>>>> 0edd48a12e40ff926f9569a77a598ad5260d875a
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;
<<<<<<< HEAD
	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		return 1;
	}
	std::cout << "Connected!\n";
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL,
		NULL, NULL);
	string msg1;
	while (true) {
		std::getline(std::cin, msg1);
		int msg_size = msg1.size();
		send(Connection, (char*)&msg_size, sizeof(int), NULL);
		send(Connection, msg1.c_str(), msg_size, NULL);
		Sleep(10);
	}
=======

	Connection = socket(AF_INET, SOCK_STREAM, NULL);

	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		cout << "Error: failed connect to server.\n";
		return 1;
	}
	cout << "Connected!\n Mary Malez" << endl;
	string percent_str;
	string days_str;
	string sum_str;
	cout << Getting(Connection) << endl;
	cin >> percent_str;
	Sending(Connection, percent_str);

	cout << Getting(Connection) << endl;
	cin >> days_str;
	Sending(Connection, days_str);

	cout << Getting(Connection) << endl;
	cin >> sum_str;
	Sending(Connection, sum_str);

	cout << Getting(Connection) << endl;
>>>>>>> 0edd48a12e40ff926f9569a77a598ad5260d875a
	system("pause");
	return 0;
}