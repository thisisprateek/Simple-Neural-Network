/*
 * Layer.h
 *
 *  Created on: 18-Aug-2018
 *      Author: prateek
 */

#ifndef SRC_LAYER_H_
#define SRC_LAYER_H_
#include <vector>
#include "Neuron.h"

class Layer {
public:
	int numNeurons;
	Layer(int numNeurons);
	Neuron *neurons;
	virtual ~Layer();
};

#endif /* SRC_LAYER_H_ */
