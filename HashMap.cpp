/*
 * HashMap.cpp
 *
 *  Created on: May 4, 2020
 *      Author: 13027
 */

/*
#include "hashMap.hpp"
#include "hashNode.hpp"
#include <iostream>
#include <math.h>
using namespace std;

hashMap::hashMap(bool hash1, bool coll1) {
	map = new hashNode*[10];
	for(int i = 0; i < 10; i++){
		map[i] = new hashNode();
	}
	mapSize = 10;
	first = map[1]->keyword;
	numKeys = 0;
	hashfn = hash1;
	collfn = coll1;
	collisions = 0;
	hashcoll = 0;

}
void hashMap::addKeyValue(string k, string v) {
	int Index = getIndex(k);
	cout << k << endl;
	hashNode* newNode = new hashNode(k, v);
	cout <<Index<<endl;
	if((map[Index]->keyword).compare("")==0){
		cout << "test 5" << endl;
		map[Index] = newNode;
		numKeys = numKeys+1;
	}
	else{
		map[Index]->addValue(k);
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
		if((map[firstIndex]->keyword).compare("")==0){
			return firstIndex;
		}
		else if((map[firstIndex]->keyword).compare(k)==0){
			return firstIndex;
		}
		else if(collfn == true){
			hashcoll = hashcoll + 1;
			int newIndex = coll1(firstIndex, firstIndex, k);
			cout << newIndex << endl;
			return newIndex;
			}
		else{
			hashcoll = hashcoll + 1;
			int newIndex = coll2(firstIndex, firstIndex, k); //
			return newIndex;
		}
	}
	else{
		int firstIndex = calcHash2(k);
		if((map[firstIndex]->keyword).compare("")==0){
			return firstIndex;
		}
		else if((map[firstIndex]->keyword).compare(k)==0){
			return firstIndex;
		}
		else if(collfn == true){
			hashcoll = hashcoll + 1;
			int newIndex = coll1(firstIndex, firstIndex, k);
			return newIndex;
		}
		else{
			hashcoll = hashcoll + 1;
			int newIndex = coll2(firstIndex, firstIndex, k);
			return newIndex;
		}
	}
}



int hashMap::calcHash2(string k){
	int length = k.size();
	int sum = 0;
	int templength;
	if (length<3){
		templength=length;
	}
	else {
		templength = 3;
	}
	for(int i = 0; i<templength; i++){
		sum = sum + pow(27,i)*(int)k[i];
	}
	int hash = sum%mapSize;
	return hash;
}















int hashMap::calcHash1(string k){
	int length = k.size();
	int sum = 0;
	int templength;
	if (length<3){
		templength=length;
	}
	else {
		templength = 3;
	}
	for(int i = 0; i<templength; i++){
		sum = sum + pow((int)k[i],i+1);
	}
	cout << sum<<endl;
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
	hashNode* oldHashMap[prevSize];
	for(int i = 0; i<prevSize; i++){
		oldHashMap[i] = map[i];
	}
	//create and assign our new map
	mapSize = 2*mapSize;
	getClosestPrime();
	hashNode* newHashMap[mapSize];
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






int hashMap::coll1(int h, int i, string k) { //linear probing
	if ((map[i]->keyword).compare("")==0 || (map[i]->keyword).compare(k)==0){
		return i;
	}
	else {
		if (i+1==mapSize){
			coll1(h,0,k);
		}
		else {
			int j = coll1(h,i+1,k);
			return j;
		}
	}
}

int hashMap::coll2(int h, int i, string k) { //quadratic probing
	int count = 1;
	if (map[i]==NULL || (map[i]->keyword).compare(k)==0){
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

	if(hashfn == true){
		int firstIndex = calcHash1(k);
		if((map[firstIndex]->keyword).compare("")==0){
			return -1;
		}
		else if((map[firstIndex]->keyword).compare(k)==0){
			return firstIndex;
		}
		else if(collfn == true){
			int newIndex = coll1(firstIndex, 0, k);
			if((map[newIndex]->keyword).compare(k)==0){
				return newIndex;
			}
			else{
				return -1;
			}
		}
		else{
			int newIndex = coll2(firstIndex, 0, k);
			if((map[newIndex]->keyword).compare(k)==0){
				return newIndex;
			}
			else{
				return -1;
			}
		}
	}
	else{
		int firstIndex = calcHash2(k);
		if((map[firstIndex]->keyword).compare("")==0){
			return -1;
		}
		else if((map[firstIndex]->keyword).compare(k)==0){
			return firstIndex;
		}
		else if(collfn == true){
			int newIndex = coll1(firstIndex, 0, k);
			if((map[newIndex]->keyword).compare(k)==0){
				return newIndex;
			}
			else{
				return -1;
			}
		}
		else{
			int newIndex = coll2(firstIndex, 0, k);
			if((map[newIndex]->keyword).compare(k)==0){
				return newIndex;
			}
			else{
				return -1;
			}
		}
	}



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
*/

