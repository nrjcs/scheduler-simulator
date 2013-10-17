/********************************************************
 * processor.h                                          *
 *                                                      *
 * Progetto Tipo 1 Sistemi in tempo Reale               *
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include <vector>
#include <iostream>

class processor {
    public:
        processor();
        int executeStep();
        int getProcess();
        void printHistory();
        void setProcess(int processId);
    private:
        int process;
        std::vector<int> history;
};
