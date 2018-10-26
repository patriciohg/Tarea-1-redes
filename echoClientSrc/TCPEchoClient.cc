/*
 *   C++ sockets on Unix and Windows
 *   Copyright (C) 2002
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "YASL.h"      // For Socket and SocketException
#include "checkArgs.h"
#include <fstream>
#include <string>
#include <iostream>    // For cerr and cout
#include <cstdlib>     // For atoi()

int RCVBUFSIZE = 10000;    // Size of receive buffer
using namespace std;
int main(int argc, char *argv[]) {

	ofstream ficheroSalida;

	std::string nombreArchivo;
	checkArgs* argumentos = new checkArgs(argc, argv);
	
    std::string servAddress; 
	uint16_t    echoServPort;
    std::string echoString;   
	
	servAddress   = argumentos->getArgs().SERVER;
	echoServPort  = argumentos->getArgs().PORT;
	nombreArchivo = 	argumentos->getArgs().ARCHIVO;
	echoString    = "GET / HTTP/1.1\nHost:"+servAddress+"\nUser-Agent: Mozilla/5.0\n\n ";
	delete argumentos;
	int echoStringLen = echoString.length();   // Determine input length
	try {
		// Establish connection with the echo server
		TCPSocket sock(servAddress, echoServPort);

		// Send the string to the echo server
		sock.send(echoString.c_str(), 200);
		//variable trucha
		std::string largo = "";
		//
		char echoBuffer[RCVBUFSIZE + 1];    // Buffer for echo string + \0
		int bytesReceived = 0;              // Bytes read on each recv()
		int totalBytesReceived = 0;         // Total bytes read
		
		// Receive the same string back from the server
		std::cout << "Received: ";               // Setup to print the echoed string
		/*<-----------------------------Cambios generados por nosotros----------->
		while (totalBytesReceived < echoStringLen) {
			if ((bytesReceived = (sock.recv(echoBuffer, RCVBUFSIZE))) <= 0) {
				std::cerr << "Unable to read 1";
				exit(EXIT_FAILURE);	
			}

			totalBytesReceived += bytesReceived;     // Keep tally of total bytes
			echoBuffer[bytesReceived] = '\0';        // Terminate the string!
			for(int i = 101; i<121;i++){
				if(echoBuffer[i] == '\n'){
					RCVBUFSIZE = atoi(largo.c_str());
					std::cout << RCVBUFSIZE;			
					break;
				}
				largo +=echoBuffer[i];
			}
		}
		char echoBuffer2[RCVBUFSIZE+1];	
		totalBytesReceived = 0;

		// Send the string to the echo server
		sock.send(echoString.c_str(), 200);

		 bytesReceived = 0;              // Bytes read on each recv()
		 totalBytesReceived = 0;         // Total bytes read
		
		// Receive the same string back from the server
		std::cout << "Received: ";               // Setup to print the echoed string
		*/
		while (totalBytesReceived < echoStringLen) {

			// Receive up to the buffer size bytes from the sender
			if ((bytesReceived = (sock.recv(echoBuffer, RCVBUFSIZE))) <= 0) {
				std::cerr << "Unable to read 2";
				exit(EXIT_FAILURE);	
				
			}
			///
		    ficheroSalida.open (nombreArchivo);
		    ficheroSalida << echoBuffer;	    
			//
			totalBytesReceived += bytesReceived;     // Keep tally of total bytes
			echoBuffer[bytesReceived] = '\0';        // Terminate the string!
			std::cout << echoBuffer;                      // Print the echo buffer
		}
		ficheroSalida.close();
		std::cout << std::endl;

		// Destructor closes the socket

	} catch(SocketException &e) {
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	
}
	return EXIT_SUCCESS;
}
