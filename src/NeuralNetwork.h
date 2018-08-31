/*
 * NeuralNetwork.h
 *
 *  Created on: 19-Aug-2018
 *      Author: prateek
 */

#ifndef SRC_NEURALNETWORK_H_
#define SRC_NEURALNETWORK_H_

#include "Neuron.h"
#include "Layer.h"
#include "Weight.h"
#include "ErrorFunctions.h"
#include "ActivationFunctions.h"
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <math.h>

class NeuralNetwork
{
  public:
	int numNeuronsInInputLayer, numHiddenLayers, numNeuronsInOutputLayer;
	//int *outputVector;
	int numNeuronsInPreviousLayer;
	std::vector<Layer> layers;
	std::vector<Weight> weights;

	NeuralNetwork();

	void addInputLayer(int numNeurons);
	void addHiddenLayer(int numNeurons);
	void addOutputLayer(int numNeurons);
	void feedForward();
	void backPropogate(std::vector<double> &outputVector);
	void setInput(std::vector<double> &featureVector);
	//void train(int epochs, std::map <double *, double *> trainData);
	void train(int epochs, std::multimap<std::vector<double>, std::vector<double>> &trainData);
	void test(std::multimap<std::vector<double>, std::vector<double>> &testData);

	virtual ~NeuralNetwork();
};

#endif /* SRC_NEURALNETWORK_H_ */
