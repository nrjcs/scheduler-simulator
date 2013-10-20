/********************************************************
 * lists.h                                              *
 *                                                      *
 * Progetto Tipo 1 Sistemi in tempo Reale               *
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include "utilities.h"
#include <algorithm>

namespace lists {
	extern std::list<int> executedJobsList;						// list of jobs that ended their execution
	extern std::map<int,std::list<int> > incomingJobsMap;		// it contains a list of incoming jobs linked to their release time
	extern std::list<int> readyJobsList;						// queue of ready jobs, ordered by priority
	extern std::list<int> waitingJobsList;						// queue of released jobs that await other job's executions

	void addToList(int jobId,int whichList);					// add a job to a list or queue
	bool isInList(int whichList, int Jobid);					// check whether a job is on a list
	void removeFromReady(int processId);						// remove a job from one list to another
	void swapList(int ProcessId, int fromList, int toList);		// swap jobs among ready and waiting lists
}
