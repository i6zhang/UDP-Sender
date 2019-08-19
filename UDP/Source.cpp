#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std; 

#include <iostream>

// "SERVER" side
 
int main() {
	// set up WSA
	WSADATA WSA; 
	// create buffer
	char buffer[24];
	// values to fill the buffer with
	double qX = 1;
	double qY = 2;
	double qZ = 3;
	// filling the buffer - convert from double to bytes
	memcpy(&buffer[0], &qX, 8);
	memcpy(&buffer[8], &qY, 8);
	memcpy(&buffer[16], &qZ, 8);
	// create a socket
	SOCKET Socket; 
	// create the addres which we want to send packets to 
	sockaddr_in clientAddress; 
	int clientLen = sizeof(clientAddress); 
	// initialize WSA
	if (WSAStartup(MAKEWORD(2, 2), &WSA) != 0) {
		cout << "STARTUP FAILED: " << endl; 
	}
	// fill in the address attributes
	clientAddress.sin_family = AF_INET;
	InetPton(AF_INET, "142.20.171.54", &clientAddress.sin_addr.S_un.S_addr);
	clientAddress.sin_port = htons(25000); 
	// set up the socket
	Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); 

	while(true){
		// send the packets to the address
		int sendto = ::sendto(Socket, buffer, sizeof(buffer), 0, (SOCKADDR*)& clientAddress, sizeof(clientAddress));
		if (sendto == SOCKET_ERROR) {
			cout << "Sending Data Failed & Error -> " << WSAGetLastError() << endl; 
		}
	}
	// close socket and clean up 
	int closeSocket = closesocket(Socket);
	int WSAcleanup = WSACleanup();
}