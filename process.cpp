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

std::list<int> process::listDependenciesFrom() {
	return dependenciesFrom;
}

std::list<int> process::listDependenciesTo() {
	return dependenciesTo;
}

void process::printProcess(){
    std::cout << "Process id: " << id << '\n';

    std::cout << "Dependencies from: ";
    utilities::printList(dependenciesFrom);

    std::cout << "Dependencies to: ";
    utilities::printList(dependenciesTo);
}

int process::release() {
	return dependenciesFrom.empty() ? READY : WAITING;
}

bool process::removeDependency(int id){
	dependenciesFrom.remove(id);

	return dependenciesFrom.empty();
}
