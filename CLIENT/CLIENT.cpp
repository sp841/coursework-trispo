
#pragma comment(lib, "ws2_32.lib") 
#include <winsock2.h> 
#include <iostream> 
#include <string> 
#include <ctime>
#pragma warning(disable: 4996) 

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
    int a;

    /* Account a1(8111, 99.99);
    // test client
     a1.print();     // A/C no: 8111 Balance=$99.99
     a1.credit(20);
     a1.debit(10);
     a1.print();     // A/C no: 8111 Balance=$109.99
 */time_t now = time(0);

 // convert now to string form
 char* dt = ctime(&now);

 std::cout << "The local date and time is: " << dt << std::endl;

 // convert now to tm struct for UTC
 tm* gmtm = gmtime(&now);
 dt = asctime(gmtm);
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

    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);

    std::string msg1;
    while (true) {
        std::getline(std::cin, msg1);
        int msg_size = msg1.size();
        

            send(Connection, (char*)&msg_size, sizeof(int), NULL);
        send(Connection, msg1.c_str(), msg_size, NULL);
        Sleep(10);
    }

    system("pause");
    return 0;
}

