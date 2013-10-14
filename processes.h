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
        bool executeOneStep(int process_id);
        bool removeDependency(int from_process_id, int process_id);
    private:
        std::map<int,process> processes_map;
};
