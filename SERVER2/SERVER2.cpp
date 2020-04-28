#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
<<<<<<< HEAD
#pragma warning(disable: 4996)
SOCKET Connections[100];
int Counter = 0;
=======
#include <string>


#pragma warning(disable: 4996)

using namespace std;

SOCKET newConnection;
SOCKET Connections[100];
int Counter = 0;


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

>>>>>>> 0edd48a12e40ff926f9569a77a598ad5260d875a
void ClientHandler(int index) {
	int msg_size;
	while (true) {
		recv(Connections[index], (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connections[index], msg, msg_size, NULL);
		for (int i = 0; i < Counter; i++) {
			if (i == index) {
				continue;
			}
			send(Connections[i], (char*)&msg_size, sizeof(int), NULL);
			send(Connections[i], msg, msg_size, NULL);
		}
		delete[] msg;
	}
}
<<<<<<< HEAD
int main(int argc, char* argv[]) {
	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}
=======


int main(int argc, char* argv[]) {
	string str;
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
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);
=======

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);

	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));

	listen(sListen, SOMAXCONN);

>>>>>>> 0edd48a12e40ff926f9569a77a598ad5260d875a
	SOCKET newConnection;
	for (int i = 0; i < 100; i++) {
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
		if (newConnection == 0) {
<<<<<<< HEAD
			std::cout << "Error #2\n";
		}
		else {
			std::cout << "Client Connected!\n";
			std::string msg = "Mary Malez";
			int msg_size = msg.size();
			send(newConnection, (char*)&msg_size, sizeof(int), NULL);
			send(newConnection, msg.c_str(), msg_size, NULL);
			Connections[i] = newConnection;
			Counter++;
			CreateThread(NULL, NULL,(LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
		}
	}
=======
			cout << "Error #2\n";
		}
		else {
			cout << "Client Connected!\n Mary Malez" << endl;
			Connections[i] = newConnection;
			Counter++;
			while (true) {
				string msg;
				string str;
				msg = "Welcome to the server\n To calculate accrued percent, enter:\n 1. Percent(0-100%): %";

				Sending(newConnection, msg);
				str = Getting(newConnection);
				int percent = atoi(str.c_str()); // Проценты

				msg = "2. Amount of days(1-365): ";

				Sending(newConnection, msg);
				str = Getting(newConnection);
				int days = atof(str.c_str()); // Дни

				msg = "3. Deposit amount: BYN";

				Sending(newConnection, msg);
				str = Getting(newConnection);
				double sum = atoi(str.c_str()); // Сумма вклада

				msg = "Accured precent: ";
				double year = sum * percent / 100;
				double acc_prec = year * days / 365;
				msg += to_string(acc_prec);
				Sending(newConnection, msg);
			}
		}
	}

>>>>>>> 0edd48a12e40ff926f9569a77a598ad5260d875a
	system("pause");
	return 0;
}