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
	process = -1;
}

int processor::getProcess(){
	 return process;
}

int processor::executeStep(){
	history.push_back(process);
	printHistory();
	return process;
}

void processor::printHistory(){
	for (std::vector<int>::size_type i = 0; i != history.size(); ++i)
		if(history[i] > 0 && history[i] < 10)
			std::cout << " 0" << history[i];
		else
			std::cout << " " <<  history[i];
	std::cout << '\n';
}

void processor::setProcess(int processId){
	 process = processId;
 }
