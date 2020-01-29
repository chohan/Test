// gcc -c -o forPython.o forPython.c
// gcc -shared -o forPython.so forPython.o
// gcc -shared -o forPython.so forPython.cpp

//#include <iostream>

extern "C" {
int add(int a, int b){ return a+b; }
int subtract(int a, int b) {return a-b;}
}

