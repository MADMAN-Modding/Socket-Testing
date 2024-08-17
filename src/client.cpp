#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string.h>
#include "connection_info.hpp"

using namespace std;

void sendMessage(string text, int clientSocket)
{
    char *message = new char[text.length() + 1];

    strcpy(message, text.c_str());

    send(clientSocket, message, strlen(message), 0);

    close(clientSocket);
}

void copyFile(string fileName, int clientSocket)
{
    string textFileLine;

    ifstream FileToCopy(fileName);

    string message = {};

    while (getline(FileToCopy, textFileLine))
    {
        message += textFileLine + "\n";
    }
    
    sendMessage(message, clientSocket);
}

int main()
{
    while (true)
    {
        int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(portNumber);
        serverAddress.sin_addr.s_addr = INADDR_ANY;

        connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

        switch (comType)
        {
        case 0:
        {
            cout << "What do you want to say? ";

            string text;

            getline(cin, text);

            if (text == "TERMINATE_CLIENT")
            {
                cout << "Closing connection";
                sendMessage(text, clientSocket);
                return 0;
            }

            sendMessage(text, clientSocket);
            break;
        }

        case 1: {
            cout << "What file do you want to copy? ";

            string text;

            getline(cin, text);

            if (text == "TERMINATE_CLIENT")
            {
                cout << "Closing connection";
                sendMessage(text, clientSocket);
                return 0;
            }

            copyFile(text, clientSocket);

            break;
        }

        default:
            cout << "What are you doing here?" << endl;

            break;
        }
    }
}