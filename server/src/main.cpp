#include "server.h"

int main(int argc, char* argv[]) {

    try {
        network::Server server;
        server.start();
    } catch (const std::runtime_error &e) {
        std::cerr << "Runtime Error: " << e.what() << '\n';
    } catch (...) {
        std::cerr << "Unknown runtime error occurred.\n";
    }

    return 0;
}