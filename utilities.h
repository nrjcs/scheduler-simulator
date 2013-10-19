/********************************************************
 * utilites.h                                           *
 *                                                      *
 * Progetto Tipo 1 Sistemi in tempo Reale               *
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
	void printIncomingMap(std::map<int,std::list<int> > myMap);
	void printIntIntMap(std::map<int,int>& myMap);
	void printList(std::list<int>& myList);
	void printVector(std::vector<int>& myVect);
}
