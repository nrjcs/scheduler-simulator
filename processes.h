/********************************************************
 * processes.h                                          *
 *                                                      *
 * Progetto Tipo 1 Sistemi in tempo Reale               *
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include "process.h"
#include <map>

class processes {
    public:
        processes(); //construct
        void add_process(int id, int releasetime, int deadline, int executiontime, std::list<int>& dependencies);
        void changeStatus(int processId, int status);
        int getReleaseTime(int processId);
        std::list<int> getListDependenciesTo(int processId);
        bool executeOneStep(int processId);
        void printProcesses();
        int release(int processId);
        bool removeDependency(int from_processId, int processId);
    private:
        void addProcessInWhenExecuted(int whichProcess, int intoWhichProcess);
        std::map<int,process> processes_map;
};
