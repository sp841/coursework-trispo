#include<iostream>
#pragma comment(lib, "ws2_32.lib") 
#include <winsock2.h> 
#pragma warning(disable: 4996)

SOCKET Connections[100];
int Counter = 0;

int main(int argc, char* argv[]) 
{
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);

    if (WSAStartup(DLLVersion, &wsaData) != 0) 
    { // запускаем библиотеку WSA и выполняем проверку т.е. (если библиотека загрузилась удачно то она вернет значения 0)
            std::cout << "Error" << std::endl;
            exit(1);
    }

    SOCKADDR_IN addr; //для хранения адреса
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //хранит адрес локальной сети
    addr.sin_port = htons(1111); //хранит номер порта
    addr.sin_family = AF_INET; //указываем семейство протоколов для интернет

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);

	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	for (int i = 0; i < 100; i++)
	{


		SOCKET newConnection;
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
		if (newConnection == 0)
		{
			std::cout << "Error #2\n";
		}
		else
		{
			std::cout << "Client Connected!\n";
			char msg[256] = "Hello. It`s my first network program!";
			send(newConnection, msg, sizeof(msg), NULL);
			/*std::string msg = "Hello. It`s my first network program!";
			int msg_size = msg.size();
			send(newConnection, (char*)&msg_size, sizeof(int), NULL);
			send(newConnection, msg.c_str(), msg_size, NULL);
			Connections[i] = newConnection;
			Counter++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);*/
		}
	}
	
	system("pause");
	return 0;
}

