/********************************************************
 * processor.h                                          *
 *                                                      *
 * Corso Sistemi in tempo Reale               			*
 * Progetto Tipo 1	P3									*
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
        int getJob();						//returns its dedicated job
        void initialise(int _id);			//set essential parameters
        void printTimeline();				//prints the execution timeline of the processor
        void setJob(int jobId);				//set a new running job
    private:
        int id;								//defined on initialization, it's the processor id
        int job;							//it contains its running job id
        std::vector<int> timeline;			//for visualisation purposes, it's the current processor execution timeline
};
