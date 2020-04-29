#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <time.h>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <vector>
#include <cstdlib>

#pragma warning(disable: 4996)
#pragma warning(disable: 4551)
#pragma warning(disable: 4018)

using namespace std;

SOCKET Connections[100];
int Counter = 0;

void ClientHandler(int index) {
	int k;
	string str;
	int str_size;
	vector<string> free_topic = {"Методология DevOps","Инструменты DevOps","Методология RUP","Методология ITIL","Инструменты для создания прототипов"};
	vector<string> record_book = {"SO942-01","SO942-02","SO942-03","SO941-05"};
	vector<string> busy_topic(record_book.size());
	int msg_size;

	busy_topic.reserve(free_topic.size());

	while (true) {
		recv(Connections[index], (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connections[index], msg, msg_size, NULL);
		for (int i = 0; i < Counter; i++) {
			if (i == index) {
				for (int j = 0; j < record_book.size(); j++) {
					if (strcmp(record_book[j].c_str(),msg) == 0) {
						k = 0 + rand() % free_topic.size();
						if (free_topic[k] != "") {
							str = "Ваша тема: " + free_topic[k] + "\nСвободные темы: ";

							busy_topic[j] = std::move(free_topic[k]);
							free_topic.erase(free_topic.begin() + k); 
							
							for (int q = 0; q < free_topic.size(); q++) {
								str += free_topic[q] + " ";
							}
							str += "\nЗанятые темы: ";
							for (int z = 0; z < busy_topic.size(); z++) {
								str += busy_topic[z] + " ";
							}
							str_size = str.size();
							send(Connections[index], (char*)&str_size, sizeof(int), NULL);
							send(Connections[index], str.c_str(), str_size, NULL);
						}
					}
				}
			}
			
		}
		delete[] msg;
	}
}


int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");
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
			cout << "Пилющенко Альберт\nClient Connected!\n";
			string msg = "Введите номер зачётки(Например СО942-01): ";
			int msg_size = msg.size();
			send(newConnection, (char*)&msg_size, sizeof(int), NULL);
			send(newConnection, msg.c_str(), msg_size, NULL);
			Connections[i] = newConnection;
			Counter++;
			CreateThread(NULL, NULL,(LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);

		}
	}
	system("pause");
	return 0;
}