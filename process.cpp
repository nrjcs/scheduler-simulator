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
	executedTime = 0;
}

void process::addDependency(int _id) {
	//std::cout << "adding " << _id << " to " << id << "\n";
	dependenciesFrom.push_back(_id);
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

void process::initialise(int _id, int _releaseTime, int _deadline, int _executionTime){
    id = _id;
    releaseTime = _releaseTime;
    deadline = _deadline;
    executionTime = _executionTime;
}

void process::printDependenciesFrom() {
	std::cout << "Process " << id << " has these dependencies: ";
	utilities::printList(dependenciesFrom);
}

std::list<int> process::listDependenciesTo() {
	return dependenciesTo;
}

void process::printProcess(){
    std::cout << "Process id: " << id << "\n release time: " << releaseTime << '\n';

    std::cout << " dependencies from: ";
    utilities::printList(dependenciesFrom);

    std::cout << " dependencies to: ";
    utilities::printList(dependenciesTo);
}

int process::release() {
	return dependenciesFrom.empty() ? READY : WAITING;
}

bool process::removeDependency(int _id){
//	std::cout << "Dependencies from: ";
//	utilities::printList(dependenciesFrom);
//	std::cout << " removing" << _id << "\n";
	dependenciesFrom.remove(_id);
//	std::cout << " removed\n";
	return dependenciesFrom.empty();
}
