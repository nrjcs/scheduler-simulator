/********************************************************
 * scheduler.cpp                                        *
 *                                                      *
 * Corso Sistemi in tempo Reale               			*
 * Progetto Tipo 1	P3									*
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include "scheduler.h"

enum { EXECUTED, INCOMING, READY, RUNNING, WAITING }; 	//jobs status

scheduler::scheduler(bool _preemptive, bool _bestEffort, std::vector<processor>& _processors, std::vector<job>& _jobs, int _unfeasibleJobsNumber) {
	// initialising parameters

	preemptive = _preemptive;
	bestEffort = _bestEffort;
	processors = _processors;
	jobs = _jobs;
	unfeasibleJobsNumber = _unfeasibleJobsNumber;
	totalJobsNumber = jobs.size();

	clockStep = -1;
	jobsThatNotMetTheirDeadline = 0;

    std::cout << "Starting machine...";

    //main loop
    while(executedJobsList.size() + waitingJobsList.size() < totalJobsNumber)
    	step();

    std::cout << "...all done!\n\n";

    //print report
    printReport();
}

bool scheduler::checkIncomingJobs(){

	bool thereAreNewReadyJobs = false;
	if(incomingJobsMap[clockStep].size() > 0) { //If there are new jobs
		for (std::list<int>::iterator it = incomingJobsMap[clockStep].begin(); it != incomingJobsMap[clockStep].end(); it++) {
			int temp = *it;
			if(jobs[temp].release() == READY){
				lists::addToList(temp, READY);
				thereAreNewReadyJobs = true;
			}
			else
				lists::addToList(temp, WAITING);
		}
	}
	return thereAreNewReadyJobs;
}

bool scheduler::executeStep(){
	bool somethingEnded = false; //if a job ended this function returns true
	for(std::vector<processor>::size_type i = 0; i != processors.size(); ++i) {
		int processRunning = processors[i].executeStep();
		if(processRunning  >= 0) {
			if(jobs[processRunning].executeOneStep(clockStep)) { //returns true when the job ends
				processors[i].setJob(-1); //remove job from processor
				addToList(processRunning, EXECUTED); //add job in executed jobs list
				jobsThatNotMetTheirDeadline += jobs[processRunning].deadlineMet() ? 0 : 1;
				removeDependencies(processRunning); // alerts other jobs about that the job finished

				somethingEnded = true; //for return porpouses
			}
		}
	}
	return somethingEnded;
}

std::map<int,int> scheduler::getProcessorsOrderedByJobId() {
	std::map<int,int> processorsOrderedByJobId;

	for(std::vector<processor>::size_type i = 0; i != processors.size(); ++i)
		processorsOrderedByJobId[processors[i].getJob()] = i;

	return processorsOrderedByJobId;
}

void scheduler::printMachineTimeline() {
	std::cout << 	"Machine timeline \n\n"
				 	"\t\t##########\t\t[] indicates processors, <> indicates jobs \n"
					"\t\t# LEGEND #\t\t^ indicates the release time and the deadline \n"
					"\t\t##########\t\t* indicates the start execution and end execution time \n\n";

	std::cout << " TIME  ";
	for(int i=0; i<= clockStep+1; i++)
		std::cout << std::setw(2) << std::setfill('0') << i << " ";

	std::cout << '\n' << "      ";

	for(int i=0; i<= clockStep+1; i++)
		std::cout << " | ";
	std::cout << "\n";

	for(std::vector<processor>::size_type i = 0; i != processors.size(); ++i)
		processors[i].printTimeline();

//	wait();

	for(std::vector<job>::size_type i = 0; i != jobs.size(); ++i)
		jobs[i].plotTimeline();

//	wait();

	std::cout << 	"\nJobs statistics\n\n";
	for(std::vector<job>::size_type i = 0; i != jobs.size(); ++i)
		jobs[i].printStats();
}

void scheduler::printReport() {
	std::cout << "################################################ REPORT ################################################\n\n";
	    if(waitingJobsList.size())
	    	std::cout << "The system finished early because " << waitingJobsList.size() << " jobs were in deadlock.\n";

	    if(unfeasibleJobsNumber>0){
	    	if(!bestEffort)
	    		if(unfeasibleJobsNumber == 1)
	    			std::cout << "There was " << unfeasibleJobsNumber << " unfeasible job (not executed).\n";
	    		else
	    			std::cout << "There were " << unfeasibleJobsNumber << " unfeasible jobs (not executed).\n";
	    	else
	    		if(unfeasibleJobsNumber == 1)
					std::cout << "There was " << unfeasibleJobsNumber << " unfeasible job (executed anyway).\n";
				else
					std::cout << "There were " << unfeasibleJobsNumber << " unfeasible jobs (executed anyway).\n";
	    }

	    if(jobsThatNotMetTheirDeadline == 0)
	    	std::cout << "All executed jobs met their deadline.\n\n";
	    else
	    	if(jobsThatNotMetTheirDeadline == 1)
	    		std::cout << jobsThatNotMetTheirDeadline << " job missed its deadline.\n\n";
	    	else
	    		std::cout << jobsThatNotMetTheirDeadline << " jobs missed their deadline.\n\n";

	    printMachineTimeline();
}

void scheduler::removeDependencies(int jobId) {
	std::list<int> listDependenciesTo = jobs[jobId].getListDependenciesTo();

	for (std::list<int>::iterator it = listDependenciesTo.begin(); it != listDependenciesTo.end(); it++)
		if( jobs[*it].removeDependency(jobId) )
			if(isInList(*it,WAITING))
				swapList(*it, WAITING, READY);
}

void scheduler::dispatcher() {
	if(readyJobsList.empty()) return; //no processes ready, no party

	if(preemptive) { //if the system is preemptive
		std::map<int,int> myMap = getProcessorsOrderedByJobId();

		//first let's fill up processors without a job
		for (std::map<int,int>::iterator it = myMap.begin(); it != myMap.end() && !readyJobsList.empty() && it->first < 0; it++){
			processors[it->second].setJob(readyJobsList.front());
			readyJobsList.pop_front();
		}

		//secondly let's preempt jobs with low priority
		for (std::map<int,int>::iterator it = myMap.end(); !readyJobsList.empty() && it->first >= 0; it--){
			if(it == myMap.end()) it--;
			if(it->first > readyJobsList.front()) {
				addToList(it->first, READY);
				processors[it->second].setJob(readyJobsList.front());
				readyJobsList.pop_front();
			}
			else break; //this for cycle goes on only until there are jobs on the ready queue that have more priority than the executing ones

			if(it == myMap.begin())
				break;
		}
	}
	else { //if the system ain't preemptive
		for(std::vector<processor>::size_type i = 0; (i != processors.size()) && !readyJobsList.empty(); ++i) {
			if(processors[i].getJob() < 0){ //if there's no job running on this processor
				processors[i].setJob(readyJobsList.front());
				readyJobsList.pop_front();
			}
		}
	}
}

void scheduler::step() {
	clockStep++; //updates clock

	if(checkIncomingJobs()) //returns true if one or more jobs
		dispatcher();

	if(executeStep()) //returns true if one or more jobs end!
		dispatcher();
}
