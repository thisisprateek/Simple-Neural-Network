/*
 * Weight.cpp
 *
 *  Created on: 19-Aug-2018
 *      Author: prateek
 */

#include "Weight.h"

Weight::Weight(int connections) {
	// TODO Auto-generated constructor stub
	this->connections = connections;
	this->weightArray = new double[connections + 1];
	//set bias
	this->weightArray[0] = 1;
}

Weight::~Weight() {
	// TODO Auto-generated destructor stub
	delete [] this->weightArray;
}

void Weight::initialize(){
	for(int i = 1;  i <=this->connections; i++){
		this->weightArray[i] = 2.0 * (rand() - 0.5) * 13;
	}
}

void Weight::reInitialize(){
	for(int i = 1; i <= this->connections; i++){
		this->weightArray[i] = i;
	}
	for(int i = 1; i <= this->connections; i++){
		int random = i + rand() * (this->connections + 1 - i);
		int output = this->weightArray[i];
		this->weightArray[i] = this->weightArray[random];
		this->weightArray[random] = output;
	}
}

