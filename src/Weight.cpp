/*
 * Weight.cpp
 *
 *  Created on: 19-Aug-2018
 *      Author: prateek
 */

#include "Weight.h"

Weight::Weight(int connections)
{
	// TODO Auto-generated constructor stub
	this->connections = connections;
	this->weightArray.push_back(1.0L);
	//this->weightArray = new double[connections + 1];
	//set bias
	//this->weightArray[0] = 1;
}
Weight ::Weight(const Weight &w) : weightArray(w.weightArray.size())
{
	this->connections = w.connections;
	//std::cout << "\nWeights copy constructor..\n";
	for (int i = 0; i < w.weightArray.size(); i++)
	{
		this->weightArray[i] = w.weightArray[i];
	}
}
Weight::~Weight()
{
	// TODO Auto-generated destructor stub
	//delete [] this->weightArray;
	//std::cout<<"\nWeight's destructor called"<<std::endl;
	for (auto weight = this->weightArray.begin(); weight != this->weightArray.end(); weight)
		this->weightArray.erase(weight);
}

void Weight::initialize()
{
	for (int i = 1; i <= this->connections; i++)
	{
		this->weightArray.push_back(2.0 * (rand() - 0.5) * 13);
	}
}

void Weight::reInitialize()
{
	std::cout << "\n";
	for (int i = 0; i <= this->connections; i++)
	{
		std::cout << " " << weightArray[i];
		//this->weightArray[i] = i;
	}
	std::cout << std::endl;
	/* for(int i = 1; i <= this->connections; i++){
		int random = i + rand() * (this->connections + 1 - i);
		int output = this->weightArray[i];
		this->weightArray[i] = this->weightArray[random];
		this->weightArray[random] = output;
	} */
}
