#include "server.h"

int main(int argc, char* argv[]) {
    network::Server server(DEFAULT_PORT1);
    server.start();

    return 0;
}