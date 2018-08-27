/*
 * Neuron.cpp
 *
 *  Created on: 18-Aug-2018
 *      Author: prateek
 */

#include "Neuron.h"

Neuron::Neuron() {
	// TODO Auto-generated constructor stub
	this->input = 0.0;
	this->output = 0.0;
	this->error = 0.0;
}
Neuron::Neuron(const Neuron &n)
{
	this->error=n.error;
	this->input=n.input;
	this->output=n.output;
}
Neuron::~Neuron() {
	// TODO Auto-generated destructor stub
}
