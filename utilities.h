/********************************************************
 * utilites.h   										*
 * 				                                        *
 * Corso Sistemi in tempo Reale               			*
 * Progetto Tipo 1	P3									*
 * Anno 2013/14                                         *
 * Universita' degli studi   di Padova                  *
 *                                                      *
 * Author: Federico Zanetello                           *
 ********************************************************/
#include <list>
#include <map>
#include <vector>
#include <iostream>
#include <iomanip>

namespace utilities {
	void printIncomingMap(std::map<int,std::list<int> > myMap);			// prints the Incoming Jobs map (see lists.h for reference)
	void printIntIntMap(std::map<int,int>& myMap);						// prints the input <int,int> map
	void printList(std::list<int>& myList);								// prints the input int list
	void printVector(std::vector<int>& myVect);							// prints the input int vector
}
