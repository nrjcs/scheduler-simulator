/********************************************************
 * main.cpp                                             *
 *                                                      *
 * Progetto Tipo 1 Sistemi in tempo Reale               *
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/

// to do: deadLock checker
#include "process.h"
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
unsigned readFromFile();
void scheduler();

bool preemptive;
int clockStep = -1;
std::vector<processor> processors;
std::vector<process> processes;

void printProcessorsHistory() {
	for(std::vector<processor>::size_type i = 0; i != processors.size(); ++i) {
			std::cout << "["<<i<<"]: ";
			processors[i].printHistory();
	}
}

int main(int argc, char** argv){
	//initialising everything
	unsigned processesNumber = readFromFile();

//	return 0;
//
//	//Initializing processes
//    int id = 0;
//    int releaseTime = 0;
//    processes[id].initialise(id,releaseTime,5,3);
//    processes[id].addDependency(3);
//    processes[3].addProcessInWhenExecuted(id);
//    processes[id].addDependency(2);
//    processes[2].addProcessInWhenExecuted(id);
//    incomingProcessesMap[releaseTime].push_back(id);
//
//    id++;
//    processes[id].initialise(id,releaseTime,1,8);
//    incomingProcessesMap[releaseTime].push_back(id);
//
//    id++;
//    releaseTime = 2;
//    processes[id].initialise(id,releaseTime,5,3);
//    incomingProcessesMap[releaseTime].push_back(id);
//
//    id++;
//    releaseTime = 3;
//    processes[id].initialise(id,releaseTime,1,3);
//    processes[id].addDependency(1);
//    processes[1].addProcessInWhenExecuted(id);
//    processes[id].addDependency(2);
//    processes[2].addProcessInWhenExecuted(id);
//    incomingProcessesMap[releaseTime].push_back(id);
//
//    id++;
//    releaseTime = 2;
//    processes[id].initialise(id,releaseTime,1,3);
//    processes[id].addDependency(1);
//    processes[1].addProcessInWhenExecuted(id);
//    incomingProcessesMap[releaseTime].push_back(id);
//
//    id++;
//	releaseTime = 0;
//	processes[id].initialise(id,releaseTime,1,10);
//    incomingProcessesMap[releaseTime].push_back(id);
//
//	id++;
//	releaseTime = 4;
//	processes[id].initialise(id,releaseTime,1,2);
//	processes[id].addDependency(1);
//	processes[1].addProcessInWhenExecuted(id);
//    incomingProcessesMap[releaseTime].push_back(id);
//
//	id++;
//	releaseTime = 6;
//	processes[id].initialise(id,releaseTime,1,9);
//	processes[id].addDependency(4);
//	processes[4].addProcessInWhenExecuted(id);
//    incomingProcessesMap[releaseTime].push_back(id);

    std::cout << "Starting Machine!\n";
    while(executedJobsList.size() < processesNumber) {
    	step();
//    	printProcessorsHistory();
    }

    printProcessorsHistory();

    return 0;
};

void wait() {
	std::cout << "Press ENTER to continue...\n";
	std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );
}


bool checkIncomingJobs(){
	if(incomingProcessesMap[clockStep].size() > 0) {
		for (std::list<int>::iterator it = incomingProcessesMap[clockStep].begin(); it != incomingProcessesMap[clockStep].end(); it++) {
			int temp = *it;
			std::cout << "Job " << temp << " released! \n";
			lists::addToList(temp, processes[temp].release());
		}
		return true;
	}
	return false;
}

void initialiseProcess(int processId,  std::istringstream& iss){
	int releaseTime, deadline, executionTime, temp;
	iss >> releaseTime;
	iss >> deadline;
	iss >> executionTime;

	processes[processId].initialise(processId,releaseTime, deadline, executionTime);
	while (iss >> temp) {
		processes[processId].addDependency(temp);
		processes[temp].addProcessInWhenExecuted(processId);
	}

	incomingProcessesMap[releaseTime].push_back(processId);
}

unsigned readFromFile() {
	std::cout << "Initialising machine... \n";
	unsigned processorsNumber, processesNumber;
	std::ifstream myFile("input");


	int temp, processId = -1, lineNumber = -1;
	std::string line;

	while (std::getline(myFile, line))
	{
		std::istringstream iss(line);
		switch(++lineNumber) {
			case 0: iss >> temp; preemptive = temp; break;
			case 1: iss >> processorsNumber; processors.assign(processorsNumber, processor()); break;
			case 2: iss >> processesNumber; processes.assign(processesNumber, process()); break;
			default: initialiseProcess(++processId,iss);
		}
	}
	return processesNumber;
	//std::cout << "preemptive!" << a << '\n';
}

void scheduler() {
	if(readyProcessesList.empty()) return; //no processes ready, no party

	if(preemptive)
		std::cout << "preemptive!\n";
	else {
		for(std::vector<processor>::size_type i = 0; (i != processors.size()) && !readyProcessesList.empty(); ++i) {
			if(processors[i].getProcess() == -1){
				processors[i].setProcess(readyProcessesList.front());
				readyProcessesList.pop_front();
			}
		}
	}
}


void printProcessRunning(){
	std::cout << "Processes running: \n";
	for(std::vector<processor>::size_type i = 0; i != processors.size(); ++i)
		std::cout << "processor " << i << " is running: " << processors[i].getProcess() << '\n';
}

void step() {
	clockStep++;
	//std::cout << "Clock: " << clockStep << '\n';

	if(checkIncomingJobs())
		scheduler();

	if(executeStep()) //returns true if one or more processes end!
		scheduler();

//	printProcessRunning();
//	printAllLists();
//	wait();

}

bool executeStep(){
	bool somethingEnded = false;
	for(std::vector<processor>::size_type i = 0; i != processors.size(); ++i) {
		int processRunning = processors[i].executeStep();
		if(processRunning  != -1) {
			if(processes[processRunning].executeOneStep()) { //returns true when the job ends
				//std::cout << " job " << processRunning << " ended!\n";
				processors[i].setProcess(-1);
				addToList(processRunning, EXECUTED);

				//std::cout << "Jobs executed: ";
				//utilities::printList(executedJobsList);

				std::list<int> listDependenciesTo = processes[processRunning].listDependenciesTo();

				for (std::list<int>::iterator it = listDependenciesTo.begin(); it != listDependenciesTo.end(); it++) {
					//std::cout << " removeDependency to "<< *it << "\n";
					if( processes[*it].removeDependency(processRunning) )
						if(isInList(*it,WAITING))
							swapList(*it, WAITING, READY);
				}

				somethingEnded = true;
			}
		}
	}
	return somethingEnded;
}

