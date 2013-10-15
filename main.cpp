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
    int myints[]= {1};
    std::list<int> test(myints,myints+1);
    std::list<int> test2;
    processes a;
    a.add_process(0,0,5,3,test);
    a.add_process(1,0,1,1,test2);

    // int i = 0;
    //while(!a.executeOneStep(1)) {};
    return 0;
};
