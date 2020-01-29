// g++ -g -w -o ipc ipc.cpp --std=c++17 -lpthread && ./ipc
// https://www.tutorialspoint.com/inter_process_communication/inter_process_communication_pipes.htm

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <cstdlib>
#include <ctime>
#include <cassert>
#include <cstring>
#include <cmath>

#include <thread>
#include <mutex>
#include <future>
#include <chrono>


#include <sys/ipc.h>
#include <sys/shm.h>
#define trace(str)(std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << "(): " << str << std::endl)



// Pipe ##########################################
#include <stdio.h>
#include <unistd.h>
namespace _Pipe {

void in_process(int argc, char** argv)
{
	char msg[2][20]={"Hi","Hello"};
	int fd[2];
	int status = pipe(fd);
	if(status == -1){ std::cout << "Unable to create pipe\n"; return; }

	std::cout << "Writing to pipe - Message is " << msg[0] << "\n";
	write(fd[1], msg[0], sizeof(msg[0]));

	char rx_msg[20];
	read(fd[0], rx_msg, sizeof(msg));
	std::cout << "Reading from pipe - Message is " << rx_msg << "\n";	

	// performance testing
	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::microseconds micro;
	auto start = Clock::now();
	//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	for(int i=0; i<1000000; i++){
		write(fd[1], msg[0], sizeof(msg[0]));
		read(fd[0], rx_msg, sizeof(msg));
	}
	auto finish = Clock::now();
	micro diff = std::chrono::duration_cast<micro>(finish - start);
	std::cout << "time diff (micro sec)=" << diff.count() << std::endl;
	// 1217625
}

void across_processes(int argc, char** argv)
{
	int fd[2];
	int pid;
	char txMsg[2][20]={"Hi", "Hello"};
	char rxMsg[20];
	int status = pipe(fd);
	if(status == -1){ std::cout << "Unable to create pipe\n"; return; }

	// creae child process
	pid = fork();
	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::microseconds micro;

	// child process
	if(pid == 0){
		read(fd[0], rxMsg, sizeof(rxMsg));
		std::cout << "Child Process: Reading from pipe - msg 1 " << rxMsg << "\n";
		read(fd[0], rxMsg, sizeof(rxMsg));
		std::cout << "Child Process: Reading from pipe - msg 2 " << rxMsg << "\n";

		// performance test
		auto start = Clock::now();
		for(int i=0; i<1000000; i++){
			read(fd[0], rxMsg, sizeof(rxMsg));
		}
		auto finish = Clock::now();
		micro diff = std::chrono::duration_cast<micro>(finish - start);
		std::cout << "Child Process read time (micro sec)=" << diff.count() << std::endl;	// 1318191
	}

	// paranet process
	else {
		std::cout << "Parent Process: Writing to pipe - msg 1 " << txMsg[0] << "\n";
		write(fd[1], txMsg[0], sizeof(txMsg[0]));
		std::cout << "Parent Process: Writing to pipe - msg 2 " << txMsg[1] << "\n";
		write(fd[1], txMsg[1], sizeof(txMsg[1]));

		// performance test
		auto start = Clock::now();
		for(int i=0; i<1000000; i++){
			write(fd[1], txMsg[0], sizeof(txMsg[0]));
		}
		auto finish = Clock::now();
		micro diff = std::chrono::duration_cast<micro>(finish - start);
		std::cout << "Parent Process wite time (micro sec)=" << diff.count() << std::endl;	// 1322955
	}
}
}


// Named pipe ####################################
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define FIFO_FILE "/tmp/fifo_2way"
namespace named_pipe {

void tx(int argc, char** argv)
{
	char msg[]={"Hello\n"};

	mkfifo(FIFO_FILE, S_IFIFO|0640);	// create FIFO
	int fd = open(FIFO_FILE, O_CREAT|O_RDWR);
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	std::cout << "sending messages\n";
	write(fd, msg, sizeof(msg));

	// performance test
	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::microseconds micro;
	auto start = Clock::now();
	for(int i=0; i<100; i++){
		write(fd, msg, sizeof(msg));
	}
	auto finish = Clock::now();
	micro diff = std::chrono::duration_cast<micro>(finish - start);
	std::cout << "Tx Process time (micro sec)=" << diff.count() << std::endl;	// 4999

	close(fd); 
}

void rx(int argc, char** argv)
{
	char msg[100];

	//mkfifo(FIFO_FILE, S_IFIFO|0640);	// create FIFO
	int fd = open(FIFO_FILE, O_RDWR);
	
	std::cout << "receiving messages\n";
	int bytes = read(fd, msg, sizeof(msg));
	std::cout << msg << std::endl;

	// performance test
	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::microseconds micro;
	auto start = Clock::now();
	for(int i=0; i<100; i++){
		bytes = read(fd, msg, sizeof(msg));
	}
	auto finish = Clock::now();
	micro diff = std::chrono::duration_cast<micro>(finish - start);
	std::cout << "Rx Process time (micro sec)=" << diff.count() << std::endl;	// 2705

	close(fd);
}
}


