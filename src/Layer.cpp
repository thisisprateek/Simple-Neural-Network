/*
 * Layer.cpp
 *
 *  Created on: 18-Aug-2018
 *      Author: prateek
 */

#include "Layer.h"

Layer::Layer(int numNeurons) {
	// TODO Auto-generated constructor stub
	this->numNeurons = numNeurons;
	this->neurons = new Neuron[numNeurons];
}

Layer::~Layer() {
	// TODO Auto-generated destructor stub
	delete [] this->neurons;
}

