#include <iostream>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX 1024
#define PORT 8080
using namespace std;

void sendAndReceiveToServer(int socketFileDescriptor, string request)
{
    char buffer[MAX];
    bzero(buffer, MAX);

    // cout << request << endl;

    write(socketFileDescriptor, request.c_str(), request.length());

    bzero(buffer, sizeof(buffer));

    read(socketFileDescriptor, buffer, MAX);

    // Send stdout as response buffer
    cout << buffer << endl;

    // write(socketFileDescriptor, request.c_str(), request.length());
}

int main(int argc, char *argv[])
{
    string host = argv[1];
    string request = argv[2];
    int socketFileDescriptor;
    struct sockaddr_in serverAddress, clientAddress;

    socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDescriptor < 0)
    {
        cout << "Error creating socker" << endl;
        exit(0);
    }
    else
    {
        cout << "Socket created" << endl;
    }

    bzero(&serverAddress, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(host.c_str());
    serverAddress.sin_port = htons(PORT);

    if (connect(socketFileDescriptor, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) != 0)
    {
        cout << "Error in connection" << endl;
        exit(0);
    }
    else
    {
        cout << "Connected to server socket" << endl;
    }

    sendAndReceiveToServer(socketFileDescriptor, request);

    close(socketFileDescriptor);

    return 0;
}