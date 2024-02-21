#include "Csocket.h"

int createSocket(const char* ipAddress, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Error: Could not create socket\n";
        return -1;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ipAddress);
    serverAddr.sin_port = htons(port);

    if (bind(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error: Bind failed\n";
        close(sock);
        return -1;
    }

    return sock;
}

void startServer(void (*callback)(const std::string&), int sock) {
    if (listen(sock, 10) == -1) {
        std::cerr << "Error: Listen failed\n";
        close(sock);
        return;
    }

    std::cout << "Server listening\n";

    struct sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    while (true) {
        int clientSocket = accept(sock, (struct sockaddr *)&clientAddr, &clientAddrSize);
        if (clientSocket == -1) {
            std::cerr << "Error: Accept failed\n";
            close(sock);
            return;
        }

        char buffer[1024] = {0};
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            std::cerr << "Error: Failed to receive message\n";
            close(clientSocket);
            continue;
        }

        // Create a new thread to handle the callback function
        std::thread(callback, std::string(buffer)).detach();

        close(clientSocket);
    }
}


int sendMessage(int sock, const char* message) {
    if (send(sock, message, strlen(message), 0) == -1) {
        std::cerr << "Error: Sending message failed\n";
        close(sock);
        return 0;
    }

    return 1;
}

int initializeClient(const char* serverIpAddress, int serverPort) {
    int clientSocket = createSocket(serverIpAddress, serverPort);
    if (clientSocket == -1) {
        std::cerr << "Error: Failed to create client socket\n";
        return -1;
    }
    startServer(emptyCallback, clientSocket);
    
    return 0;
}

// // Function to parse JSON from a file
// std::map<std::string, std::string> parseJSON(const std::string& filename) {
//     std::ifstream file(filename);
//     std::map<std::string, std::string> data;

//     if (file.is_open()) {
//         std::string line;
//         while (std::getline(file, line)) {
//             // Parse JSON line by line (simplified)
//             // Example: {"key": "value"}
//             size_t pos = line.find(':');
//             if (pos != std::string::npos) {
//                 std::string key = line.substr(1, pos - 2);
//                 std::string value = line.substr(pos + 2, line.size() - pos - 3);
//                 data[key] = value;
//             }
//         }
//         file.close();
//     } else {
//         std::cerr << "Error: Unable to open file\n";
//     }

//     return data;
// }

// // Function to serialize data to JSON and write to a file
// void serializeJSON(const std::map<std::string, std::string>& data, const std::string& filename) {
//     std::ofstream file(filename);
//     if (file.is_open()) {
//         file << "{\n";
//         for (const auto& pair : data) {
//             file << "  \"" << pair.first << "\": \"" << pair.second << "\",\n";
//         }
//         file << "}\n";
//         file.close();
//     } else {
//         std::cerr << "Error: Unable to open file\n";
//     }
// }