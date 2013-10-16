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
	history = "";
}

int processor::getProcess(){
	 return process;
}

int processor::executeStep(){
	history.append(".");
	if(process<10)
		history.append(std::to_string(process));
	history.append(".");
	return process;
}

 void processor::setProcess(int processId){
	 process = processId;
 }
