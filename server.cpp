#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#define DEFAULT_PORT 1402
#define BUFFER_SIZE 1024
#define ERROR_S "SERVER ERROR: "
#define CLIENT_CLOSE_CONNECTION_SYMBOL '#'

void hendle_client(int client) {}

bool is_client_connection_close(const char* args)
{
    for (int idx = 0; idx < strlen(args); ++idx) {
        if (args[idx] == CLIENT_CLOSE_CONNECTION_SYMBOL) {
            return true;
        }
    }
    return false;
}

int main(int argc, char** argv)
{
    int client;
    int server;
    
    struct sockaddr_in server_address;
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) {
        std::cout << ERROR_S <<"establishing socket error.";
        exit(0);
    }

    std::cout << "SERVER: Socket for server was created.\n";

    server_address.sin_port = htons(DEFAULT_PORT);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htons(INADDR_ANY);

    int ret = bind(client, reinterpret_cast<struct sockaddr*>(&server_address),
        sizeof(server_address));

    if (ret < 0) {
        std::cout << ERROR_S << "binding connection. Socket has already been establishing.\n";
        return -1;
    }

    socklen_t size = sizeof(server_address);
    std::cout << "SERVER: Listening clients...\n";
    listen(client, 1);

    server = accept(client, reinterpret_cast<struct sockaddr*>(&server_address), &size);
    if (server < 0) {
        std::cout << ERROR_S << "Can't accepting client.\n";
    }

    // можно обернуть в потоки и иметь несколько клиентов
    char buffer[BUFFER_SIZE];
    bool IS_EXIT = false;
    while (server > 0) {
        strcpy(buffer, "=> Server connected!\n");
        send(server, buffer, BUFFER_SIZE, 0);
        std::cout << "=> Connected to the client!" << 
        std::endl << "Enter" << CLIENT_CLOSE_CONNECTION_SYMBOL << "to end the connection\n\n";

        std::cout << "Client: ";
        recv(server, buffer, BUFFER_SIZE, 0);
        std::cout << buffer << std::endl;
        if (is_client_connection_close(buffer)) {
            IS_EXIT = true;
        }

        while (!IS_EXIT) {
            std::cout << "Server: ";
            std::cin.getline(buffer, BUFFER_SIZE);
            send(server, buffer, BUFFER_SIZE, 0);
            if (is_client_connection_close(buffer)) {
                break;
            }
            
            std::cout << "Client: ";
            recv(server, buffer, BUFFER_SIZE, 0);
            std::cout << buffer << std::endl;
            if ( is_client_connection_close(buffer)) {
                break;
            }
        }
        
        std::cout << "\nGood Bye..." << std::endl;
        IS_EXIT = false;
        exit(1);
    }
    return 0;
}