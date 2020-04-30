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
string words[5] = { "Dualism" , "Agile software" , "integrated development environment" , "Software maintenance" , "Computer software" };
string terms[5] = { " it's systems or problems in which an intelligent adversary attempts to exploit the weaknesses of the investigator  " , "comprises various approaches to software development under which requirements and solutions evolve through the collaborative effort of self-organizing and cross-functional teams and their customer " ,
"is a software application that provides comprehensive facilities to computer programmers for software development. " , "in software engineering is the modification of a software product after delivery to correct faults, to improve performance or other attributes." ,
"is a collection of data or computer instructions that tell the computer how to work." };

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
			cout << asctime(localtm) << endl << "Vladislav Birulin \nConnected!\n";
			string msg = "The database has definitions such as: Dualism , Agile software , integrated development environment , Software maintenanc , Computer software\nEnter the term: ";
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
