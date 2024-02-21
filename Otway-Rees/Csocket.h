#ifndef Csocket_H
#define Csocket_H

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

int createSocket(const char* ipAddress, int port);

void startServer(void (*callback)(const std::string&), int sock);

int sendMessage(int sock, const char* message);
std::map<std::string, std::string> parseJSON(const std::string& filename);

void serializeJSON(const std::map<std::string, std::string>& data, const std::string& filename);

#endif // Csocket_H


