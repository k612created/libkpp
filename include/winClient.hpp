/**
 * Thanks https://blog.csdn.net/xiaoquantouer/article/details/58001960 !
 * OwO
 */

#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;

class Client {
  WORD sockVersion = MAKEWORD(2, 2);
  WSADATA data;
  SOCKET sClient;
  sockaddr_in serAddr;
  int PORT, bufferSize;
  int nAddrLen;
  char * recvData;
  string serverAddr;
  public:
    Client(int Port, int BufferSize, const char * ServerAddr) : PORT( Port ), bufferSize( BufferSize ), serverAddr(ServerAddr) {
      recvData = new char[bufferSize];
    }
    Client() {
      PORT = 8080;
      bufferSize = 1024;
      recvData = new char[bufferSize];
    }
    int init() {
      if (WSAStartup(sockVersion, &data) != 0) {
        return -1;
      }
      sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      if (sClient == INVALID_SOCKET) {
        printf("Invalid Socket! XwX");
        return -1;
      }
      serAddr.sin_family = AF_INET;
      serAddr.sin_port = htons(PORT);
      serAddr.sin_addr.S_un.S_addr = inet_addr(serverAddr.c_str());
      if (connect(sClient, (sockaddr *) & serAddr, sizeof(serAddr)) == SOCKET_ERROR) {
        printf("Connect Error! XwX");
        closesocket(sclient);
        return -1;
      }
    }

    string getBuffer() {
      memset(recvData, 0, sizeof(recvData));
      int ret = recv(sClient, recvData, bufferSize, 0);
      if (ret > 0) {
        recvData[ret] = 0x00;
      }
      closesocket(sClient);
      return string(recvData);
    }
    
    void sendMsg(string msg) {
      send(sClient, msg.c_str(), strlen(msg.c_str()), 0);
      closesocket(sClient);
      return ;
    }

    void closeSocket() {
      WSACleanup();
      return ;
    }

};
