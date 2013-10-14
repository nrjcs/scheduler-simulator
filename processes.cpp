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
    processes_map[id] = process(releasetime, deadline, executiontime, dependencies);
    std::cout << "Process " << id << " inserted (Total size: " << processes_map.size() << ")\n";
}

bool processes::executeOneStep(int id) {
    // processes_map.size();
    // return true;
    return processes_map[id].executeOneStep();
}

// bool processes::removeDependency(int from, int id) {
//     return processes_map[from].removeDependency(id);
// }