//Chloe's code from 5-11-20

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
/*Input: a boolean indicating which hash function to use, a boolean indicating which collision function to use
 * Output: None
 * Action: Is a constructor to make an initial hash map
 */
	map = new hashNode *[11];
	for (int i=0;i<11;i++){
		map[i]=NULL; //set all of the values to an initial empty value

	}
	first = "";
	numKeys=0;
	mapSize = 11;
	hashfn=hash1;
	collfn=coll1;
	collisions=0;
	hashcoll=0;
}

void hashMap::printMap() {
/*Input: None
 * Output: None
 * Action: Printing all the keys and values in the map
 */
	cout << "In printMap()" << endl;
	for (int i = 0; i < mapSize; i++) {
		if (map[i] != NULL) {
			cout << map[i]->keyword << ": ";
			for (int j = 0; j < map[i]->currSize;j++) {
				cout << map[i]->values[j] << ", ";
			}
			cout << endl;
		}
	}
}

void hashMap::addKeyValue(string k, string v) {
/*Input: A string holding the key, a string holding the value
 * Output: None
 * Action: Add the key to the map and add it's value to the corresponding values array
 */
	int Index = getIndex(k); //find out which index to place the key
	if (map[Index]==NULL){ //if no node already exists
		map[Index]=new hashNode(k,v);
		numKeys++;
	}
	else if (map[Index]!=NULL && map[Index]->keyword.compare(k)==0){ //if this word is already in the map
		map[Index]->addValue(v);
	}
	if (first==""){ //if this is the first node placed set the first value
		first=k;
	}
	double ratio  = (double)numKeys/(double)mapSize;
	if (ratio>0.7){ //if we are over 70% full in the map, make the map bigger
		reHash();
	}
}

int hashMap::getIndex(string k) {
/*Input: A string holding the value of the key
 * Output: An integer of the appropriate index in the map
 * Action: Figure out which index the key should go to in the map
 */
	if (hashfn){ //if we are using hash function one
		int Index = calcHash1(k);
		if (map[Index]!=NULL && map[Index]->keyword.compare(k)!=0 && collfn){ //if there is at least one collision and we are using collision function one
			collisions++;
			int loopcounter=0;
			while ((map[Index]!=NULL && map[Index]->keyword.compare(k)!=0)){
				//iterating through the linear probing method until we find a spot for the key
				Index = coll1(Index,loopcounter,k);
				loopcounter++;
			}
			hashcoll=hashcoll+(loopcounter-1);
		}
		else if (map[Index]!=NULL && map[Index]->keyword.compare(k)!=0 && !collfn){ //if there is at least one collision and we are using collision function two
			collisions++;
			int loopcounter=0;
			while ((map[Index]!=NULL && map[Index]->keyword.compare(k)!=0)){
				//iterating through the quadratic probing method until we find a spot for the key
				Index = coll2(Index,loopcounter,k);
				loopcounter++;
			}
			hashcoll=hashcoll+(loopcounter-1);
		}
		return Index;
	}
	else {
		int Index = calcHash2(k);
		if (map[Index]!=NULL && map[Index]->keyword.compare(k)!=0 && collfn){//if there is at least one collision and we are using collision function one
			collisions++;
			int loopcounter=0;
			while ((map[Index]!=NULL && map[Index]->keyword.compare(k)!=0)){
				//iterating through the linear probing method until we find a spot for the key
				Index = coll1(Index,loopcounter,k);
				loopcounter++;
			}
			hashcoll=hashcoll+(loopcounter-1);
		}
		else if (map[Index]!=NULL && map[Index]->keyword.compare(k)!=0 && !collfn){//if there is at least one collision and we are using collision function two
			collisions++;
			int loopcounter=0;
			while ((map[Index]!=NULL && map[Index]->keyword.compare(k)!=0)){
				//iterating through the quadratic probing method until we find a spot for the key
				Index = coll2(Index,loopcounter,k);
				loopcounter++;
			}
			hashcoll=hashcoll+(loopcounter-1);
		}
		return Index;
	}
}

int hashMap::calcHash2(string k){
	int length = k.size();
	int sum = 0;
	int templength;
	if (length<3){
		templength=length;
	}
	else {
		templength = 3;
	}
	for(int i = 0; i<templength; i++){
		sum = sum + pow(27,i)*(int)k[i];
	}
	int hash = sum%mapSize;
	return hash;
}
int hashMap::calcHash1(string k){
	int length = k.size();
	int sum = 0;
	int templength;
	if (length<3){
		templength=length;
	}
	else {
		templength = 3;
	}
	for(int i = 0; i<templength; i++){
		sum = sum + pow((int)k[i],i+1);
	}
	int hash = sum%mapSize;
	return hash;
}


