#include "LoggerClient.h"
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include "../SHVNative/natives.h"


#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <string>
#define LOG(lvl, str) locLogger.Log(locLogger.##lvl, ##str, true)
#pragma comment(lib, "Ws2_32.lib")

void CClientNetwork::StartWSA() {
    // Initialize Winsock
    WSADATA wsaData;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        locLogger.Log(ERROR2, "WSA Init Failed!" + std::to_string(iResult), true);
        return;
    }

}
#define DEFAULT_PORT "27015"
void CClientNetwork::StartConnectionProcess() {
    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    // Resolve the server address and port
    iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        this->locLogger.Log(ERROR2, "getaddrinfo failed: " + std::to_string(iResult) + '\n', true);
        WSACleanup();
        return;
    }
    this->sockFd = INVALID_SOCKET;
    ptr = result;
    this->sockFd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (sockFd == INVALID_SOCKET) {
        locLogger.Log(ERROR2, "Error at socket(): " + std::to_string(WSAGetLastError()) + '\n', true);
        freeaddrinfo(result);
        WSACleanup();
        return;
    }
}

void CClientNetwork::ConnectionProcess() {
    iResult = connect(sockFd, ptr->ai_addr, (int)ptr->ai_addrlen);
    
    while (iResult < 0) {
        iResult = connect(sockFd, ptr->ai_addr, (int)ptr->ai_addrlen);
        locLogger.Log(ERROR2, "Connection Failed. Trying Again in 1 second.\n", true);
        WAIT(1000);
    }
    locLogger.Log(INFO, "Connection Success!", true);
    freeaddrinfo(result);

    if (sockFd == INVALID_SOCKET) {
        locLogger.Log(ERROR2, "Unable to connect to server!\n",true);
        WSACleanup();
        return;

    }
}

void CClientNetwork::Cleanup() {
    locLogger.Log(INFO, "We have decided to cleanup!", true);
    iResult = shutdown(sockFd, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        locLogger.Log(ERROR2, "shutdown failed: " + std::to_string(iResult) + '\n', true);
        closesocket(sockFd);
        WSACleanup();
        return;
    }
}
void CClientNetwork::SendData(std::string& buff) {
}

CClientNetwork::~CClientNetwork() {
    this->Cleanup(); // although we might not want to end it we have to :(
}
