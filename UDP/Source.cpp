#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#include <chrono>

#pragma comment(lib, "ws2_32.lib")

using namespace std; 

#include <iostream>

// "SERVER" side
 
int main() {
	WSADATA WSA; 
	char buffer[24];

	double qX = 1;
	double qY = 2;
	double qZ = 3;

	memcpy(&buffer[0], &qX, 8);
	memcpy(&buffer[8], &qY, 8);
	memcpy(&buffer[16], &qZ, 8);

	auto start = chrono::high_resolution_clock::now();
	auto finish = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed;

	SOCKET Socket; 
	
	sockaddr_in clientAddress; 
	int clientLen = sizeof(clientAddress); 

	if (WSAStartup(MAKEWORD(2, 2), &WSA) != 0) {
		cout << "STARTUP FAILED: " << endl; 
	}
	
	clientAddress.sin_family = AF_INET;
	InetPton(AF_INET, "142.20.171.54", &clientAddress.sin_addr.S_un.S_addr);
	clientAddress.sin_port = htons(25000); 

	Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); 

	while(true){
		int sendto = ::sendto(Socket, buffer, sizeof(buffer), 0, (SOCKADDR*)& clientAddress, sizeof(clientAddress));
		if (sendto == SOCKET_ERROR) {
			cout << "Sending Data Failed & Error -> " << WSAGetLastError() << endl; 
		}
		finish = chrono::high_resolution_clock::now(); 
		elapsed = finish - start; 
		qX = elapsed.count();
		qY = elapsed.count();
		qZ = elapsed.count();
		
		memcpy(&buffer[0], &qX, 8);
		memcpy(&buffer[8], &qY, 8);
		memcpy(&buffer[16], &qZ, 8);
	}
	int closeSocket = closesocket(Socket);
	int WSAcleanup = WSACleanup();
}