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
std::vector<int> getRunningProcesses();

bool preemptive;
int clockStep = -1;
std::vector<processor> processors;
std::vector<process> processes;

int main(int argc, char** argv){
	//declaring everything
	int processorsNumber, processesNumber;


	//initialising everything
	std::cout << "Initialising... \n";
	preemptive = false;
	processorsNumber = 1;
	processesNumber = 4;
	processors.assign(processorsNumber, processor());
	processes.assign(processesNumber, process());

	//Initializing processes
    int myints[]= {1,2};
    int myints2[]= {0,2};
    std::list<int> test0(myints,myints+2);
    std::list<int> test1,test2,test3(myints2,myints2+2);

    int id = 1;
    int releaseTime = 0;
    processes[id].initialise(id,releaseTime,5,3,test0);
    incomingProcessesMap[releaseTime].push_back(id++);
    processes[id].initialise(id,releaseTime,1,1,test1);
    incomingProcessesMap[releaseTime].push_back(id++);

    releaseTime = 2;
    processes[id].initialise(id,releaseTime,5,3,test2);
    incomingProcessesMap[releaseTime].push_back(id++);

    releaseTime = 3;
    processes[id].initialise(id,releaseTime,1,1,test3);
    incomingProcessesMap[releaseTime].push_back(id++);

    //printAllLists();
    std::cout << "\n";

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
			std::cout << "job " << *it << " released \n";
			addToList(*it, processes[*it].release());
		}
		return true;
	}
	return false;
}

std::vector<int> getRunningProcesses(){
	std::vector<int> runningProcesses;
	for(std::vector<processor>::size_type i = 0; i != processors.size(); ++i)
		runningProcesses[i] = processors[i].getProcess();
	return runningProcesses;
}

void scheduler() {
	if(readyProcessesList.size() == 0) return; //no processes ready, no party

	std::vector<int> runningProcesses = getRunningProcesses();

	if(preemptive)
		for(std::vector<processor>::size_type i = 0; i != processors.size(); ++i)
			;
	else
		for(std::vector<processor>::size_type i = 0; (i != processors.size()) && readyProcessesList.size() > 0; ++i) {
			processRunning = processors[i].getProcess();
			if(processRunning == -1){
				processor[i].setProcess
			}

		//runningProcesses[i] = processors[i].getProcess();
//		for (std::list<int>::iterator it = runningProcesses.begin(); it != runningProcesses.end(); it++)
//			if(*it == -1){
//				swapList(readyProcesses.front(), READY, RUNNING);
//			}
//	}

}


void printProcessRunning(){
	std::cout << "Processes running: \n";
	for(std::vector<processor>::size_type i = 0; i != processors.size(); ++i)
		std::cout << "processor " << i << " is running: " << processors[i].getProcess() << '\n';
}

void step() {
	bool callScheduler = false;
	callScheduler = executeStep();
	clockStep++;
	std::cout << "Clock: " << clockStep << '\n';
	callScheduler = callScheduler || checkIncomingJobs();

	if(callScheduler)
		scheduler();
	//printProcessRunning();
	//printAllLists();
	wait();
	step();
}

bool executeStep(){
	bool somethingEnded = false;
	for(std::vector<processor>::size_type i = 0; i != processors.size(); ++i) {
		std::cout << "["<<i<<"] :";
		int processRunning = processors[i].executeStep();
		if(processRunning  != -1) {
			bool jobEnded = processes[processRunning].executeOneStep();
			std::cout << "process " << processRunning << " does one step\n";
			if(jobEnded) {
				std::cout << "job ended!\n";
				processors[i].setProcess(-1);
				addToList(processRunning, EXECUTED);
				std::list<int> list = processes[processRunning].listDependenciesTo();

				for (std::list<int>::size_type it2 =0; it2 != list.size(); it2++)
					if(processes[processRunning].removeDependency(it2) && isInList(processRunning,WAITING))
						swapList(it2, WAITING, READY);

				somethingEnded = true;
			}
		}
	}
	return somethingEnded;
}

