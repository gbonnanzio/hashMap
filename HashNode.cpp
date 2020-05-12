/*
 * HashNode.cpp
 *
 *  Created on: May 4, 2020
 *      Author: 13027
 */




#include "hashMap.hpp"
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;



hashNode::hashNode(string s){
	keyword = s;
	values = new string[100];
	valuesSize = 100;
	currSize = 0;
	srand(time(NULL));
}
hashNode::hashNode(){
	keyword = "";
	values = new string[100];
	valuesSize = 100;
	currSize = 0;
	srand(time(NULL));
}
hashNode::hashNode(string s, string v){
	keyword = s;
	values = new string[100];
	values[0] = v;
	valuesSize = 100;
	currSize = 1;
}
void hashNode::addValue(string v) {
/*Input: a string holding the word after our key
 * Output: Nothing
 * Action: adding a value to the end of the value array associated with a key
 */
	int count=0;
	while (values[count]!=""){
		//go through the values array until we reach an empty space
		count++;
	}
	values[count]=v; //place the value in the array
	currSize++;
	if (currSize==valuesSize){
		//if the values array is full call dblArray to double the size of the array
		dblArray();
	}
}
void hashNode::dblArray() {
/*Input: None
 * Output:None
 * Action: Double the size of the array and copy over old values
 */
	valuesSize= valuesSize*2;
	string *valuesTwo = new string[valuesSize];
	for (int i=0;i<(currSize);i++){ //copying over the values
		valuesTwo[i]=values[i];
	}
	delete values;
	values=valuesTwo;
}

string hashNode::getRandValue() {
/*Input: Nothing
 * Output: a string holding the randomly selected value
 * Action: Randomly choose a single value from the array of values.
 */
	int num = rand() % currSize;
	return values[num];
}
