#include "Csocket.h"
#include <iostream>
#include <string>

using namespace std;
string clientName;
void emptyCallback(const std::string& message) {
    // Do nothing
}

int main() {
    const char* serverIpAddress = "127.0.0.1";
    int serverPort = 12345;


    std::cout << "Welcome! This is a client program.\n";
    std::cout << "Please enter your name: ";
    std::getline(std::cin, clientName);
    
    if (initializeClient(serverIpAddress, serverPort) == -1) {
            return -1;
        }


    return 0;
}
