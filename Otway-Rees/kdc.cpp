#include "Csocket.h"


void emptyCallback(const std::string& message) {
    // Do nothing
}

int main() {
    const char* serverIpAddress = "127.0.0.1";
    int serverPort = 12345;


    int clientSocket = createSocket(serverIpAddress, serverPort);
    if (clientSocket == -1) {
        std::cerr << "Error: Failed to create client socket\n";
        return -1;
    }

    startServer(emptyCallback, clientSocket);

    return 0;
}