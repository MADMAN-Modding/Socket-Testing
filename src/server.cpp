#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <unistd.h>
#include "connection_info.hpp"

using namespace std;

void messageReader(char *buffer)
{
    cout << "Message from client: " << buffer << endl;
};

void fileWriter(char *buffer, ofstream &MessagesFile)
{
    cout << "Message: " << buffer << endl;

    MessagesFile << buffer << endl;
};

int main()
{

    ofstream MessagesFile("messages.txt");

    if (comType != 1)
    {
        remove("messages.txt");
        MessagesFile.close();
    }

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portNumber);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    while (true)
    {
        listen(serverSocket, 5);

        int clientSocket = accept(serverSocket, nullptr, nullptr);

        char buffer[1024] = {0};

        recv(clientSocket, buffer, sizeof(buffer), 0);

        switch (comType)
        {
        case 0:
            messageReader(buffer);
            break;

        case 1:
            if (buffer == "TERMINATE_SERVER")
            {
                MessagesFile.close();
                break;
            }
            else
            {
                fileWriter(buffer, MessagesFile);
                break;
            }
        default:
            cout << "How did you get here?"
                      << endl;
            break;
        }

        if (strcmp(buffer, "TERMINATE_SERVER") == 0)
        {
            cout << "Stopping Server" << endl;
            close(serverSocket);
            break;
        }
    }
}