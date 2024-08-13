#include "client.h"


namespace network {


network::Client::Client(int port): port(port) {

    try {

        client = socket(AF_INET, SOCK_STREAM, 0);
        if (client < 0) {
            std::cerr << ERROR_C << "establishing socket error.";
            exit(0);
        }

        client_address.sin_port = htons(DEFAULT_PORT);
        client_address.sin_family = AF_INET;
        inet_pton(AF_INET, SERVER_IP, &client_address.sin_addr);

    } catch (const std::runtime_error &e) {
        std::cerr << "Establishing socket error. " << e.what() << '\n';
    }

    std::cout << "\n=> Client socket created.";
}


network::Client::~Client() {
    close(client);
    std::cout << "=> Client socket closed.\n";
}


bool network::Client::disconnect(const char* args)
{
    for (int idx = 0; idx < strlen(args); ++idx) {
        if (args[idx] == DISCONNECT_SYMBOL) {
            return true;
        }
    }
    return false;
}


void network::Client::process() {
    char buffer[BUFFER_SIZE];

    for (;;) {
        std::cout << "Client: ";
        std::cin.getline(buffer, BUFFER_SIZE);
        send(client, buffer, BUFFER_SIZE, 0);
        if (disconnect(buffer)) {
            throw std::runtime_error(std::string("Error: Disconnection command received. Buffer content: ") + buffer);
        }

        std::cout << "Server: ";
        recv(client, buffer, BUFFER_SIZE, 0);
        std::cout << buffer;
        if (disconnect(buffer)) {
            throw std::runtime_error(std::string("Error: Disconnection command received. Buffer content: ") + buffer);
        }

        std::cout << std::endl;
    }
    
    close(client);

    std::cout << "\nGood Bye..." << std::endl;
}


void network::Client::connected() {
    char buffer[BUFFER_SIZE];

    try {
        if (connect(client, reinterpret_cast<const struct sockaddr*>(&client_address), sizeof(client_address)) == 0) {
            std::cout << "=> Connection to server "
                    << inet_ntoa(client_address.sin_addr)
                    << " with port number: " << DEFAULT_PORT << '\n';
        }
        
        std::cout << "=> Waiting for server confirmation...\n";
        recv(client, buffer, BUFFER_SIZE, 0);
        std::cout << "=> Connection established.\n" << "Enter " << DISCONNECT_SYMBOL << " for close the connection.\n";
        
        process();
    } catch (const std::runtime_error &e) {
        std::cerr << "Runtime Error: " << e.what() << '\n';
    } catch (...) {
        std::cerr << "Unknown runtime error occurred.\n";
    }
}


}; // namespace network