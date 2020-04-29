#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <time.h>
#include <ctime>

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
	time_t now = time(0);
	tm* localtm = localtime(&now);
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
	cout << "Connected!\nTime start: " << asctime(localtm) << endl << "Compiled by Alina Stadnik" << endl;
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
	cout << "Time stop: " << asctime(localtm) << endl;
	system("pause");
	return 0;
}