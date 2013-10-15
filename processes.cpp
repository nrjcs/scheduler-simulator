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

processes::processes() {
    std::cout << "Map created\n";
};

void processes::add_process(int id, int releasetime, int deadline, int executiontime, std::list<int>& dependencies){
    processes_map[id] = process(id, releasetime, deadline, executiontime, dependencies);

    std::list<int> Dependencieslist = processes_map[id].listDependencies();

    std::cout << "Processes to add to others:\n";
    for (std::list<int>::iterator it = Dependencieslist.begin(); it != Dependencieslist.end(); it++)
          std::cout << *it << ' ';
    std::cout << '\n';

    std::cout << "Process " << id << " inserted (Total size: " << processes_map.size() << ")\n";
}

void processes::addProcessInWhenExecuted(int whichProcess, int intoWhichProcess) {
	processes_map[intoWhichProcess].addProcessInWhenExecuted(whichProcess);
}


bool processes::executeOneStep(int id) {
    return processes_map[id].executeOneStep();
}

 bool processes::removeDependency(int from, int id) {
     return processes_map[from].removeDependency(id);
 }
