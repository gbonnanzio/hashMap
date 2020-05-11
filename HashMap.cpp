/*
 * HashMap.cpp
 *
 *  Created on: May 4, 2020
 *      Author: 13027
 */


#include "hashMap.hpp"
#include "hashNode.hpp"
#include <iostream>
#include <math.h>
using namespace std;

hashMap::hashMap(bool hash1, bool coll1) {
}
void hashMap::addKeyValue(string k, string v) {
}
int hashMap::getIndex(string k) {
}


































































//test
































int hashMap::calcHash2(string k){
	int length = k.size();
	int sum = 0;
	for(int i = 0; i<length; i++){
		sum = sum + pow(27,i)*(int)k[i];
	}
	int hash = sum%mapSize;
	return hash;
}















int hashMap::calcHash1(string k){
	int length = k.size();
	int sum = 0;
	for(int i = 0; i<length; i++){
		sum = sum + pow((int)k[i],i+1);
	}
	int hash = sum%mapSize;
	return hash;

}

















void hashMap::getClosestPrime() {
	int testNum = mapSize + 1;
	bool primeCheck = isPrime(testNum);
	while(primeCheck == false){
		testNum++;
		primeCheck = isPrime(testNum);
	}
	mapSize = testNum;
}

bool hashMap::isPrime(int testNum){
	//returns true if checkNum is prime
	int numSqrRoot = floor(sqrt(testNum));
	bool checker;
	int val;
	for(int i=2; i<numSqrRoot; i++){
		val = testNum%i;
		if(val == 0){
			return true;
		}
	}
	return false;
}

void hashMap::reHash() {
	//clone current map
	int prevSize = mapSize;
	hashNode** oldHashMap = new hashNode[prevSize];
	for(int i = 0; i<prevSize; i++){
		oldHashMap[i] = map[i];
	}
	//create and assign our new map
	mapSize = 2*mapSize;
	getClosestPrime();
	hashNode** newHashMap = new hashNode[mapSize];
	map = newHashMap;
	//place old values in new map
	for(int i = 0; i<prevSize; i++){
		if(oldHashMap[i]!=NULL){
			string key = oldHashMap[i]->keyword;
			for(int j=0; j<oldHashMap[i]->currSize; j++){
				string val = oldHashMap[i]->values[j];
				addKeyValue(key,val);
			}
		}
	}
}


int hashMap::coll1(int h, int i, string k) {
}
int hashMap::coll2(int h, int i, string k) {
}
int hashMap::findKey(string k) {
//NOTE: THIS METHOD CANNOT LOOP from index 0 to end of hash array looking for the key.  That destroys any efficiency in run-time. 
}


void hashMap::printMap() {
	cout << "In printMap()" << endl;
	for (int i = 0; i < mapSize; i++) {
		//cout << "In loop" << endl;
		if (map[i] != NULL) {
			cout << map[i]->keyword << ": ";
			for (int j = 0; j < map[i]->currSize;j++) {
				cout << map[i]->values[j] << ", ";
			}
			cout << endl;
		}
	}
}


