/********************************************************
 * main.cpp                                             *
 *                                                      *
 * Corso Sistemi in tempo Reale               			*
 * Progetto Tipo 1	P3									*
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include "scheduler.h"

using namespace lists;

enum { EXECUTED, INCOMING, READY, RUNNING, WAITING }; 			//jobs status

void readFromFile();											// load data from input file
void readAndInitialiseJob(int jobId,  std::istringstream& iss); // read from input the job information and initialise it
void removeDependencies(int jobId);								// alerts all the linked jobs that the jobId has finished

bool preemptive = true;											// by default the machine is preemptive
bool bestEffort = true;											// by default the machine is best effort (executes unfeasible jobs)
std::vector<processor> processors;								// array of system's processors
std::vector<job> jobs;											// array of system's jobs
int jobsThatNotMetTheirDeadline = 0;							// current jobs number that finished after their deadline
int unfeasibleJobsNumber = 0;									// current unfeasible jobs number
unsigned totalJobsNumber;										// total number of jobs in the system

int main(int argc, char** argv){
	//initialising everything
	readFromFile();

    std::cout << "Starting machine...";

    scheduler(preemptive, bestEffort, processors, jobs, unfeasibleJobsNumber, totalJobsNumber);

    return 0;
}

void readAndInitialiseJob(int jobId,  std::istringstream& iss) {
	int releaseTime, deadline, executionTime, temp;
	iss >> releaseTime;
	iss >> deadline;
	iss >> executionTime;

	jobs[jobId].initialise(jobId,releaseTime, deadline, executionTime);

	if(!jobs[jobId].isFeasible()){ //if the job is unfeasible
		unfeasibleJobsNumber++;
		if(!bestEffort) { //if the system is not best effort the job is not going to be executed
			removeDependencies(jobId);
			addToList(jobId, EXECUTED);
			return;
		}
	}
	// adding dependencies
	while (iss >> temp) {
		if(!isInList(temp, EXECUTED)) { //if the job isn't executed yet
			jobs[jobId].addDependency(temp);
			jobs[temp].alertThisJobWhenDone(jobId);
		}
	}
	incomingJobsMap[releaseTime].push_back(jobId);
}

void readFromFile() {
	std::cout << "Initialising machine...\n\nMachine statistics\n";
	unsigned processorsNumber;
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
				iss >> totalJobsNumber;
				std::cout << " -Jobs: " << totalJobsNumber << ";\n\n";
				jobs.assign(totalJobsNumber, job());
				break;
			default: readAndInitialiseJob(++jobId,iss);
		}
	}
}

void removeDependencies(int jobId) {
	std::list<int> listDependenciesTo = jobs[jobId].getListDependenciesTo();

	for (std::list<int>::iterator it = listDependenciesTo.begin(); it != listDependenciesTo.end(); it++)
		if( jobs[*it].removeDependency(jobId) )
			if(isInList(*it,WAITING))
				swapList(*it, WAITING, READY);
}
