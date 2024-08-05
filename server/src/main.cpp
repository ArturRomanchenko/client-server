#include "server.h"

int main(int argc, char* argv[]) {
    network::Server server;
    server.start();

    return 0;
}