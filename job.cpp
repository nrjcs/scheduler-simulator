/********************************************************
 * job.cpp                                              *
 *                                                      *
 * Corso Sistemi in tempo Reale               			*
 * Progetto Tipo 1	P3									*
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
	startTime = -1;
}

void job::addDependency(int _id) {
	dependenciesFrom.push_back(_id);
	dependenciesFromCopy.push_back(_id);
}

void job::alertThisJobWhenDone(int _id) {
	dependenciesTo.push_back(_id);
}

bool job::deadlineMet(){
	return completionTime <= deadline;
}

bool job::executeOneStep(int executionStep){
	if(executedTime == 0)
		startTime = executionStep;

	if(++executedTime == executionTime) {
		completionTime = executionStep+1;
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
	return (releaseTime + executionTime) <= deadline;
}

std::list<int> job::getListDependenciesTo() {
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

		if(i == startTime)
			std::cout << "*";
		else
			std::cout << " ";

		if(i == completionTime-1)
			std::cout << "*";
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

	std::cout <<	" ## " << std::setw(2) << std::setfill(' ') << id << "  ## ";

	if(startTime>=0) {
		std::cout <<"Start time: " << startTime << "\t"
					"End time: " << completionTime << "\t\t";

		if(deadlineMet())
			std::cout << "Deadline met: YES\tLateness:" << deadline - completionTime << "\n";
		else
			std::cout << "Deadline met: NO\tTardiness: " << completionTime - deadline << "\n";
	}
	else {
		std::cout <<"NOT EXECUTED";
		if(dependenciesFromCopy.size() > 0) {
			std::cout << " (DEADLOCK)";
		}
		std::cout << '\n';
	}

	std::cout << " ######### ";

	if(startTime>=0)
		std::cout << "Response time: " << completionTime - releaseTime <<"\t";

	if(dependenciesFromCopy.size() > 0) {
		std::cout << "Dependencies: ";
		utilities::printList(dependenciesFromCopy);
		std::cout << "\n";
	}
	else
		std::cout << "\n\n";
}

int job::release() {
	return dependenciesFrom.empty() ? READY : WAITING;
}

bool job::removeDependency(int _id){
	dependenciesFrom.remove(_id);
	return dependenciesFrom.empty();
}
