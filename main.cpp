/********************************************************
 * main.cpp                                             *
 *                                                      *
 * Progetto Tipo 1 Sistemi in tempo Reale               *
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/

// to do: deadLock checker, check if deadline can be respected (if job is 'feasible')
#include "job.h"
#include "processor.h"
#include "lists.h"
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace lists;
enum { EXECUTED, INCOMING, READY, RUNNING, WAITING };

void step();
bool executeStep();
void printMachineTimeline();
unsigned readFromFile();
void scheduler();
void removeDependencies(int processId);

bool preemptive = true;
bool bestEffort = true;
int clockStep = -1;
std::vector<processor> processors;
std::vector<job> jobs;

int main(int argc, char** argv){
	//initialising everything
	unsigned jobsNumber = readFromFile();

    std::cout << "Starting machine...";

    while(executedJobsList.size() < jobsNumber)
    	step();

    std::cout << "...all done!\n\n";

    printMachineTimeline();

    return 0;
};

void wait() {
	std::cout << "Press ENTER to continue...\n";
	std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );
}

std::map<int,int> getProcessorsOrderedByPriority() {
	std::map<int,int> processorsOrderedByPriority;

	for(std::vector<processor>::size_type i = 0; i != processors.size(); ++i)
		processorsOrderedByPriority[processors[i].getProcess()] = i;

	return processorsOrderedByPriority;
}

bool checkIncomingJobs(){
	if(incomingProcessesMap[clockStep].size() > 0) {
		for (std::list<int>::iterator it = incomingProcessesMap[clockStep].begin(); it != incomingProcessesMap[clockStep].end(); it++) {
			int temp = *it;
			lists::addToList(temp, jobs[temp].release());
		}
		return true;
	}
	return false;
}

void initialiseProcess(int jobId,  std::istringstream& iss){
	int releaseTime, deadline, executionTime, temp;
	iss >> releaseTime;
	iss >> deadline;
	iss >> executionTime;

	jobs[jobId].initialise(jobId,releaseTime, deadline, executionTime);
	if((!bestEffort) && (!jobs[jobId].isFeasible())){
		removeDependencies(jobId);
		addToList(jobId, EXECUTED);
	}
	else{
		while (iss >> temp) {
			if(!isInList(temp, EXECUTED)) {//if the job isn't executed yet
				jobs[jobId].addDependency(temp);
				jobs[temp].alertThisJobWhenDone(jobId);
			}
		}
		incomingProcessesMap[releaseTime].push_back(jobId);
	}
}

unsigned readFromFile() {
	std::cout << "Initialising machine...\n\nMachine statistics\n";
	unsigned processorsNumber, processesNumber;
	std::ifstream myFile("input");

	int processId = -1, lineNumber = -1;
	std::string line;

	while (std::getline(myFile, line))
	{
		int temp;
		std::istringstream iss(line);
		switch(++lineNumber) {
			case 0:
				iss >> temp;
				if(temp == 0){
					preemptive = false;
					std::cout << " -Non-preemptive;\n";
				}
				else
					std::cout << " -Preemptive;\n";

				break;
			case 1:
				iss >> temp;
				if(temp == 0){
					bestEffort = false;
					std::cout << " -Non best effort (doesn't execute unfeasible jobs);\n";
				}
				else
					std::cout << " -Best effort (executes unfeasible jobs);\n";
				break;
			case 2:
				iss >> processorsNumber;
				std::cout << " -Processors: " << processorsNumber << ";\n";
				processors.assign(processorsNumber, processor());
				for(unsigned i = 0; i < processorsNumber; i++)
					processors[i].initialise(i+1);
				break;
			case 3:
				iss >> processesNumber;
				std::cout << " -Jobs: " << processesNumber << ";\n\n";
				jobs.assign(processesNumber, job());
				break;
			default: initialiseProcess(++processId,iss);
		}
	}
	return processesNumber;
}

void scheduler() {
	if(readyProcessesList.empty()) return; //no processes ready, no party
	if(preemptive) {
		std::map<int,int> myMap = getProcessorsOrderedByPriority();
		for (std::map<int,int>::iterator it = myMap.begin(); it != myMap.end() && !readyProcessesList.empty(); it++)
			if(it->first < 0 || it->first > readyProcessesList.front()) {
				if(it->first >= 0)
					addToList(it->first, READY);
				processors[it->second].setProcess(readyProcessesList.front());
				readyProcessesList.pop_front();
			}
			else break;
	}
	else {
		for(std::vector<processor>::size_type i = 0; (i != processors.size()) && !readyProcessesList.empty(); ++i) {
			if(processors[i].getProcess() < 0){
				processors[i].setProcess(readyProcessesList.front());
				readyProcessesList.pop_front();
			}
		}
	}
}

void printMachineTimeline() {
	std::cout << 	"Machine timeline \n\n"
				 	" ######## [] indicates processors, <> indicates jobs \n"
					" #LEGEND# $ indicates the release time and the deadline \n"
					" ######## * indicates the response and completion time \n\n";

	std::cout << " TIME  ";
	for(int i=0; i<= clockStep; i++)
		std::cout << std::setw(2) << std::setfill('0') << i << " ";

	std::cout << '\n' << "      ";

	for(int i=0; i<= clockStep; i++)
		std::cout << " | ";
	std::cout << "\n";

	for(std::vector<processor>::size_type i = 0; i != processors.size(); ++i)
		processors[i].printTimeline();

	for(std::vector<job>::size_type i = 0; i != jobs.size(); ++i)
		jobs[i].plotTimeline();

//	return;
//	wait();
	std::cout << 	"\nJobs statistics\n";
	for(std::vector<job>::size_type i = 0; i != jobs.size(); ++i)
		jobs[i].printStats();
}

void step() {
	clockStep++;

	if(checkIncomingJobs())
		scheduler();

	if(executeStep()) //returns true if one or more processes end!
		scheduler();
}

bool executeStep(){
	bool somethingEnded = false;
	for(std::vector<processor>::size_type i = 0; i != processors.size(); ++i) {
		int processRunning = processors[i].executeStep();
		if(processRunning  != -1) {
			if(jobs[processRunning].executeOneStep(clockStep)) { //returns true when the job ends
				//std::cout << " job " << processRunning << " ended!\n";
				processors[i].setProcess(-1);
				addToList(processRunning, EXECUTED);

				removeDependencies(processRunning);

				somethingEnded = true;
			}
		}
	}
	return somethingEnded;
}

void removeDependencies(int processId) {
	std::list<int> listDependenciesTo = jobs[processId].listDependenciesTo();

	for (std::list<int>::iterator it = listDependenciesTo.begin(); it != listDependenciesTo.end(); it++)
		if( jobs[*it].removeDependency(processId) )
			if(isInList(*it,WAITING))
				swapList(*it, WAITING, READY);
}