// Shared Memory #################################
// testing: (./ipc SM_tx &); ./ipc SM_rx
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#define BUF_SIZE 1024
#define SHM_KEY 0x1234

namespace SM {

struct shmseg {
	int cnt;
	int complete;
	char buf[BUF_SIZE];
};

int fill_buffer(char* bufptr, int size)
{
	static char ch = 'A';
	int filled_count;
	memset(bufptr, ch, size-1);
	bufptr[size-1] = '\0';
	if(ch > 'z') ch = 'A';	// ch > 'z' => ch='A'
	if((ch>='A') && (ch<='z')){	
		if((ch>=91) && (ch<=96)){ch='A';}	// excluding non alphabet
	}
	filled_count = strlen(bufptr);
	ch++;
	return filled_count;
}

void tx(int argc, char** argv)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	int shmid;
	struct shmseg *smp;
	char *bufptr;
	int space_available;

	shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
	if(shmid == -1){perror("Shared memory"); return;}
	smp = (shmseg*)shmat(shmid, NULL, 0);	// attach
	if(smp == (void*) -1){perror("shared memory attach"); return;}

	// transfer block of data from buffer to shared memory
	bufptr = smp->buf;
	space_available = BUF_SIZE;
	int i;
	for(i=0; i<5; i++){
		smp->cnt = fill_buffer(bufptr, space_available);
		smp->complete = 0;
		std::cout << "Writing Process: SM wrote " << smp->cnt << std::endl;
		bufptr = smp->buf;
		space_available = BUF_SIZE;
		sleep(3);
	}
	std::cout << "Tx Process: wrote " << i << std::endl;
	smp->complete = 1;
	if(shmdt(smp) == -1){perror("shmdt");return;}
	if(shmctl(shmid, IPC_RMID, 0) == -1){perror("shmctl");return;}
	std::cout << "Tx Process: Complete\n";
}

void rx(int argc, char** argv)
{
	int shmid;
	struct shmseg *smp;

	shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
	if(shmid == -1){perror("Shared memory"); return;}
	smp = (shmseg*)shmat(shmid, NULL, 0);	// attach
	if(smp == (void*) -1){perror("shared memory attach"); return;}

	// transfer block of data from shared memory to stdout
	while(smp->complete !=1){
		std::cout << "segment contain: " << smp->buf << std::endl;
		if(smp->cnt == -1){perror("read");return;}
		std::cout << "Reading Process: SM read " << smp->cnt << std::endl;
		sleep(3);
	}
	std::cout << "Rx Process: reading done. Detaching SM\n";
	if(shmdt(smp) == -1){perror("shmdt");return;}
	std::cout << "Rx Process: Complete\n";
}

}


// Message Queues ################################
// testing: (./ipc MQ_tx &); ./ipc MQ_rx
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define PERMS 0644

namespace MQ {
struct msgbuf {
   long mtype;
   char mtext[200];
};

void tx(int argc, char** argv)
{
	struct msgbuf buf;
	int msgid;
	int len;
	key_t key;
	system("touch msgq.txt");

	if((key = ftok("msgq.txt", 'B')) == -1){perror("ftok");return;}
trace("");
	if((msgid = msgget(key, PERMS|IPC_CREAT)) == -1){perror("msgget");return;}
trace("");
	std::cout << "MQ Tx: ready to send messages.\n";
	buf.mtype = 1;	// don't care the type now
	strcpy(buf.mtext, "Bismillah");
	//std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	for(int i=0; i<1; i++){
		if(msgsnd(msgid, &buf, strlen(buf.mtext)+1, 0) == -1) perror("msgsnd");
		std::cout << "MQ Tx: sent " << buf.mtext << std::endl;
	}
	if(msgctl(msgid, IPC_RMID, NULL) == -1){perror("msgctl");return;}
	std::cout << "MQ Tx: sending is done\n";
}

