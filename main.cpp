/********************************************************
 * main.cpp                                             *
 *                                                      *
 * Progetto Tipo 1 Sistemi in tempo Reale               *
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include "processes.h"

//add_process(int id, int releasetime, int deadline, int executiontime, std::list<int>& dependencies); //construct

int main(int argc, char** argv){
    int myints[]= {1,2};
    int myints2[]= {0,2};
    std::list<int> test0(myints,myints+2);
    std::list<int> test1,test2,test3(myints2,myints2+2);
    processes a;

    //Adding processes
    a.add_process(0,0,5,3,test0);
    a.add_process(1,0,1,1,test1);
    a.add_process(2,1,5,3,test2);
    a.add_process(3,2,1,1,test3);

    std::cout << "\n\n";
    a.printProcesses();
    // int i = 0;
    //while(!a.executeOneStep(1)) {};
    return 0;
};
