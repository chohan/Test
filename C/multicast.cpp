// gcc -g multicast.cpp -o multicast

// The following program sends or receives multicast packets. If invoked
// with one argument, it sends a packet containing the current time to an
// arbitrarily chosen multicast group and UDP port. If invoked with no
// arguments, it receives and prints these packets. Start it as a sender on
// just one host and as a receiver on all the other hosts

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <ctime>
#include <chrono>
#include <thread>
#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)

#define MCAST_PORT 6000
#define MCAST_GROUP "224.0.0.0"

void Tx(int argc, char** argv)
{
	struct sockaddr_in addr;
	int sock, cnt;
	struct ip_mreq mreq;
	char message[1024];
	
	// set up socket
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {perror("Error opening datagram socket!\n"); exit(1);}
	printf("Opening multicast socket %s:%d\n", MCAST_GROUP, MCAST_PORT);

	//bzero((char *)&addr, sizeof(addr));
	memset((char*)&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(MCAST_PORT);
	socklen_t addrlen = sizeof(addr);
	
	// disable loopback to receive same message sent
	//char loopch = 0;
	//if(setsockopt(sock, IPPROTO_IP, IP_MULTICAST_LOOP, (char*)&loopch, sizeof(loopch)) < 0){
	//	perror("Error setting IP_MULTIAST_LOOP!\n");
	//	exit(1);
	//} else { printf("Disabling loopback...OK.\n");}

	// send
	addr.sin_addr.s_addr = inet_addr(MCAST_GROUP);
	while (true) {
		time_t t = time(0);
		sprintf(message, "time is %-24.24s", ctime(&t));
		printf("Sending: %s: \"%s\"\n", inet_ntoa(addr.sin_addr), message);
		if(sendto(sock, message, sizeof(message), 0, (struct sockaddr *) &addr, addrlen) < 0)
		{perror("Error in sending datagram message!\n");}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}


void Rx(int argc, char** argv)
{
	struct sockaddr_in addr;
	int sock, cnt;
	struct ip_mreq mreq;
	char message[1024];
	
	// set up socket
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {perror("Error opening datagram socket!\n"); exit(1);}
	printf("Opening multicast socket %s:%d\n", MCAST_GROUP, MCAST_PORT);

	//bzero((char *)&addr, sizeof(addr));
	memset((char*)&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(MCAST_PORT);
	socklen_t addrlen = sizeof(addr);
	
  if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		perror("Binding datagram socket error");
		exit(1);
	}

	mreq.imr_multiaddr.s_addr = inet_addr(MCAST_GROUP);         
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);         
	if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
		perror("setsockopt mreq");
		exit(1);
	}         
	
	// Enable SO_REUSEADDR to allow multiple instances of this
	// application to receive copies of the multicast datagrams
	int reuse = 1;
	if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0){
		perror("Setting SO_REUSEADDR error");
		exit(1);
	}else printf("Setting SO_REUSEADDR...OK.\n");

  // receive
	while (true) {
		if(recvfrom(sock, message, sizeof(message), 0, (struct sockaddr *) &addr, &addrlen) < 0)
		{perror("Error reading message\n");}
		printf("Receiving: %s: \"%s\"\n", inet_ntoa(addr.sin_addr), message);
	}
}

int main(int argc, char** argv)
{
	     if(memcmp(argv[1], "Tx", strlen("Tx")) == 0)	Tx(argc, argv);
	else if(memcmp(argv[1], "Rx", strlen("Rx")) == 0)	Rx(argc, argv);

	return 0;
}

