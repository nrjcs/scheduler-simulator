/********************************************************
 * lists.cpp                                            *
 *                                                      *
 * Progetto Tipo 1 Sistemi in tempo Reale               *
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include "lists.h"

namespace lists {
	enum { EXECUTED, INCOMING, READY, RUNNING, WAITING };

	std::map<int,std::list<int> > incomingProcessesMap; // step number and list of incoming processes
	std::list<int> readyProcessesList;
	std::list<int> waitingProcessesList;
	std::list<int> executedJobsList;

	void addToList(int processId,int whichList){
		switch(whichList) {
			case READY: readyProcessesList.push_back(processId); readyProcessesList.sort(); break; //I want this list always sorted
			case WAITING: waitingProcessesList.push_back(processId); break;
		}
	}

	void printAllLists() {
		std::cout << "Processes ready: ";
		utilities::printList(readyProcessesList);

		std::cout << "Processes incoming: \n";
		utilities::printIncomingMap(incomingProcessesMap);

		std::cout << "Processes waiting: ";
		utilities::printList(waitingProcessesList);
	}

	void removeFromReady(int processId){
		readyProcessesList.remove(processId);
	}

	void swapList(int processId, int from, int to){
		switch(from) {
			case READY: readyProcessesList.remove(processId); break;
			case WAITING: waitingProcessesList.remove(processId); break;
		}

		switch(to) {
			case READY: readyProcessesList.push_back(processId); readyProcessesList.sort(); break;
			case WAITING: waitingProcessesList.push_back(processId); break;
		}
	}
}
