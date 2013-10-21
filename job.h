/********************************************************
 * job.h                                                *
 *                                                      *
 * Corso Sistemi in tempo Reale               			*
 * Progetto Tipo 1	P3									*
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include "utilities.h"

class job {
    public:
		job(); 																			//construct
        void initialise(int _id, int _releaseTime, int _deadline, int _executionTime);	//set essential parameters
        bool isFeasible();																//returns whether the job is feasible or not
        void addDependency(int id);														//add dependency of another job
        void alertThisJobWhenDone(int id);												//add this job to his dependenciesTo
        bool deadlineMet();																//returns true if the deadline was met
        bool executeOneStep(int executionStep);											//tells the job to do one execution step, then returns true if the job is now completed
        std::list<int> getListDependenciesTo();											//returns the list of jobs that are awaiting his execution
        void plotTimeline();															//plots the job's timeline
        void printStats();																//prints the job's parameters
        int release();																	//simulate the job release, it returns whether it is ready or it must wait some other jobs prior execution
        bool removeDependency(int id);													//remove the input job from his dependencies, returns whether now it is ready or must wait some other jobs prior execution
    private:
        int completionTime;  															//set at the end of his execution, tells you when the job finished
        int deadline;  																	//set on initialisation, tells you the job's deadline
        int executionTime;																//set on initialisation, tells you how many steps the job takes to complete
        int executedTime;																//tells you how many steps the job already did
        int id;																			//set on initialization, it's the job id
        int releaseTime;																//set on initialization, tells you when the job is released
        int startTime;																	//tells you when the jobs started its execution
        std::list<int> dependenciesFrom;												//set on initialization, tells you which jobs our job must wait prior execution
        std::list<int> dependenciesFromCopy;											//set on initialization, tells you which jobs our job must wait prior execution
        std::list<int> dependenciesTo;													//when executed, the job alert these jobs that his execution is complete
};
