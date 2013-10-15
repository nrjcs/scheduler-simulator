/********************************************************
 * processes.h                                          *
 *                                                      *
 * Progetto Tipo 1 Sistemi in tempo Reale               *
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include "processes.h"
enum { EXECUTED, INCOMING, READY, RUNNING, WAITING };

processes::processes() {
    //std::cout << "Map created\n";
};

void processes::add_process(int id, int releasetime, int deadline, int executiontime, std::list<int>& dependencies){
    std::cout << "Adding process " << id << "\n";
	processes_map[id].initialise(id, releasetime, deadline, executiontime, dependencies);

    std::list<int> Dependencieslist = processes_map[id].listDependenciesFrom();

    for (std::list<int>::iterator it = Dependencieslist.begin(); it != Dependencieslist.end(); it++)
    	addProcessInWhenExecuted(id,*it);
}

void processes::addProcessInWhenExecuted(int whichProcess, int intoWhichProcess) {
	std::cout << " adding priority " << intoWhichProcess << " < " << whichProcess << "\n";
	processes_map[intoWhichProcess].addProcessInWhenExecuted(whichProcess);
}

void processes::changeStatus(int processId, int status){
	if(status == RUNNING)
		processes_map[processId].execute();
}
bool processes::executeOneStep(int id) {
    return processes_map[id].executeOneStep();
}

std::list<int> processes::getListDependenciesTo(int processId) {
	return processes_map[processId].listDependenciesTo();
}

int processes::getReleaseTime(int id){
	return processes_map[id].getReleaseTime();
}

void processes::printProcesses() {
	for (std::map<int,process>::iterator it = processes_map.begin(); it != processes_map.end(); it++)
		(it->second).printProcess();
    std::cout << '\n';
}

int processes::release(int processId){
	return processes_map[processId].release();
}

bool processes::removeDependency(int from, int id) {
	return processes_map[from].removeDependency(id);
}
