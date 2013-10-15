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

//add_process(int id, int releasetime, int deadline, int executiontime, std::list<int>& dependencies); //construct
enum { EXECUTED, INCOMING, READY, RUNNING, WAITING };

void printList2(std::list<int>& myList) {
	for (std::list<int>::iterator it = myList.begin(); it != myList.end(); it++)
        std::cout << *it << " ";
    std::cout << '\n';
}

void printAllLists();
void addToList(int processId,int whichList);

int stepClock = -1;
std::map<int,std::list<int> > incomingProcesses; // step number and list of incoming processes
std::list<int> readyProcesses;
std::list<int> runningProcesses;
std::list<int> waitingProcesses;
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
    printAllLists();

    return 0;
};

void addToList(int processId,int whichList){
    switch(whichList) {
    	case INCOMING: incomingProcesses[allProcesses.getReleaseTime(processId)].push_back(processId); break;
    	case READY: readyProcesses.push_back(processId); readyProcesses.sort(); break; //I want it to be always sorted
    	case WAITING: waitingProcesses.push_back(processId); break;
    }
}

void printMap(std::map<int,std::list<int> > myMap) {
	for (std::map<int,std::list<int> >::iterator it = myMap.begin(); it != myMap.end(); it++) {
		std::cout << " release time: " << it->first << " processes: ";
		printList2((it->second));
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
