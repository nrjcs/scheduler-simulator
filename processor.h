/********************************************************
 * processor.h                                          *
 *                                                      *
 * Progetto Tipo 1 Sistemi in tempo Reale               *
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include "utilities.h"

class processor {
    public:
        processor();						//construct
        int executeStep();					//simulate one execution cycle
        int getProcess();					//returns its dedicated job
        void initialise(int _id);			//set essential parameters
        void printTimeline();				//prints the execution timeline of the processor
        void setProcess(int processId);		//set a new running processor
    private:
        int id;								//defined on initialization, it's the processor id
        int process;						//it contains its running job id
        std::vector<int> timeline;			//for visualisation purposes, it's the current processor execution timeline
};
