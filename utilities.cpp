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
	void printList(std::list<int>& myList){
		for (std::list<int>::iterator it = myList.begin(); it != myList.end(); it++)
			std::cout << *it << " ";
		std::cout << '\n';
	}

	void printIncomingMap(std::map<int,std::list<int> > myMap){
		for (std::map<int,std::list<int> >::iterator it = myMap.begin(); it != myMap.end(); it++) {
			std::cout << " release time: " << it->first << " processes: ";
			printList((it->second));
		}
	}
}
