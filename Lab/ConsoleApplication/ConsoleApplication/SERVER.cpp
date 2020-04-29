#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <time.h>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#pragma warning(disable: 4996)
#pragma warning(disable: 4551)

using namespace std;

SOCKET Connections[100];
int Counter = 0;
string words[5] = { "Ford" , "Lamborghini" , "Earth" , "Dog" , "Space" };
string terms[5] = { "Is an American multinational automaker that has its main headquarters in Dearborn, Michigan." , "Is an Italian brand and manufacturer of luxury sports cars and SUVs based in Sant'Agata Bolognese." ,
"Is the third planet from the Sun and the only astronomical object known to harbor life." , "Is a member of the genus Canis (canines), which forms part of the wolf-like canids, and is the most widely abundant terrestrial carnivore." ,
"is the boundless three-dimensional extent in which objects and events have relative position and direction." };

void ClientHandler(int index) {
	int msg_size;
	int term_size;
	string term;
	while (true) {
		recv(Connections[index], (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connections[index], msg, msg_size, NULL);
		cout << msg << endl;
		for (int i = 0; i < Counter; i++) {
			if (i == index) {
				for (int i = 0; i < 5; i++) {
					if (strcmp(words[i].c_str(), msg) == 0) {
						term = terms[i];
						term_size = term.size();
					}
				}
			}
			send(Connections[index], (char*)&term_size, sizeof(int), NULL);
			send(Connections[index], term.c_str(), term_size, NULL);
		}
		delete[] msg;
	}
}


int main(int argc, char* argv[]) {
	time_t now = time(0);
	tm* localtm = localtime(&now);
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
			cout << asctime(localtm) << endl << "Welcome to the system!\n";
			string msg = "The database has definitions such as: Ford, Lamborghini, Earth, Dog, Space\nEnter the term: ";
			int msg_size = msg.size();
			send(newConnection, (char*)&msg_size, sizeof(int), NULL);
			send(newConnection, msg.c_str(), msg_size, NULL);
			Connections[i] = newConnection;
			Counter++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
		}
	}
	system("pause");
	return 0;
}


