/********************************************************
 * lists.cpp                                            *
 *                                                      *
 * Progetto Tipo 1 Sistemi in tempo Reale               *
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include "lists.h"

namespace lists {
	enum { EXECUTED, INCOMING, READY, RUNNING, WAITING }; //jobs status

	std::list<int> executedJobsList;						// list of jobs that ended their execution
	std::map<int,std::list<int> > incomingJobsMap;			// it contains a list of incoming jobs linked to their release time
	std::list<int> readyJobsList;							// queue of ready jobs, ordered by priority
	std::list<int> waitingJobsList;							// queue of released jobs that await other job's executions


	void addToList(int jobId,int whichList){
		switch(whichList) {
			case READY: readyJobsList.push_back(jobId); readyJobsList.sort(); break;
			case WAITING: waitingJobsList.push_back(jobId); break;
			case EXECUTED: executedJobsList.push_back(jobId); break;
		}
		return;
	}

	bool isInList(int jobId, int whichList){
		std::list<int>::iterator findIter;
		switch(whichList) {
			case READY: findIter = std::find(readyJobsList.begin(), readyJobsList.end(), jobId); break;
			case WAITING: findIter = std::find(waitingJobsList.begin(), waitingJobsList.end(), jobId); break;
			case EXECUTED: findIter = std::find(executedJobsList.begin(), executedJobsList.end(), jobId); break;
		}
		return *findIter == jobId;

	}

	void removeFromReady(int jobId){
		readyJobsList.remove(jobId);
	}

	void swapList(int jobId, int from, int to){
		switch(from) {
			case READY: readyJobsList.remove(jobId); break;
			case WAITING: waitingJobsList.remove(jobId); break;
		}

		switch(to) {
			case READY: readyJobsList.push_back(jobId); readyJobsList.sort(); break;
			case WAITING: waitingJobsList.push_back(jobId); break;
		}
	}
}
