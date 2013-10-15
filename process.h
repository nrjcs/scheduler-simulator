/********************************************************
 * process.h                                            *
 *                                                      *
 * Progetto Tipo 1 Sistemi in tempo Reale               *
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include <list>
#include <iostream>

class process {
    public:
        process();
        process(int id, int releasetime, int deadline, int executiontime, std::list<int>& dependencies); //construct
        void addProcessInWhenExecuted(int id);
        bool executeOneStep();
        std::list<int> listDependencies();
        void printProcess();
        bool removeDependency(int id);
    private:
        int releaseTime;
        int deadline;
        int state;
        int executionTime;
        int executedTime;
        int id;
        std::list<int> dependencies;
        std::list<int> whenExecuted;
        std::list<int> original_dependencies;
};
