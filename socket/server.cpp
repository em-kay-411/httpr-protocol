#include <iostream>
#include <netdb.h>
#include <memory>
#include <stdexcept>
#include <array>
#include <netinet/in.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX 1024
#define PORT 8080
using namespace std;

string serverPath = "/Users/emkay/Documents/httpr/applications/server.js";

void waitForMessages(int connectionFileDescriptor)
{
    char buffer[MAX];
    array<char, 1024> responseBuffer;

    for (;;)
    {
        cout << connectionFileDescriptor << endl;
        if(connectionFileDescriptor < 0){
            continue;
        }

        bzero(buffer, MAX);       

        read(connectionFileDescriptor, buffer, sizeof(buffer));

        string request = buffer;

        // executing the shell command for NodeJS
        string command = "node " + serverPath + " \"" + request + "\"";
        cout << command << endl;
        string result = "";

        FILE *pipe = popen(command.c_str(), "r");
        if (!pipe){
            throw runtime_error("popen() failed!");
        }           

        while (!feof(pipe))
        {
            if (fgets(responseBuffer.data(), 1024, pipe) != nullptr){
                result += responseBuffer.data();
            }                
            // cerr << result << '\n';
        }

        int rc = pclose(pipe);

        if (rc == EXIT_SUCCESS)
        { // == 0
            // cerr << "Success" << '\n';
        }
        else if (rc == EXIT_FAILURE){
            // cerr << "Failed" << '\n';
        }

        cout <<"Result : " <<  result << endl;         

        write(connectionFileDescriptor, result.c_str(), result.length());   
        break;
    }

    // write(connectionFileDescriptor, request.c_str(), request.length());
}

int main()
{
    int socketFileDescriptor, connectionFileDescriptor;
    struct sockaddr_in serverAddress, clientAddress;

    socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);

    if (socketFileDescriptor < 0)
    {
        cout << "Error creating socket" << endl;
        exit(0);
    }
    else
    {
        cout << "Scoket created" << endl;
    }

    bzero(&serverAddress, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(PORT);

    if (::bind(socketFileDescriptor, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == 0)
    {
        cout << "Bound successfully" << endl;
    }
    else
    {
        cout << "error binding" << endl;
        exit(0);
    }

    if (listen(socketFileDescriptor, 5) != 0)
    {
        cout << "Failed Listenting" << endl;
        exit(0);
    }
    else
    {
        cout << "listening" << endl;
    }

    socklen_t clientAddressSize = sizeof(clientAddress);

    connectionFileDescriptor = accept(socketFileDescriptor, (struct sockaddr *)&clientAddress, &clientAddressSize);

    if (connectionFileDescriptor < 0)
    {
        cout << "Connection Failed" << endl;
        exit(0);
    }
    else
    {
        cout << "Connected to the socket" << endl;
    }

    waitForMessages(connectionFileDescriptor);

    close(socketFileDescriptor);
}