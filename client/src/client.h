#ifndef CLIENT_H
#define CLIENT_H

#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#include <stdexcept>

#define DEFAULT_PORT 1402
#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define DISCONNECT_SYMBOL '#'
#define ERROR_C "CLIENT ERROR: "


namespace network {


    class Client {
    public:
        Client(int port = DEFAULT_PORT);
        ~Client();
        void connected();

    private:
        void process();
        bool disconnect(const char* args);

    private:
        int client;
        int port;
        struct sockaddr_in client_address;
        
    }; // Client


}; // namespace network


#endif // CLIENT_H