/*
 * HashMap.cpp
 *
 *  Created on: May 4, 2020
 *      Author: 13027
 * TA Name: Chunbo Song
 * Partners: Nicholas Samulewicz, Geoff Bonnanzio, Chloe Griffiths
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
/*Input: A string holding the key value
 * Output: An integer of the corresponding hashed index
 * Action: Base 27 Hash function to calculate the index for the placement.
 */
	int length = k.size();
	int sum = 0;
	int templength;

	//if the word is 1 or 2 chars long use all letters
	if (length<3){
		templength=length;
	}
	//else use the first three letters
	else {
		templength = 3;
	}
	for(int i = 0; i<templength; i++){ //go through and sum using the base 27 rule
		sum = sum + pow(27,i)*(int)k[i];
	}
	int hash = sum%mapSize; //mod to be within the map size range
	return hash;
}
int hashMap::calcHash1(string k){
/*Input: A string holding the key value
 * Output: An integer of the corresponding hashed index
 * Action: power hash of the first three letters.
 */
	int length = k.size();
	int sum = 0;
	int templength;
	//if the word is 1 or 2 chars long use all letters
	if (length<3){
		templength=length;
	}
	//else use the first three letters
	else {
		templength = 3;
	}
	for(int i = 0; i<templength; i++){//go through and sum using the power rule
		sum = sum + pow((int)k[i],i+1);
	}
	int hash = sum%mapSize; //mod to be within the map size range
	return hash;
}


void hashMap::getClosestPrime() {
/*Input: None
 * Output: None
 * Action: Find the closest prime to the current mapSize and make that the new mapSize
 */
	int testNum = mapSize;
	bool nofactors = true;
	while (nofactors){
		testNum++;
		bool interiorfactors = false;
		for (int i = 2; i<testNum; i++){
			//if the test number has a factor we set the flag to true
			if (testNum%i==0){
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
	//store all of the information in the current map to a temp map
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

	//iterate through all of the nodes in the old map and place their info in the new one with new indices
	for(int i=0;i<temp;i++){
		if (oldHashMap[i]!=NULL){ //if the old hash map had info at this node add it to new map
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
	if (h+1==mapSize){ //in the case that we go out of bounds of the map so we start probing from index 0
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
	if (h+change>=mapSize){//in the case that we go out of bounds of the map so we start at a different spot
		return (h+change)%mapSize;
	}
	else {
		return h+change;
	}
}

int hashMap::findKey(string k) {
/* Special Note: This code is never actually used in the program. Basically we found a way where this function was not
 * needed because most of the work is done in getIndex. We asked Professor Yarrington about it, and she said this was an
 * acceptable approach to complete the project.
 * Input: A string containing the value of the key
 * Output: An integer indicating a location of where the key is in the map
 * Action: Find the location of an integer in the map, or indicate if it does not exist
 */
	if(hashfn == true){
		int firstIndex = calcHash1(k);
		if((map[firstIndex]->keyword).compare("")==0){ //if the space is empty
			return -1;
		}
		else if((map[firstIndex]->keyword).compare(k)==0){ //if the space contains the key
			return firstIndex;
		}
		else if(collfn == true){ //in the cases of a collision
			while ((map[firstIndex]!=NULL && map[firstIndex]->keyword.compare(k)!=0)){ //running through the collision function
				firstIndex = coll1(firstIndex,0,k);
			}
			if((map[firstIndex]->keyword).compare(k)==0){
				return firstIndex;
			}
			else{
				return -1;
			}
		}
		else{ //cases of a collision
			while ((map[firstIndex]!=NULL && map[firstIndex]->keyword.compare(k)!=0)){  //running through the collision function
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
		if((map[firstIndex]->keyword).compare("")==0){ //if the space is empty
			return -1;
		}
		else if((map[firstIndex]->keyword).compare(k)==0){ //if the space holds our key
			return firstIndex;
		}
		else if(collfn == true){ //in the cases of a collision
			while ((map[firstIndex]!=NULL && map[firstIndex]->keyword.compare(k)!=0)){  //running through the collision function
				firstIndex = coll1(firstIndex,0,k);
			}
			if((map[firstIndex]->keyword).compare(k)==0){
				return firstIndex;
			}
			else{
				return -1;
			}
		}
		else{//in the cases of a collision
			while ((map[firstIndex]!=NULL && map[firstIndex]->keyword.compare(k)!=0)){  //running through the collision function
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