void hashMap::getClosestPrime() {
/*Input: None
 * Output: None
 * Action: Find the closest prime to the current mapSize
 */
	int testNum = mapSize;
	bool nofactors = true;
	while (nofactors){
		testNum++;
		bool interiorfactors = false;
		for (int i = 2; i<testNum; i++){
			if (testNum%i==0){ //if the test number has an factors we set interior factors to true
				interiorfactors=true;
			}
		}
		if (interiorfactors==false){
			//in the case that the number tested has no factors, it is the prime we want
			nofactors=false;
		}
	}
	mapSize=testNum;
}


void hashMap::reHash() {
/*Input: None
 * Output: None
 * Action: Rehash all the information in the old map into a newer larger map
 */
	//get all of the information in the current map stored in a temp map
	int temp = mapSize;
	hashNode* oldHashMap[temp];
	for (int i=0;i<temp;i++){
		oldHashMap[i]=map[i];
	}

	//get the new larger map size
	mapSize=mapSize*2;
	getClosestPrime();

	//make a new map and set all of it's spaces to Null
	map = new hashNode*[mapSize];
	for (int i=0;i<mapSize;i++){
		map[i]=NULL;

	}
	first = "";
	numKeys=0;

	//now we need to iterate through all of the nodes in the old map and place their info in the new
	for(int i=0;i<temp;i++){
		if (oldHashMap[i]!=NULL){ //if the old hash map had info at this node
			string k = oldHashMap[i]->keyword;
			int j=0;
			while (oldHashMap[i]->values[j]!=""){ //go through all the values at this node and append them onto the new map
				addKeyValue(k,oldHashMap[i]->values[j]);
				j++;
			}
		}
	}
}

int hashMap::coll1(int h, int i, string k){
/*Input: An integer of the current index, an integer of the total repititions we've used this function, and a string holding the key value
 * Output: An integer index of the next spot along using the linear probing method
 * Action: Probe linearly if we have a collision
 */
	if (h+1==mapSize){ //in the case that we go out of bounds of the map
		return 0;
	}
	else {
		return h+1;
	}
}

int hashMap::coll2(int h, int i, string k){
/*Input: An integer of the current index, an integer of the total repetitions we've used this function, and a string holding the key value
 * Output: An integer index of the next spot along using the quadratic probing method
 * Action: Probe quadratically if we have a collision
 */
	int change = (i+1)^2;
	if (h+change>=mapSize){//in the case that we go out of bounds of the map
		return (h+change)%mapSize;
	}
	else {
		return h+change;
	}
}

int hashMap::findKey(string k) {
//NOTE: THIS METHOD CANNOT LOOP from index 0 to end of hash array looking for the key.  That destroys any efficiency in run-time.

	if(hashfn == true){
		int firstIndex = calcHash1(k);
		if((map[firstIndex]->keyword).compare("")==0){
			return -1;
		}
		else if((map[firstIndex]->keyword).compare(k)==0){
			return firstIndex;
		}
		else if(collfn == true){
			while ((map[firstIndex]!=NULL && map[firstIndex]->keyword.compare(k)!=0)){
				firstIndex = coll1(firstIndex,0,k);
			}
			if((map[firstIndex]->keyword).compare(k)==0){
				return firstIndex;
			}
			else{
				return -1;
			}
		}
		else{
			while ((map[firstIndex]!=NULL && map[firstIndex]->keyword.compare(k)!=0)){
				firstIndex = coll2(firstIndex,0,k);
			}
			if((map[firstIndex]->keyword).compare(k)==0){
				return firstIndex;
			}
			else{
				return -1;
			}
		}
	}
	else{
		int firstIndex = calcHash2(k);
		if((map[firstIndex]->keyword).compare("")==0){
			return -1;
		}
		else if((map[firstIndex]->keyword).compare(k)==0){
			return firstIndex;
		}
		else if(collfn == true){
			while ((map[firstIndex]!=NULL && map[firstIndex]->keyword.compare(k)!=0)){
				firstIndex = coll1(firstIndex,0,k);
			}
			if((map[firstIndex]->keyword).compare(k)==0){
				return firstIndex;
			}
			else{
				return -1;
			}
		}
		else{
			while ((map[firstIndex]!=NULL && map[firstIndex]->keyword.compare(k)!=0)){
				firstIndex = coll2(firstIndex,0,k);
			}
			if((map[firstIndex]->keyword).compare(k)==0){
				return firstIndex;
			}
			else{
				return -1;
			}
		}
	}



}

