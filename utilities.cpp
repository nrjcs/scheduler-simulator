/********************************************************
 * utilites.h                                           *
 *                                                      *
 * Progetto Tipo 1 Sistemi in tempo Reale               *
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include "utilities.h"

namespace utilities {

	void printIncomingMap(std::map<int,std::list<int> > myMap){
		for (std::map<int,std::list<int> >::iterator it = myMap.begin(); it != myMap.end(); it++) {
			std::cout << " release time: " << it->first << " processes: ";
			printList((it->second));
		}
	}

	void printIntIntMap(std::map<int,int>& myMap) {
		for (std::map<int,int>::iterator it = myMap.begin(); it != myMap.end(); it++)
			std::cout << it->first << " (" << it->second << ") ";
		std::cout << '\n';
	}

	void printList(std::list<int>& myList){
		for (std::list<int>::iterator it = myList.begin(); it != myList.end(); ++it)
			std::cout << *it << " ";
		std::cout << '\n';
	}

	void printVector(std::vector<int>& myVec) {
		for(std::vector<int>::size_type i = 0; i != myVec.size(); ++i)
			std::cout << myVec[i] << " ";
		std::cout << '\n';
	}
}
