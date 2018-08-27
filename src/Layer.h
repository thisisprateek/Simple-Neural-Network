/*
 * Layer.h
 *
 *  Created on: 18-Aug-2018
 *      Author: prateek
 */

#ifndef SRC_LAYER_H_
#define SRC_LAYER_H_
#include <vector>
#include <iostream>
#include "Neuron.h"

class Layer {
public:
	int numNeurons;
	Layer(int numNeurons);
	//Neuron *neurons;
	std::vector<Neuron> neurons;
	virtual ~Layer();
	Layer(const Layer &l);
};

#endif /* SRC_LAYER_H_ */
