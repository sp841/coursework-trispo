#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>
#pragma warning(disable: 4996)

SOCKET Connection;

void ClientHandler() {
	int msg_size;
	while (true) {
		recv(Connection, (char*)&msg_size, sizeof(int), NULL);
		char* msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connection, msg, msg_size, NULL);
		std::cout << msg << "\n";
		delete[] msg;
	}
}

struct DepositInfo {
	float depositInterest;
	uint32_t depositTerm;
	float depositAmount;
};

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::cout << "Брич Павел Романович\n";
	time_t time = std::time(nullptr);
	struct tm tm;
	localtime_s(&tm, &time);
	std::cout << std::put_time(&tm, "%d.%m.%Y %H:%M:%S") << std::endl;

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
	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		return 1;
	}
	std::cout << "Connected!\n";
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL,
		NULL, NULL);
	std::string msg1;
	while (true) {
		std::cout << "\nРасчёт процентов по банковскому вкладу\n";

		DepositInfo deposit;

		std::cout << "Введите процент: ";
		std::getline(std::cin, msg1);
		deposit.depositInterest = std::stof(msg1);

		std::cout << "Введите срок (в месяцах): ";
		std::getline(std::cin, msg1);
		deposit.depositTerm = std::stoi(msg1);

		std::cout << "Введите сумму: ";
		std::getline(std::cin, msg1);
		deposit.depositAmount = std::stof(msg1);

		std::cout << "\n";

		send(Connection, (char*)&deposit, sizeof(deposit), NULL);
		Sleep(10);
	}
	system("pause");
	return 0;
}