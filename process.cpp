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

void printList(std::list<int>& myList) {
    for (std::list<int>::iterator it = myList.begin(); it != myList.end(); it++)
        std::cout << *it << ' ';
    std::cout << '\n';
}

process::process() {;}

process::process(int _id, int _releaseTime, int _deadline, int _executionTime, std::list<int>& _dependencies){
    id = _id;
    releaseTime = _releaseTime;
    deadline = _deadline;
    executionTime = _executionTime;
    dependencies = _dependencies;

    //making a copy of the list
    for (std::list<int>::iterator it = dependencies.begin(); it != dependencies.end(); it++)
        original_dependencies.push_back(*it);

    state = dependencies.size() == 0 ? ( releaseTime == 0 ? READY : INCOMING ) : WAITING;
    executedTime = 0;

    printProcess();
}

void process::addProcessInWhenExecuted(int id) {
	whenExecuted.push_back(id);
}

bool process::executeOneStep(){
    std::cout << "one step\n";
    return ++executedTime == executionTime;
}

std::list<int> process::listDependencies() {
	return dependencies;
}

void process::printProcess(){
    std::cout << "Process id: " << id << '\n';;

    std::cout << "Dependencies from: \n";
    printList(original_dependencies);
}

bool process::removeDependency(int id){
	dependencies.remove(id);
	std::cout << dependencies.size(); 
	return dependencies.size() == 0;
}
