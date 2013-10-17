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
        process(); //construct
        void initialise(int id, int releasetime, int deadline, int executiontime);
        void addDependency(int id);
        void addProcessInWhenExecuted(int id);
        bool executeOneStep();
        int getReleaseTime();
        void printDependenciesFrom();
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
        std::list<int> dependenciesFrom;
        std::list<int> dependenciesTo;
};
