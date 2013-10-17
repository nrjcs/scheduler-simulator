/********************************************************
 * process.h                                            *
 *                                                      *
 * Progetto Tipo 1 Sistemi in tempo Reale               *
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include "utilities.h"

class process {
    public:
        process();
        void initialise(int id, int releasetime, int deadline, int executiontime, std::list<int>& dependencies); //construct
        void addProcessInWhenExecuted(int id);
        bool executeOneStep();
        int getReleaseTime();
        std::list<int> listDependenciesFrom();
        std::list<int> listDependenciesTo();
        void printProcess();
        int release();
        bool removeDependency(int id);
    private:
        int releaseTime;
        int deadline;
        int executionTime;
        int executedTime;
        int id;
        std::list<int> dependencies;
        std::list<int> dependenciesTo;
        std::list<int> original_dependencies;
};
