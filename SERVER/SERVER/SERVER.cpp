﻿#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <map>
#include <string>
#pragma warning(disable: 4996)
SOCKET Connections[100];
int Counter = 0;
std::map <  std::string, std::string > def = { {"C#","is a general-purpose, multi-paradigm programming language encompassing strong typing, lexically scoped, imperative, declarative, functional, generic, object-oriented (class-based), and component-oriented programming disciplines."},
	{"Java "," is a general-purpose programming language that is class-based, object-oriented, and designed to have as few implementation dependencies as possible."},
	{"Python ","is an interpreted, high-level, general-purpose programming language." }};
void ClientHandler(int index) {
	int msg_size;
	while (true) {
		recv(Connections[index], (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connections[index], msg, msg_size, NULL);
		
		msg_size = def[msg].size() + 1;
			send(Connections[index], (char*)&msg_size, sizeof(def[msg].size() + 1), NULL);
			send(Connections[index], def[msg].c_str(), msg_size, NULL);
			
		
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
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);
	SOCKET newConnection;
	std::cout << "Birula Maksim SP841\n";
	std::cout << "Mon May 4 20:35:30 2020\n";
	for (int i = 0; i < 100; i++) {
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
		if (newConnection == 0) {
			std::cout << "Error #2\n";
		}
		else {
			std::cout << "Client Connected!\n";
			
			std::string msg = "Hello. It`s my first network program!";
			int msg_size = msg.size();
			send(newConnection, (char*)&msg_size, sizeof(int), NULL);
			send(newConnection, msg.c_str(), msg_size, NULL);
			Connections[i] = newConnection;
			
				Counter++;
			CreateThread(NULL, NULL,
				(LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
		}
	}
	system("pause");
	return 0;
}