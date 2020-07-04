/** 
 * Thanks https://blog.csdn.net/xiaoquantouer/article/details/58001960/ !
 * OwO
*/

#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;

class Server {
	WORD sockVersion;
	WSADATA wsaData;
	SOCKET sListen, sClient;
	sockaddr_in sin, remoteAddr;
	int PORT, bufferSize;
	int nAddrLen;
	char * recvData;
	public:
		Server(int Port, int BufferSize) : PORT(Port), bufferSize(BufferSize) {
			recvData = new char[bufferSize];
		}
		Server() {
			PORT = 8080;
			bufferSize = 1024;
			recvData = new char[bufferSize];
		}
		int init() {
			sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (sListen == INVALID_SOCKET) {
				printf("Socket creation error! XwX");
				return -1;
			}
			sin.sin_family = AF_INET;
			sin.sin_port = htons(PORT);
			sin.sin_addr.S_un.S_addr = INADDR_ANY;
			if (bind(sListen, (LPSOCKADDR) & sin, sizeof(sin)) == SOCKET_ERROR) {
				printf("Binding Error! XwX");
				return -1;
			}
			if (listen(sListen, 5) == SOCKET_ERROR) {
				printf("Listening Error! XwX");
				return -1;
			}
		}
		string getBuffer() {
			nAddrLen = sizeof(remoteAddr);
			sClient = accept(sListen, (SOCKADDR *) & remoteAddr, &nAddrLen);
			if (sClient == INVALID_SOCKET) {
				printf("Accepting Error! XwX");
				return string("");
			}
			memset(recvData,0,sizeof(recvData));
			int ret = recv(sClient, recvData, bufferSize, 0);
			if (ret > 0) {
				recvData[ret] = 0x00;
				closesocket(sClient);
				return string(recvData);
			}
			closesocket(sClient);
			return string("");
		}
		void sendMsg(string msg) {
			sClient = accept(sListen, (SOCKADDR *) & remoteAddr, &nAddrLen);
			if (sClient == INVALID_SOCKET) {
				printf("Accepting Error! XwX");
				return ;
			}
			send(sClient, msg.c_str(), strlen(msg.c_str()), 0);
			closesocket(sClient);
			return ;
		}
		void closeSocket() {
			closesocket(sListen);
			WSACleanup();
			return ;
		}
};
