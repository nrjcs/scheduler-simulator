/********************************************************
 * lists.cpp                                            *
 *                                                      *
 * Corso Sistemi in tempo Reale               			*
 * Progetto Tipo 1	P3									*
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include "lists.h"

namespace lists {
	std::list<int> executedJobsList;							// list of jobs that ended their execution
	std::map<int,std::list<int> > incomingJobsMap;				// it contains a list of incoming jobs linked to their release time
	std::list<int> readyJobsList;								// queue of ready jobs, ordered by priority
	std::list<int> waitingJobsList;								// queue of released jobs that await other job's executions


	void addToList(int jobId,int whichList){
		switch(whichList) {
			case utilities::READY: readyJobsList.push_back(jobId); readyJobsList.sort(); break;
			case utilities::WAITING: waitingJobsList.push_back(jobId); break;
			case utilities::EXECUTED: executedJobsList.push_back(jobId); break;
		}
		return;
	}

	bool isInList(int jobId, int whichList){
		std::list<int>::iterator findIter;
		switch(whichList) {
			case utilities::READY: findIter = std::find(readyJobsList.begin(), readyJobsList.end(), jobId); return findIter != readyJobsList.end();
			case utilities::WAITING: findIter = std::find(waitingJobsList.begin(), waitingJobsList.end(), jobId); return findIter != waitingJobsList.end();
			case utilities::EXECUTED: findIter = std::find(executedJobsList.begin(), executedJobsList.end(), jobId); return findIter != executedJobsList.end();
		}
	}

	void removeFromReady(int jobId){
		readyJobsList.remove(jobId);
	}

	void swapList(int jobId, int from, int to){
		switch(from) {
			case utilities::READY: readyJobsList.remove(jobId); break;
			case utilities::WAITING: waitingJobsList.remove(jobId); break;
		}

		switch(to) {
			case utilities::READY: readyJobsList.push_back(jobId); readyJobsList.sort(); break;
			case utilities::WAITING: waitingJobsList.push_back(jobId); break;
		}
	}

	void removeDependencies(int jobId, std::vector<job>& _jobs) {
		std::list<int> listDependenciesTo = _jobs[jobId].getListDependenciesTo();

		for (std::list<int>::iterator it = listDependenciesTo.begin(); it != listDependenciesTo.end(); it++)
			if(_jobs[*it].removeDependency(jobId) )
				if(isInList(*it,utilities::WAITING))
					swapList(*it, utilities::WAITING, utilities::READY);
	}
}
