#include <string>
#include <map>
#include <thread>


struct Client
{
  std::string     name;
  std::string     host;
  unsigned short  port;
  unsigned int    sock;
  std::thread::id thid;
  pthread_t       pth_id;
  std::string     status;
};

// callback function
//using cbFUNC = void(*)(const std::string clientHost, const unsigned int clientPort, const char* data, const int size);
using cbFUNC = void(*)(const char* buf, const int buf_size, const std::string& clientName, const int clientSock);

class Socket   
{   
public:
  Socket(const std::string& parent_);
  ~Socket(void);
  int CreateServerSocket(int nListeningPort, cbFUNC cbFunc);
  int CreateClientSocket(const std::string& sServerPC, int nServerPort, int retries, int retryDelay);

  void	servantTx(const char* buf, const int buf_size, const std::string& clientName="", const int clientSock=0);
  void	servantRx(const char* buf, const int buf_size, const std::string& clientName="", const int clientSock=0);

private:
		cbFUNC*	_pcbFunc;
    int opt = TRUE;   
    int master_socket , addrlen, client_socket[30] ,  
          max_clients = 30 , activity;
		// int i , valread, new_socket, sd; 
    int max_sd;   
//    struct sockaddr_in address;   
         
    char buffer[1025];  //data buffer of 1K  
         
    //set of socket descriptors  
    fd_set readfds;   
         
    //a message  
    char *message = "ECHO Daemon v1.0 \r\n";

  std::map<std::string, Client> _mapClient;
  std::string _sParent; // name of the parent object/process/function that created this socket object
};

