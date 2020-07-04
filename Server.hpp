/**
 * Thank you, https://geeksforgeeks.org/socket-programming-cc/.
 * d(0w0)b!
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
using namespace std;

class Server {
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt, addrlen;
	char * buffer;
	int buffSize;
	short PORT;
	public:
		Server(const short Port, const int bufferSize) : PORT(Port), buffSize(bufferSize) {
			buffer = new char[bufferSize];
			opt = 1;
			addrlen = sizeof(address);
		}
		Server() {
			buffer = new char[1024];
			opt = 1;
			PORT = 8080;
			buffSize = 1024;
			addrlen = sizeof(address);
		}
		void init() {
			// Creating Socket File Descriptor
			if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
				perror("Socket file descriptor creation failed! XwX");
				exit(EXIT_FAILURE);
			}
			// Forcefully attaching socket to the port
			if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
				perror("Setsockopt Failed! XwX");
				exit(EXIT_FAILURE);
			}
			address.sin_family = AF_INET;
			address.sin_addr.s_addr = INADDR_ANY;
			address.sin_port = htons(PORT);
			// Forcefully attaching socket to the port
			if (bind(server_fd, (struct sockaddr *) & address, sizeof(address)) < 0) {
				perror("Binding Failed! XwX");
				exit(EXIT_FAILURE);
			}
			if (listen(server_fd, 3) < 0) {
				perror("Listening Failed! XwX");
				exit(EXIT_FAILURE);
			}
			if ((new_socket = accept(server_fd, (struct sockaddr *) & address, (socklen_t *) & addrlen)) < 0) {
				perror("Error Accepting! XwX");
				exit(EXIT_FAILURE);
			}
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
