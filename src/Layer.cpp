/*
 * Layer.cpp
 *
 *  Created on: 18-Aug-2018
 *      Author: prateek
 */

#include "Layer.h"

Layer::Layer(int numNeurons)
{
	// TODO Auto-generated constructor stub
	this->numNeurons = numNeurons;
	for (int i = 0; i < numNeurons; i++)
	{
		//Neuron *neuron = new Neuron();
		//this->neurons.push_back(*neuron);
		this->neurons.push_back(*(new Neuron()));
	}
}
Layer::Layer(const Layer &l) : neurons(l.neurons.size())
{
	this->numNeurons = l.numNeurons;
	for (int i = 0; i < l.neurons.size(); i++)
	{
		this->neurons.push_back(*(new Neuron(l.neurons[i])));
	}
}

Layer::~Layer()
{
	//std::cout << "\nLayer's destructor called!" << std::endl;
	// TODO Auto-generated destructor stub
	for (auto neuron = this->neurons.begin(); neuron != this->neurons.end(); neuron++)
		this->neurons.erase(neuron);
}