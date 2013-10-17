/********************************************************
 * main.cpp                                             *
 *                                                      *
 * Progetto Tipo 1 Sistemi in tempo Reale               *
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include "process.h"
#include "processor.h"
#include "lists.h"
#include <limits>
#include <vector>
using namespace lists;
//add_process(int id, int releasetime, int deadline, int executiontime, std::list<int>& dependencies); //construct
enum { EXECUTED, INCOMING, READY, RUNNING, WAITING };

void step();
bool executeStep();
void scheduler();

bool preemptive;
int clockStep = -1;
std::vector<processor> processors;
std::vector<process> processes;

int main(int argc, char** argv){
	//declaring everything
	unsigned processorsNumber, processesNumber;


	//initialising everything
	std::cout << "Initialising machine... \n";
	preemptive = false;
	processorsNumber = 1;
	processesNumber = 4;
	processors.assign(processorsNumber, processor());
	processes.assign(processesNumber, process());

	std::cout << "Initialising jobs.. \n";
	//Initializing processes
    int id = 1;
    int releaseTime = 0;
    processes[id].initialise(id,releaseTime,5,3);
    processes[id].addDependency(3);
    processes[id].addDependency(2);
    incomingProcessesMap[releaseTime].push_back(id);

    id = 2;
    processes[id].initialise(id,releaseTime,1,1);
    incomingProcessesMap[releaseTime].push_back(id);

    id = 3;
    releaseTime = 2;
    processes[id].initialise(id,releaseTime,5,3);
    incomingProcessesMap[releaseTime].push_back(id);

    id = 4;
    releaseTime = 3;
    processes[id].initialise(id,releaseTime,1,1);
    processes[id].addDependency(1);
    processes[id].addDependency(2);
    incomingProcessesMap[releaseTime].push_back(id++);

    while(executedJobsList.size() < processesNumber)
    	step();

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
			//std::cout << "Job " << temp << " released! \n";
			lists::addToList(temp, processes[temp].release());
		}
		return true;
	}
	return false;
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
	std::cout << "Clock: " << clockStep << '\n';

	if(checkIncomingJobs())
		scheduler();

	if(executeStep()) //returns true if one or more processes end!
		scheduler();

	printProcessRunning();
	printAllLists();
	wait();

}

bool executeStep(){
	bool somethingEnded = false;
	for(std::vector<processor>::size_type i = 0; i != processors.size(); ++i) {
		std::cout << "["<<i<<"]: ";
		int processRunning = processors[i].executeStep();
		if(processRunning  != -1) {
			if(processes[processRunning].executeOneStep()) { //returns true when the job ends
				std::cout << "job " << processRunning << " ended!\n";
				processors[i].setProcess(-1);
				addToList(processRunning, EXECUTED);
				std::list<int> listDependenciesTo = processes[processRunning].listDependenciesTo();

				for (std::list<int>::size_type j = 0; j != listDependenciesTo.size(); ++j)
					if( processes[(listDependenciesTo[j])].removeDependency(processRunning) ) ;
//						;if(isInList(listDependenciesTo[j],WAITING))
//							swapList(listDependenciesTo[j], WAITING, READY);

				somethingEnded = true;
			}
		}
	}
	return somethingEnded;
}

