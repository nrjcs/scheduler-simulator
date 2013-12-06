/********************************************************
 * processor.cpp                                        *
 *                                                      *
 * Corso Sistemi in tempo Reale               			*
 * Progetto Tipo 1	P3									*
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include "processor.h"

processor::processor() {
	id = -1;
	job = -1;
}

int processor::getJob(){
	 return job;
}

int processor::executeStep(){
	timeline.push_back(job);
	return job;
}
void processor::initialise(int procId) {
	id = procId;
	job = -id;
}
void processor::printTimeline(){
	std::cout << " [" << std::setw(2) << std::setfill('0') << id << "]: ";

	for (std::vector<int>::size_type i = 0; i != timeline.size(); ++i) {
		std::cout << " ";

		if(timeline[i] < 0) {
			std::cout << "--";
			continue;
		}
		std::cout << std::setw(2) << std::setfill('0') << timeline[i];
	}
	std::cout << '\n';
}

void processor::setJob(int jobId){
	if(jobId < 0)
		job = -id;
	else
		job = jobId;
 }
