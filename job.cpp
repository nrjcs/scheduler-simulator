/********************************************************
 * job.cpp                                              *
 *                                                      *
 * Progetto Tipo 1 Sistemi in tempo Reale               *
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include "job.h"
#include <sstream>

enum { EXECUTED, INCOMING, READY, RUNNING, WAITING };

job::job() {
	completionTime = -1;
	deadline = -1;
	executionTime = -1;
	executedTime = 0;
	id = -1;
	releaseTime = -1;
	responseTime = -1;
}

void job::addDependency(int _id) {
	dependenciesFrom.push_back(_id);
}

void job::alertThisJobWhenDone(int _id) {
	dependenciesTo.push_back(_id);
}

bool job::deadlineMet(){
	return completionTime < deadline;
}

bool job::executeOneStep(int executionStep){
	if(executedTime == 0) {
//		timeline.push_back (5);
		responseTime = executionStep;
	}

	if(++executedTime == executionTime) {
		completionTime = executionStep;
		return true;
	}
	return false;
}

void job::initialise(int _id, int _releaseTime, int _deadline, int _executionTime){
	id = _id;
    releaseTime = _releaseTime;
    deadline = _deadline;
    executionTime = _executionTime;
}

bool job::isFeasible(){
	return (releaseTime + executionTime) < deadline;
}

void job::printDependenciesFrom() {
	std::cout << "Process " << id << " has these dependencies: ";
	utilities::printList(dependenciesFrom);
}

std::list<int> job::listDependenciesTo() {
	return dependenciesTo;
}

int max(int a, int b) {
	if(a>=b)
		return a;
	return b;
}

void job::plotTimeline(){
	// printing process id
	std::cout << " <" << std::setw(2) << std::setfill('0') << id << ">: ";

	// plotting timeline
	for (int i = 0; i <= max(deadline,completionTime); i++){
		if(i == releaseTime || i == deadline)
			std::cout << "^";
		else
			std::cout << " ";

		if(i == responseTime)
			std::cout << "$";
		else
			std::cout << " ";

		if(i == completionTime)
			std::cout << "$";
		else
			std::cout << " ";
	}
	std::cout << '\n';
}

void job::printStats() {
	std::cout << 	" ## JOB ## " <<
					"Release time: " << releaseTime << "\t"
					"Execution time: " << executionTime << "\t"
					"Deadline: before " << deadline << "\t";
	if(isFeasible())
		std::cout <<	"Feasible interval: " << deadline - releaseTime << "\n";
	else
		std::cout <<	"UNFEASIBLE\n";

	std::cout <<	" ## " << std::setw(2) << std::setfill(' ') << id << "  ## "
					"Response time: " << responseTime << "\t"
					"Completion time: " << completionTime << "\t";

	if(deadlineMet())
		std::cout << "Deadline met: YES\tLateness:" << deadline - completionTime;
	else
		std::cout << "Deadline met: NO\tTardiness: " << completionTime - deadline;

	std::cout << "\n\n";
}

int job::release() {
	return dependenciesFrom.empty() ? READY : WAITING;
}

bool job::removeDependency(int _id){
	dependenciesFrom.remove(_id);
	return dependenciesFrom.empty();
}