void rx(int argc, char** argv)
{
	struct msgbuf buf;
	int msgid;
	int len;
	key_t key;

	if((key = ftok("msgq.txt", 'B')) == -1){perror("ftok");return;}
trace("");
	//if((msgid = msgget(key, PERMS)) == -1){perror("msgget");return;}
	while((msgid = msgget(key, PERMS)) == -1) { sleep(3);}
trace("");
	std::cout << "MQ Rx: ready to receive messages.\n";
	for(int i=0; i<1; i++){
		if(msgrcv(msgid, &buf, sizeof(buf.mtext), 0, 0) == -1){perror("msgrcv");return;}
		std::cout << "MQ Rx: received " << buf.mtext << std::endl;
	}
	std::cout << "MQ Tx: receiving is done\n";
	system("rm msgq.txt");
}

}


// Semaphones ####################################
namespace Semaphone {

void tx(int argc, char** argv)
{
}

void rx(int argc, char** argv)
{
}

}


// signals #######################################
namespace Signal {

void tx(int argc, char** argv)
{
}

void rx(int argc, char** argv)
{
}

}


// Memory Mapping ################################
// Filename: mmap_test.c 
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>

namespace MM {
void write_mmap_sample_data()
{
	int fd;
	char ch;
	struct stat testfilestat;
	fd = open("MMAP_DATA.txt", O_CREAT|O_TRUNC|O_WRONLY, 0666);
	if(fd==-1){perror("File open error"); return;}
	ch='A';while(ch<='Z'){write(fd, &ch, sizeof(ch));ch++;}	// write A to Z
	ch='0';while(ch<='9'){write(fd, &ch, sizeof(ch));ch++;} // write 0 to 9
	ch='a';while(ch<='z'){write(fd, &ch, sizeof(ch));ch++;} // write a to z
	close(fd);	
}

void tx(int argc, char** argv)
{
	struct stat mmapstat;
	char *data;
	int minbyteindex;
	int maxbyteindex;
	int offset;
	int fd;
	int unmapstatus;

	write_mmap_sample_data();
	if(stat("MMAP_DATA.txt", &mmapstat)==-1){perror("stat failure"); return;}
	if((fd=open("MMAP_DATA.txt", O_RDONLY))==-1){perror("open failure"); return;}
	data = (char*)mmap((caddr_t)0, mmapstat.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if(data == (caddr_t)(-1)){perror("mmap failure"); return;}
	minbyteindex = 0;
	maxbyteindex = mmapstat.st_size -1;
	do{
		printf("Enter -1 to quit or ");
		printf("enter a number between %d and %d: ", minbyteindex, maxbyteindex);
	scanf("%d", &offset);
	if((offset >= 0) && (offset <= maxbyteindex))
		printf("Received char at %d is %c\n", offset, data[offset]);
	else if(offset != -1)
		printf("Received invalid index %d\n", offset);
	}while(offset != -1);
	unmapstatus = munmap(data, mmapstat.st_size);

	if(unmapstatus == -1){perror("numap failure"); return;}
	close(fd);
	system("rm -f MMAP_DATA.txt");
	return;
}

void rx(int argc, char** argv)
{
}

}


int main(int argc, char** argv)
{
	std::cout << "Bismillah\n";

	     if(memcmp(argv[1], "pipe_in_process", strlen("pipe_in_process")) == 0)  _Pipe::in_process(argc, argv);
	else if(memcmp(argv[1], "pipe_across_processes", strlen("pipe_across_processes")) == 0)  _Pipe::across_processes(argc, argv);

	else if(memcmp(argv[1], "named_pipe_tx", strlen("named_pipe_tx")) == 0)  named_pipe::tx(argc, argv);
	else if(memcmp(argv[1], "named_pipe_rx", strlen("named_pipe_rx")) == 0)  named_pipe::rx(argc, argv);

	else if(memcmp(argv[1], "SM_tx", strlen("SM_tx")) == 0)  SM::tx(argc, argv);
	else if(memcmp(argv[1], "SM_rx", strlen("SM_rx")) == 0)  SM::rx(argc, argv);

	else if(memcmp(argv[1], "MQ_tx", strlen("MQ_tx")) == 0)  MQ::tx(argc, argv);
	else if(memcmp(argv[1], "MQ_rx", strlen("MQ_rx")) == 0)  MQ::rx(argc, argv);

	else if(memcmp(argv[1], "MM_tx", strlen("MM_tx")) == 0)  MM::tx(argc, argv);
	

	return 0;
}
