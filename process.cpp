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
#include <sstream>

enum { EXECUTED, INCOMING, READY, RUNNING, WAITING };

process::process() {
	completionTime = -1;
	deadline = -1;
	executionTime = -1;
	executedTime = 0;
	id = -1;
	releaseTime = -1;
	responseTime = -1;
}

void process::addDependency(int _id) {
	//std::cout << "adding " << _id << " to " << id << "\n";
	dependenciesFrom.push_back(_id);
}

void process::alertThisJobWhenDone(int _id) {
	dependenciesTo.push_back(_id);
}

bool process::deadlineMet(){
	return completionTime < deadline;
}

bool process::executeOneStep(int executionStep){
	if(executedTime == 0)
		responseTime = executionStep;

	if(++executedTime == executionTime) {
		completionTime = executionStep;
		return true;
	}
	return false;
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

int max(int a, int b) {
	if(a>=b)
		return a;
	return b;
}

void process::plotTimeline(){
	// printing process id
	if(id < 10)
		std::cout << " <0" << id << ">: ";
	else
		std::cout << " <" << id << ">: ";

	// plotting timeline
	for (int i = 0; i <= max(deadline,completionTime); i++){
		if(i == releaseTime || i == deadline)
			std::cout << "^";
		else
			std::cout << " ";

		if(i == responseTime)
			std::cout << "*";
		else
			std::cout << " ";

		if(i == completionTime)
			std::cout << "*";
		else
			std::cout << " ";
	}
	std::cout << '\n';
}

void process::printStats() {
	std::cout << "Job " << id << ":\n";
	std::cout << " execution time: " << executionTime << '\n';
	std::cout << " release time: " << releaseTime << '\n';
	std::cout << " deadline: before " << deadline << '\n';
	std::cout << " response time: " << responseTime << '\n';
	std::cout << " completion time: " << completionTime << '\n';

	if(deadlineMet())
		std::cout << " deadline met: YES\n";
	else
		std::cout << " deadline met: NO\n";

	std::cout << '\n';
}

int process::release() {
	return dependenciesFrom.empty() ? READY : WAITING;
}

bool process::removeDependency(int _id){
	dependenciesFrom.remove(_id);
	return dependenciesFrom.empty();
}
