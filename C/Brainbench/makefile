#BOOST_ROOT=/usr/local/boost_1_41_0/
prefix=/usr/local/boost_1_41_0/
exec_prefix=$(prefix)
includedir=$(prefix)/include/
libdir=$(prefix)lib/

#export BOOST_ROOT=/usr/local/boost_1_41_0
#export LD_LIBRARY_PATH=/usr/local/boost_1_41_0/lib
#echo $LD_LIBRARY_PATH
#To create a static library, or to add additional object files to an existing static library
#ar rcs my_library.a file1.o file2.o


#to create a static library
#g++ -o user_sqrt1.o -c user_sqrt1.cpp 
#g++ -o user_log1.o -c user_log1.cpp
#ar rc libuser.a user_sqrt1.o user_log1.o 
#ranlib libuser.a

#to remove CR (^M) character http://kb.iu.edu/data/acux.html
#:1,$s/^M//g

CC = g++
CFLAGS = -I /usr/local/boost_1_41_0 -c

#library directories
LIBDIRS = \
	  -L./ \
	  -L/usr/local/boost_1_41_0/lib

#libraries
LIBS = -lboost_filesystem \
       -lboost_system \
       -lboost_serialization \
       -lboost_thread

#library flags
LFLAGS = $(LIBDIRS) $(LIBS)

all: Brainbench

Brainbench:   Brainbench.o  Test.o myboost.o mySTL.o IKM.o Previsor.o Tibra.o Macquarie.o Nomura.o
	$(CC) Brainbench.o  Test.o myboost.o mySTL.o IKM.o Previsor.o Tibra.o Macquarie.o Nomura.o -o Brainbench $(LFLAGS)


#Global.o: Global.h
#	g++ -c Global.h

Brainbench.o: Brainbench.cpp
	$(CC) $(CFLAGS) Brainbench.cpp

Test.o: Test.cpp
	$(CC) $(CFLAGS) Test.cpp

myboost.o: myboost.cpp
	$(CC) $(CFLAGS) myboost.cpp

mySTL.o: mySTL.cpp
	$(CC) $(CFLAGS) mySTL.cpp

IKM.o: IKM.cpp
	$(CC) $(CFLAGS) IKM.cpp

Previsor.o: Previsor.cpp
	$(CC) $(CFLAGS) Previsor.cpp

Tibra.o: Tibra.cpp
	$(CC) $(CFLAGS) Tibra.cpp

Macquarie.o: Macquarie.cpp
	$(CC) $(CFLAGS) Macquarie.cpp

Nomura.o: Nomura.cpp
	$(CC) $(CFLAGS) Nomura.cpp

clean:
	rm -rf *o Brainbench


