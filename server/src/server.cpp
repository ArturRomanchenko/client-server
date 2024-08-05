#include "server.h"


namespace network {


network::Server::Server(int port): port(port) {
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) {
        std::cout << ERROR_S <<"establishing socket error.";
        exit(0);
    }

    std::cout << "SERVER: Socket for server was created.\n";

    server_address.sin_port = htons(DEFAULT_PORT);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htons(INADDR_ANY);

    init();
}


network::Server::~Server() {
    close(server);
    close(client);
}


bool network::Server::disconnect(const char* args)
{
    for (int idx = 0; idx < strlen(args); ++idx) {
        if (args[idx] == CLIENT_CLOSE_CONNECTION_SYMBOL) {
            return true;
        }
    }
    return false;
}


void network::Server::recive(int server) {
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
        if (disconnect(buffer)) {
            IS_EXIT = true;
        }

        while (!IS_EXIT) {
            std::cout << "Server: ";
            std::cin.getline(buffer, BUFFER_SIZE);
            send(server, buffer, BUFFER_SIZE, 0);
            if (disconnect(buffer)) {
                break;
            }
            
            std::cout << "Client: ";
            recv(server, buffer, BUFFER_SIZE, 0);
            std::cout << buffer << std::endl;
            if ( disconnect(buffer)) {
                break;
            }
        }
        
        std::cout << "\nGood Bye..." << std::endl;
        IS_EXIT = false;
        close(server);
        return;
    }
}


void network::Server::init() {
    if (bind(client, reinterpret_cast<struct sockaddr*>(&server_address),
        sizeof(server_address)) < 0) {
        std::cout << ERROR_S << "binding connection. Socket has already been establishing.\n";
        return;
    }

    std::cout << "SERVER: Listening clients...\n";
    listen(client, MAX_CLIENTS);
}


void network::Server::start() {
    //std::lock_guard lock(_mutex);
    for (;;) {
        socklen_t size = sizeof(server_address);
        server = accept(client, reinterpret_cast<struct sockaddr*>(&server_address), &size);
        if (server < 0) {
            std::cout << ERROR_S << "Can't accepting client.\n";
        } else {
            std::thread client_thread(&Server::recive, this, server);
            client_thread.detach();
        }
    }
}


}; // namespace network