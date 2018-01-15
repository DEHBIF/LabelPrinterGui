
#include <fstream>
#include <iostream>
#include <sys/socket.h>

#include <cstring> 
extern "C"{
	#include <stdio.h>
	#include <sys/socket.h>
	#include <stdlib.h>
	#include <netinet/in.h>
	#include <string.h>
	#include <arpa/inet.h>
	#include <stdio.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <cstdlib>
	#include <cstring>
	#include <unistd.h>
}

class PrinterJob {
	std::string payload;
	public:
	PrinterJob(std::string devID, std::string mac, std::string modelName,std::string password, std::string ID){
	payload = devID + ";" + mac + ";" + modelName + ";" + ID + ";" + password + "\n\n"; 
    };	

    std::string get(){
       return payload;
    };
}; 

class PrinterServer{
public:
	
	int _port; 
	std::string _ip; 

	PrinterServer(std::string ip, int port){
		_port = port; 
		_ip = ip; 
	}

	int sendPayload( std::string payload){ 
		std::cout << "Server should send: " << payload << std::endl;
		struct sockaddr_in address;
		int sock = 0, valread;
		struct sockaddr_in serv_addr;

		char buffer[1024] = {0};
		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
		    printf("\n Socket creation error \n");
		    return -1;
		}

		memset(&serv_addr, '0', sizeof(serv_addr));

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(_port);
		  
		// Convert IPv4 and IPv6 addresses from text to binary form
		if(inet_pton(AF_INET, _ip.c_str(), &serv_addr.sin_addr)<=0){
		    printf("\nInvalid address/ Address not supported \n");
		    return -1;
		}

		if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		    printf("\nConnection Failed \n");
		    return -1;
		}
		send(sock , payload.c_str() , payload.length() , 0 );
		std::cout << "Message sent\n";
		return 0;
     };
} ;


class LabelPrinter{
public:
	int print(std::string devID, std::string mac, std::string modelName, std::string ID, std::string password, std::string ip, int port){
		PrinterJob pj(devID, mac, modelName, ID, password);
		PrinterServer server(ip, port);
		std::string payload = pj.get();
		return server.sendPayload(payload);
	}
}; 













