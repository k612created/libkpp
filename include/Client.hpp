/**
 * Thank you, https://geeksforgeeks.org/socket-programming-cc/.
 * d(0w0)b!
*/

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
using namespace std;

class Client {
		int sock, valread;
		struct sockaddr_in serv_addr;
		char * buffer;
		int PORT, buffSize;
		string addr;
	public:
		Client(const short Port, const int bufferSize, const char * Address) : PORT(Port), buffSize(bufferSize), addr(string(Address)) {
			sock = 0;
			buffer = new char[bufferSize];
		}
		Client() {
			PORT = 8080;
			buffSize = 1024;
			buffer = new char[1024];
			sock = 0;
		}

		int init() {
			if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
				printf("\n Socket Creation Error! XwX \n");
				return -1;
			}
			serv_addr.sin_family = AF_INET;
			serv_addr.sin_port = htons(PORT);
			if (inet_pton(AF_INET, addr.c_str(), &serv_addr.sin_addr) <= 0) {
				printf("\n Invalid address / Address not supported! XwX \n");
				return -1;
			}
			if (connect(sock, (struct sockaddr *) & serv_addr, sizeof(serv_addr)) < 0) {
				printf("\n Connection Failed! XwX \n");
				return -1;
			}
			return 0;
		}

		string getBuffer() {
			memset(buffer,0,sizeof(buffer));
			valread = read(new_socket, buffer, buffSize);
			return string(buffer);
		}
		void sendMsg(const char * msg) {
			send(new_socket, msg, strlen(msg), 0);
			return;
		}
		void sendMsg(string msg) {
			send(new_socket, msg.c_str(), strlen(msg.c_str()), 0);
			return;
		}
};
