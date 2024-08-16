#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include "connection_info.hpp"

void sendMessage(std::string text, int clientSocket) {
        char* message = new char[text.length() + 1];

        strcpy(message, text.c_str());

        send(clientSocket, message, strlen(message), 0);

        close(clientSocket);
}

int main() {
    
    while (true)
    {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portNumber);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
        std::cout << "What do you want to say? ";

        std::string text;

        std::getline(std::cin, text);

        if (text == "TERMINATE_CLIENT") {
            std::cout << "Closing connection";
            sendMessage(text, clientSocket);
            break;
        }        

        sendMessage(text, clientSocket);
    }
    
}