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

namespace lists {
	extern std::map<int,std::list<int> > incomingProcessesMap; // step number and list of incoming processes
	extern std::list<int> readyProcessesList;
	extern std::list<int> waitingProcessesList;
	extern std::list<int> executedJobsList;

	void addToList(int processId,int whichList);
	void printAllLists();
	void removeFromReady(int processId);
	void swapList(int ProcessId, int fromList, int toList);

	bool checkIncomingJobs();
}
