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

process::process() {
	id = -1;
	releaseTime = -1;
	deadline = -1;
	executionTime = -1;
	executedTime = -1;
}

void process::addProcessInWhenExecuted(int _id) {
	dependenciesTo.push_back(_id);
}

bool process::executeOneStep(){
    return ++executedTime == executionTime;
}

int process::getReleaseTime(){
	return releaseTime;
}

void process::initialise(int _id, int _releaseTime, int _deadline, int _executionTime, std::list<int>& _dependencies){
    id = _id;
    releaseTime = _releaseTime;
    deadline = _deadline;
    executionTime = _executionTime;
    dependencies = _dependencies;

    //making a copy of the list
    for (std::list<int>::iterator it = dependencies.begin(); it != dependencies.end(); it++)
        original_dependencies.push_back(*it);

    executedTime = 0;
}

std::list<int> process::listDependenciesFrom() {
	return dependencies;
}

std::list<int> process::listDependenciesTo() {
	return dependenciesTo;
}

void process::printProcess(){
    std::cout << "Process id: " << id << '\n';

    std::cout << "Dependencies from: ";
    utilities::printList(original_dependencies);

    std::cout << "Dependencies to: ";
    utilities::printList(dependenciesTo);
}

int process::release() {
	return dependencies.size() == 0 ? READY : WAITING;
}

bool process::removeDependency(int id){
	dependencies.remove(id);

	return dependencies.size() == 0;
}
