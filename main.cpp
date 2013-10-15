/********************************************************
 * main.cpp                                             *
 *                                                      *
 * Progetto Tipo 1 Sistemi in tempo Reale               *
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include "processes.h"
#include <limits>

//add_process(int id, int releasetime, int deadline, int executiontime, std::list<int>& dependencies); //construct
enum { EXECUTED, INCOMING, READY, RUNNING, WAITING };

void printAllLists();
void printList2(std::list<int>& myList);
void printMap(std::map<int,std::list<int> > myMap);
void addToList(int processId,int whichList);
bool checkIncomingJobs();
void step();
bool executeStep();
void scheduler();
void swapList(int ProcessId, int fromList, int toList);
bool preemptive = false;
bool processorsInIdle();

int stepClock = -1;
std::map<int,std::list<int> > incomingProcesses; // step number and list of incoming processes
std::list<int> readyProcesses;
std::list<int> runningProcesses;
std::list<int> waitingProcesses;
std::list<int> executedJobs;
processes allProcesses;

int main(int argc, char** argv){
	//initialising everything
	std::cout << "Initialising... \n";

    int myints[]= {1,2};
    int myints2[]= {0,2};
    std::list<int> test0(myints,myints+2);
    std::list<int> test1,test2,test3(myints2,myints2+2);
    runningProcesses.push_back(-1); //only one core;

    //Adding processes
    int id = 0;
    allProcesses.add_process(id,0,5,3,test0);
    addToList(id++,INCOMING);
    allProcesses.add_process(id,0,1,1,test1);
    addToList(id++,INCOMING);
    allProcesses.add_process(id,1,5,3,test2);
    addToList(id++,INCOMING);
    allProcesses.add_process(id,2,1,1,test3);
    addToList(id++,INCOMING);

    std::cout << "\n";
    //allProcesses.printProcesses();
    //printAllLists();

    step();

    return 0;
};

void wait() {
	std::cout << "Press ENTER to continue...\n";
	std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );
}

void addToList(int processId,int whichList){
    switch(whichList) {
    	case INCOMING: incomingProcesses[allProcesses.getReleaseTime(processId)].push_back(processId); break;
    	case READY: readyProcesses.push_back(processId); readyProcesses.sort(); break; //I want it to be always sorted
    	case WAITING: waitingProcesses.push_back(processId); break;
    }
}

bool checkIncomingJobs(){
	if(incomingProcesses[stepClock].size() > 0) {
		for (std::list<int>::iterator it = incomingProcesses[stepClock].begin(); it != incomingProcesses[stepClock].end(); it++) {
			std::cout << "ready now: " << *it << '\n';
			addToList(*it, READY);
		}

		readyProcesses.sort();

		return true;
	}
	return false;
}

void scheduler() {
	if((!preemptive && ! processorsInIdle()))
		return;

	if(preemptive)
		;
	else{
		for (std::list<int>::iterator it = runningProcesses.begin(); it != runningProcesses.end(); it++)
			if(*it == -1){
				swapList(readyProcesses.front(), READY, RUNNING);
			}
	}

}

void step() {
	bool callScheduler = false;
	callScheduler = executeStep();
	stepClock++;
	std::cout << "clock: " << stepClock << '\n';
	callScheduler = callScheduler || checkIncomingJobs();

	if(callScheduler)
		scheduler();
	wait();
	std::cout << "Processes running: ";
	printList2(runningProcesses);
	step();
}

bool executeStep(){
	bool somethingEnded = false;
	for (std::list<int>::iterator it = runningProcesses.begin(); it != runningProcesses.end(); it++){
		if(*it != -1) {
			bool jobEnded = allProcesses.executeOneStep(*it);
			std::cout << "process " << *it << " does one step";
			if(jobEnded) {
				std::cout << "job ended!";
				swapList(*it, RUNNING, EXECUTED);
				somethingEnded = true;
			}
		}
	}
	return somethingEnded;
}

bool processorsInIdle(){
	for (std::list<int>::iterator it = runningProcesses.begin(); it != runningProcesses.end(); it++)
		if(*it == -1)
			return true;

	return false;
}

void swapList(int processId, int from, int to){
	switch(from) {
		case RUNNING:
			for (std::list<int>::iterator it = runningProcesses.begin(); it != runningProcesses.end(); it++) {
	        	if(*it == processId)
	        		*it = -1;
	        	break;
			} break;
		case READY: readyProcesses.remove(processId); break;
		case WAITING: waitingProcesses.remove(processId); break;
	}

	switch(to) {
		case RUNNING:
			for (std::list<int>::iterator it = runningProcesses.begin(); it != runningProcesses.end(); it++) {
				if(*it == -1) {
					*it = processId;
					break;
				}
			}
			allProcesses.changeStatus(processId,RUNNING);
			break;
		case READY: readyProcesses.push_back(processId); readyProcesses.sort(); break;
		case WAITING: waitingProcesses.push_back(processId); break;
	}
}

void printAllLists() {
	std::cout << "Processes ready: ";
	printList2(readyProcesses);

	std::cout << "Processes incoming: \n";
	printMap(incomingProcesses);

	std::cout << "Processes running: ";
	printList2(runningProcesses);

	std::cout << "Processes waiting: ";
	printList2(waitingProcesses);
}

void printList2(std::list<int>& myList) {
	for (std::list<int>::iterator it = myList.begin(); it != myList.end(); it++)
        std::cout << *it << " ";
    std::cout << '\n';
}

void printMap(std::map<int,std::list<int> > myMap) {
	for (std::map<int,std::list<int> >::iterator it = myMap.begin(); it != myMap.end(); it++) {
		std::cout << " release time: " << it->first << " processes: ";
		printList2((it->second));
	}
}
