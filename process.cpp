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
	status = -1;
	releaseTime = -1;
	deadline = -1;
	executionTime = -1;
	executedTime = -1;
}

void process::addProcessInWhenExecuted(int _id) {
	dependenciesTo.push_back(_id);
}

void process::execute(){
	status = RUNNING;

	std::cout << "Process " << id << " now running\n";
}
bool process::executeOneStep(){
	if(status != RUNNING) {
		std::cout << "ERROR: trying to execute a process (" << id << ") with status: " << status;
		return false;
	}

    if(++executedTime == executionTime) {
    	status = EXECUTED;
    	return true;
    }
    return false;
}

int process::getReleaseTime(){
	return releaseTime;
}

int process::initialise(int _id, int _releaseTime, int _deadline, int _executionTime, std::list<int>& _dependencies){
    id = _id;
    releaseTime = _releaseTime;
    deadline = _deadline;
    executionTime = _executionTime;
    dependencies = _dependencies;

    //making a copy of the list
    for (std::list<int>::iterator it = dependencies.begin(); it != dependencies.end(); it++)
        original_dependencies.push_back(*it);

    status = INCOMING;
    executedTime = 0;

    return status;
}
std::list<int> process::listDependenciesFrom() {
	return dependencies;
}

std::list<int> process::listDependenciesTo() {
	return dependenciesTo;
}

void process::preempt(){
	status = READY;
}

void process::printProcess(){
    std::cout << "Process id: " << id << " status: ";

    switch(status){
    	case EXECUTED: std::cout << "executed\n"; break;
    	case INCOMING: std::cout << "incoming\n"; break;
    	case READY: std::cout << "ready\n"; break;
    	case RUNNING: std::cout << "running\n"; break;
    	case WAITING: std::cout << "waiting\n"; break;
    	default: std::cout << "NONE\n";
    }

    std::cout << "Dependencies from: ";
    utilities::printList(original_dependencies);

    std::cout << "Dependencies to: ";
    utilities::printList(dependenciesTo);
}

int process::release() {
	status = dependencies.size() == 0 ? READY : WAITING;
	return status;
}

bool process::removeDependency(int id){
	dependencies.remove(id);
	if(dependencies.size() == 0 && status == WAITING) {
		status = READY;
		return true;
	}
	return false;
}
