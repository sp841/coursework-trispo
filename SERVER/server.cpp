#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <iomanip>
#pragma warning(disable: 4996)

SOCKET Connections[100];
int Counter = 0;

struct DepositInfo {
	float depositInterest;
	uint32_t depositTerm;
	float depositAmount;
};

void ClientHandler(int index) {
	DepositInfo deposit;
	while (true) {
		recv(Connections[index], (char*)&deposit, sizeof(DepositInfo), NULL);
		float sum = deposit.depositAmount * (deposit.depositInterest * deposit.depositTerm * 30.4375f / (365.25f * 100.f));

		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << sum;

		std::string str = "Сумма процентов по вкладу: " + stream.str();

		int msg_size = (int)strlen(str.c_str());
		send(Connections[index], (char*)&msg_size, sizeof(int), NULL);
		send(Connections[index], str.c_str(), msg_size, NULL);
	}
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::cout << "Рудько Сергей СП841\n";
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
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);
	SOCKET newConnection;
	for (int i = 0; i < 100; i++) {
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
		if (newConnection == 0) {
			std::cout << "Error #2\n";
		}
		else {
			std::cout << "Client #" << Counter << " connected!\n";
			Connections[i] = newConnection;
			Counter++;
			CreateThread(NULL, NULL,
				(LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
		}
	}
	system("pause");
	return 0;
}