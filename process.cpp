/********************************************************
 * process.cpp                                          *
 *                                                      *
 * Progetto Tipo 1 Sistemi in tempo Reale               *
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include "process.h"

enum { EXECUTED, INCOMING, READY, RUNNING, WAITING };

process::process() {;}
process::process(int _releaseTime, int _deadline, int _executionTime, std::list<int>& _dependencies){
    releaseTime = _releaseTime;
    deadline = _deadline;
    executionTime = _executionTime;
    dependencies = _dependencies;
    state = dependencies.size() == 0 ? ( releaseTime == 0 ? READY : INCOMING ) : WAITING;
    executedTime = 0;
}

bool process::executeOneStep(){
    std::cout << "one step\n";
    return ++executedTime == executionTime;
}

bool process::removeDependency(int id){
	dependencies.remove(id);
	std::cout << dependencies.size(); 
	return dependencies.size() == 0;
}