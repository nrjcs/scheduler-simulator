/********************************************************
 * main.cpp                                             *
 *                                                      *
 * Progetto Tipo 1 Sistemi in tempo Reale               *
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include "job.h"
#include "processor.h"
#include "lists.h"
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace lists;

enum { EXECUTED, INCOMING, READY, RUNNING, WAITING }; 			//jobs status

bool checkIncomingJobs();										// this function release each scheduled job at the right time, returns true if one or more READY jobs are relased
bool executeStep();												// makes each processor to execute one step: returns true if one or more jobs finish
std::map<int,int> getProcessorsOrderedByJobPriority();			// returns a map with a link to the processors ordered by their current executing jobs
void printMachineTimeline();									// prints report of the machine behavior
unsigned readFromFile();										// load data from input file
void readAndInitialiseJob(int jobId,  std::istringstream& iss); //read from input the job information and initialise it
void removeDependencies(int jobId);								// alerts all the linked jobs that the jobId has finished
void scheduler();												// add/preempt jobs to/from processors
void step();													// it's like a clock
void wait();													// stops the program execution until the user press the return key

bool preemptive = true;											// by default the machine is preemptive
bool bestEffort = true;											// by default the machine is best effort (executes unfeasible jobs)
int clockStep = -1;												// keeps track of the system time
std::vector<processor> processors;								// array of system's processors
std::vector<job> jobs;											// array of system's jobs

int main(int argc, char** argv){
	//initialising everything
	unsigned jobsNumber = readFromFile();

    std::cout << "Starting machine...";

    //main loop
    while(executedJobsList.size() < jobsNumber)
    	step();

    std::cout << "...all done!\n\n";

    //print report
    printMachineTimeline();

    return 0;
}

bool checkIncomingJobs(){
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

bool executeStep(){
	bool somethingEnded = false; //if a job ended this function returns true
	for(std::vector<processor>::size_type i = 0; i != processors.size(); ++i) {
		int processRunning = processors[i].executeStep();
		if(processRunning  >= 0) {
			if(jobs[processRunning].executeOneStep(clockStep)) { //returns true when the job ends
				processors[i].setJob(-1); //remove job from processor
				addToList(processRunning, EXECUTED); //add job in executed jobs list

				removeDependencies(processRunning); // alerts other jobs about that the job finished

				somethingEnded = true; //for return porpouses
			}
		}
	}
	return somethingEnded;
}

std::map<int,int> getProcessorsOrderedByJobPriority() {
	std::map<int,int> processorsOrderedByJobPriority;

	for(std::vector<processor>::size_type i = 0; i != processors.size(); ++i)
		processorsOrderedByJobPriority[processors[i].getJob()] = i;

	return processorsOrderedByJobPriority;
}

void printMachineTimeline() {
	std::cout << 	"Machine timeline \n\n"
				 	" ########## [] indicates processors, <> indicates jobs \n"
					" # LEGEND # ^ indicates the release time and the deadline \n"
					" ########## * indicates the response and completion time \n\n";

	std::cout << " TIME  ";
	for(int i=0; i<= clockStep; i++)
		std::cout << std::setw(2) << std::setfill('0') << i << " ";

	std::cout << '\n' << "      ";

	for(int i=0; i<= clockStep; i++)
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

void readAndInitialiseJob(int jobId,  std::istringstream& iss) {
	int releaseTime, deadline, executionTime, temp;
	iss >> releaseTime;
	iss >> deadline;
	iss >> executionTime;

	jobs[jobId].initialise(jobId,releaseTime, deadline, executionTime);

	if((!bestEffort) && (!jobs[jobId].isFeasible())){ //this decides whether the job is going to be executed or not
		removeDependencies(jobId);
		addToList(jobId, EXECUTED);
	}
	else{
		while (iss >> temp) {
			if(!isInList(temp, EXECUTED)) { //if the job isn't executed yet
				jobs[jobId].addDependency(temp);
				jobs[temp].alertThisJobWhenDone(jobId);
			}
		}
		incomingJobsMap[releaseTime].push_back(jobId);
	}
}

unsigned readFromFile() {
	std::cout << "Initialising machine...\n\nMachine statistics\n";
	unsigned processorsNumber, processesNumber;
	std::ifstream myFile("input");

	int jobId = -1, lineNumber = -1;
	std::string line;

	while (std::getline(myFile, line))
	{
		int temp;
		std::istringstream iss(line);
		switch(++lineNumber) {
			case 0:
				iss >> temp;
				if(temp == 0){
					preemptive = false;
					std::cout << " -Non-preemptive;\n";
				}
				else
					std::cout << " -Preemptive;\n";

				break;
			case 1:
				iss >> temp;
				if(temp == 0){
					bestEffort = false;
					std::cout << " -Non best effort (doesn't execute unfeasible jobs);\n";
				}
				else
					std::cout << " -Best effort (executes unfeasible jobs);\n";
				break;
			case 2:
				iss >> processorsNumber;
				std::cout << " -Processors: " << processorsNumber << ";\n";
				processors.assign(processorsNumber, processor());
				for(unsigned i = 0; i < processorsNumber; i++)
					processors[i].initialise(i+1);
				break;
			case 3:
				iss >> processesNumber;
				std::cout << " -Jobs: " << processesNumber << ";\n\n";
				jobs.assign(processesNumber, job());
				break;
			default: readAndInitialiseJob(++jobId,iss);
		}
	}
	return processesNumber;
}

void removeDependencies(int jobId) {
	std::list<int> listDependenciesTo = jobs[jobId].getListDependenciesTo();

	for (std::list<int>::iterator it = listDependenciesTo.begin(); it != listDependenciesTo.end(); it++)
		if( jobs[*it].removeDependency(jobId) )
			if(isInList(*it,WAITING))
				swapList(*it, WAITING, READY);
}

void scheduler() {
	if(readyJobsList.empty()) return; //no processes ready, no party

	if(preemptive) { //if the system is preemptive
		std::map<int,int> myMap = getProcessorsOrderedByJobPriority();
		for (std::map<int,int>::iterator it = myMap.begin(); it != myMap.end() && !readyJobsList.empty(); it++)
			if(it->first < 0 || it->first > readyJobsList.front()) {
				if(it->first >= 0)
					addToList(it->first, READY);
				processors[it->second].setJob(readyJobsList.front());
				readyJobsList.pop_front();
			}
			else break; //this for cycle goes on only until there are jobs on the ready queue that have more priority than the executing ones
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

void step() {
	clockStep++; //updates clock

	if(checkIncomingJobs()) //returns true if one or more jobs
		scheduler();

	if(executeStep()) //returns true if one or more jobs end!
		scheduler();
}

void wait() {
	std::cout << "Press ENTER to continue...\n";
	std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );
}
