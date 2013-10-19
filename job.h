/********************************************************
 * job.h                                                *
 *                                                      *
 * Progetto Tipo 1 Sistemi in tempo Reale               *
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include "utilities.h"

class job {
    public:
		job(); 																		//construct
        void initialise(int _id, int _releaseTime, int _deadline, int _executionTime);	//set essential parameters
        void addDependency(int id);														//add dependency of another job
        void alertThisJobWhenDone(int id);												//add this job to his dependenciesTo
        bool deadlineMet();																//returns true if the deadline was met
        bool executeOneStep(int executionStep);											//tells the job to do one execution step, then returns true if the job is now completed
        void printDependenciesFrom();													//[TO DELETE] print the jobs dependencies
        std::list<int> listDependenciesTo();											//returns the list of jobs that are awaiting his execution
        void plotTimeline();															//plots the job's timeline
        void printStats();																//prints the job's parameters
        int release();																	//simulate the job release, it returns whether it is ready or it must wait some other jobs prior execution
        bool removeDependency(int id);													//remove the input job from his dependencies, returns whether now it is ready or must wait some other jobs prior execution
    private:
        int completionTime;  															//defined at the end of his execution, tells you when the job finished
        int deadline;  																	//defined on initialisation, tells you the job's deadline
        int executionTime;																//defined on initialisation, tells you how many steps the job takes to complete
        int executedTime;																//tells you how many steps the job already did
        int id;																			//defined on initialization, it's the job id
        int releaseTime;																//defined on initialization, tells you when the job is released
        int responseTime;																//tells you when the jobs got executed the first time
        std::list<int> dependenciesFrom;												//defined on initialization, tells you which jobs our job must wait prior execution
        std::list<int> dependenciesTo;													//when executed, the job alert these jobs that his execution is complete
};
