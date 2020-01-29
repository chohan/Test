// gcc -g multicast.cpp -o multicast

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)

struct in_addr localInterface;
struct sockaddr_in groupSock;
struct sockaddr_in localSock;
struct ip_mreq group;
int sd;
char local_ip[] = "192.168.0.165";
char mcast_ip[] = "225.1.1.1";
unsigned int mcast_port = 5555;
char databuf[1024] = "Bismillah Multicast message!";


void tx(int argc, char** argv)
{
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sd < 0){ printf("Error opening datagram socket!\n"); exit(1);}
	else printf("Opening the datagram socket...OK\n");

	// init grop sockaddr struct with MC address ip:port
	memset((char*)&groupSock, 0, sizeof(groupSock));
	groupSock.sin_family = AF_INET;
	groupSock.sin_addr.s_addr = inet_addr(mcast_ip);
	groupSock.sin_port = htons(mcast_port);

	// disable loopback to receive same message sent
	{
		char loopch = 0;
		if(setsockopt(sd, IPPROTO_IP, IP_MULTICAST_LOOP, (char*)&loopch, sizeof(loopch)) < 0){
			perror("Error setting IP_MULTIAST_LOOP!\n");
//			close(sd);
			exit(1);
		} else { printf("Disabling loopback...OK.\n");}
	}

	// set local interface for outbound multicast datagram
	// IP provided should be associated with a local multicast capable interface
	localInterface.s_addr = inet_addr(local_ip);
	if(setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, (char*)&localInterface, sizeof(localInterface)) < 0)
	{perror("Error setting local interface"); exit(1);}
	else printf("Setting local interface...OK\n");

	// send message to multicase group
	for(int i=0; i<10; i++){
		if(sendto(sd, databuf, sizeof(databuf), 0, (struct sockaddr*)&groupSock, sizeof(groupSock)) < 0 )
		{perror("Error in sending datagram message!\n");}
		else printf("Sending datagram message...OK\n");

	// try re-read own sent message
//		if(read(sd, databuf, sizeof(databuf)) < 0){perror("Error reading message\n");}
//		socklen_t socklen = sizeof(groupSock);
//		if(recvfrom(sd, databuf, sizeof(databuf), 0, (struct sockaddr*)&groupSock, &socklen) < 0 ){
//			perror("Error reading message\n");
//		} else {printf("Message: %s", databuf);}
	}
}
// int addrlen = sizeof(addr);
// if((nbytes=recvfrom(sock, msgbuf, MSGBUFSIZE, 0,
//                               (struct sockaddr *) &addr,&addrlen)) < 0)


void rx(int argc, char** argv)
{
	// Create a datagram socket on which to receive
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sd < 0){perror("Opening datagram socket error");exit(1);}
	else printf("Opening datagram socket....OK.\n");

	// Enable SO_REUSEADDR to allow multiple instances of this
	// application to receive copies of the multicast datagrams
	{
		int reuse = 1;
		if(setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0)
		{
			perror("Setting SO_REUSEADDR error");
//			close(sd);
			exit(1);
		}
		else printf("Setting SO_REUSEADDR...OK.\n");
	}

	/* Bind to the proper port number with the IP address */
	/* specified as INADDR_ANY. */
	memset((char *) &localSock, 0, sizeof(localSock));
	localSock.sin_family = AF_INET;
	localSock.sin_port = htons(4321);
	localSock.sin_addr.s_addr = INADDR_ANY;
	if(bind(sd, (struct sockaddr*)&localSock, sizeof(localSock)))
	{
		perror("Binding datagram socket error");
//		close(sd);
		exit(1);
	}
	else printf("Binding datagram socket...OK.\n");
	 
	/* Join the multicast group 226.1.1.1 on the local 203.106.93.94 */
	/* interface. Note that this IP_ADD_MEMBERSHIP option must be */
	/* called for each local interface over which the multicast */
	/* datagrams are to be received. */
	group.imr_multiaddr.s_addr = inet_addr(mcast_ip);//"226.1.1.1");
	group.imr_interface.s_addr = inet_addr(local_ip);//"203.106.93.94");
	if(setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group)) < 0)
	{
		perror("Adding multicast group error");
//		close(sd);
		exit(1);
	}
	else printf("Adding multicast group...OK.\n");
	 
	// Read from the socket
	socklen_t socklen = sizeof(localSock);
	for(int i=0; i<10; i++){
		if(recvfrom(sd, databuf, sizeof(databuf), 0, (struct sockaddr*)&localSock, &socklen) < 0 ){
			perror("Error reading message\n");
		} else {printf("Message: %s", databuf);}
	}
}

int main(int argc, char** argv)
{
	     if(memcmp(argv[1], "tx", strlen("tx")) == 0)	tx(argc, argv);
	else if(memcmp(argv[1], "rx", strlen("rx")) == 0)	rx(argc, argv);

	return 0;
}

