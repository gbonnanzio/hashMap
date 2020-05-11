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
	hashNode **map = new hashNode[10];
	for(int i = 0; i < 10; i++){
		map[i] = hashNode();
	}
	mapSize = 10;
	first = map[1];
	numKeys = 0;
	hashfn = hash1;
	collfn = coll1;
	collisions = 0;
	hashcoll = 0;

}
void hashMap::addKeyValue(string k, string v) {

	int Index = getIndex(k);
	hashNode *newNode = hashNode(k, v);
	if((map[Index]->keyword).compare == ""){
		map[Index] = newNode;
		numKeys = numKeys+1;
	}
	else{
		addValue(k);
	}
	int load = numKeys/mapSize;
	if(load > 0.7){
		reHash();
	}
	return;

}


int hashMap::getIndex(string k) {

	if(hashfn == true){
		int firstIndex = calcHash1(k);
		if((map[firstIndex]->keyword).compare == ""){
			return firstIndex;
		}
		else if((map[firstIndex]->keyword).compare == k){
			return firstIndex;
		}
		else if(collfn == true){
			hashcoll = hashcoll + 1;
			int newIndex = coll1(firstIndex, 0, k);
			return newIndex;
			}
		else{
			hashcoll = hashcoll + 1;
			int newIndex = coll2(firstIndex, 0, k);
			return newIndex;
		}
	}
	else{
		int firstIndex = calcHash2(k);
		if((map[firstIndex]->keyword).compare == ""){
			return firstIndex;
		}
		else if((map[firstIndex]->keyword).compare == k){
			return firstIndex;
		}
		else if(collfn == true){
			hashcoll = hashcoll + 1;
			int newIndex = coll1(firstIndex, 0, k);
			return newIndex;
		}
		else{
			hashcoll = hashcoll + 1;
			int newIndex = coll2(firstIndex, 0, k);
			return newIndex;
		}
	}




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
}







int hashMap::coll1(int h, int i, string k) { //linear probing
	if (map[i]==NULL || (map[i]->keyword).compare(k)!=0){
		return i;
	}
	else {
		if (i+1==mapSize){
			coll1(h,0,k);
		}
		else {
			coll1(h,i+1,k);
		}
	}
}
int hashMap::coll2(int h, int i, string k) { //quadratic probing
	int count = 1;
	if (map[i]==NULL || (map[i]->keyword).compare(k)!=0){
		return i;
	}
	else {
		int change= count^2;
		if(i+change==mapSize){
			count++;
			coll1(h,0,k);
		}
		else {
			count++;
			coll1(h,i+change,k);
		}
	}
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


