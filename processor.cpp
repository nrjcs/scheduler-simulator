/********************************************************
 * process.cpp                                          *
 *                                                      *
 * Progetto Tipo 1 Sistemi in tempo Reale               *
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include "processor.h"

processor::processor() {
	id = -1;
	process = -1;
}

int processor::getProcess(){
	 return process;
}

int processor::executeStep(){
	timeline.push_back(process);
	return process;
}
void processor::initialise(int _id) {
	id = _id;
	process = -id;
}
void processor::printTimeline(){
	if(id<10)
		std::cout << " [0" << id << "]: ";
	else
		std::cout << " [" << id << "]: ";

	for (std::vector<int>::size_type i = 0; i != timeline.size(); ++i) {
		std::cout << " ";

		if(timeline[i] < 0) {
			std::cout << "--";
			continue;
		}
		if(timeline[i] < 10)
			std::cout << "0";

		std::cout <<  timeline[i]+1;
	}
	std::cout << '\n';
}

void processor::setProcess(int processId){
	if(processId < 0)
		process = -id;
	else
		process = processId;
 }
