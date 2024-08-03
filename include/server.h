#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <thread>
//#include <mutex>

#define DEFAULT_PORT 1402
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 3
#define ERROR_S "SERVER ERROR: "
#define CLIENT_CLOSE_CONNECTION_SYMBOL '#'

namespace network {

class Server {
  public:
    Server(int port = DEFAULT_PORT);
    ~Server();
    void start();
  private:
    bool is_client_connection_close(const char* args);
    void handle_client(int server);
    void setup_server();
  private:
    int server;
    int client;
    int port;
    //std::mutex _mutex;
    struct sockaddr_in server_address;
}; // Server

}; // namespace network

#endif // SERVER_H