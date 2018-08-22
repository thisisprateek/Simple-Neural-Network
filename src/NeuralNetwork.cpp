/*
 * NeuralNetwork.cpp
 *
 *  Created on: 19-Aug-2018
 *      Author: prateek
 */

#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(){
	// TODO Auto-generated constructor stub
	this->numNeuronsInInputLayer = 0;
	this->numNeuronsInOutputLayer = 0;
	this->numHiddenLayers = 0;
	this->numNeuronsInPreviousLayer = 0;
	//this->outputVector = NULL;
}

NeuralNetwork::~NeuralNetwork() {
	// TODO Auto-generated destructor stub
}

void NeuralNetwork::addInputLayer(int numNeurons) {
	this->numNeuronsInInputLayer = numNeurons;
	Layer *layer = new Layer(numNeurons);
	this->layers.push_back(*layer);
	this->numNeuronsInPreviousLayer = numNeurons;
}

void NeuralNetwork::addHiddenLayer(int numNeurons) {
	Layer *layer = new Layer(numNeurons);
	this->layers.push_back(*layer);
	this->numHiddenLayers++;
	Weight *weight = new Weight(this->numNeuronsInPreviousLayer * numNeurons);
	weight->initialize();
	this->weights.push_back(*weight);
	this->numNeuronsInPreviousLayer = numNeurons;
}

void NeuralNetwork::addOutputLayer(int numNeurons) {
	this->numNeuronsInOutputLayer = numNeurons;
	Layer *layer = new Layer(numNeurons);
	this->layers.push_back(*layer);
	/*Weight *weight = new Weight(this->numNeuronsInPreviousLayer * numNeurons);
	weight->initialize();
	this->weights.push_back(*weight);*/
	//std::cout<<weight->connections<<std::endl;
}

void NeuralNetwork::feedForward() {
	//Total Number of layers is numHiddenLayers + 1 input Layer + 1 output layer
	auto previousLayer = this->layers.begin();
	for (int i = 0; i < previousLayer->numNeurons; i++)
		std::cout << previousLayer->neurons[i].output << std::endl;
	auto layerIterator = (this->layers.begin() + 1);
	auto weightIterator = this->weights.begin();
	for (; layerIterator != this->layers.end();
			layerIterator++, weightIterator++) {
		auto currentLayer = layerIterator;
		auto weights = weightIterator;
		int numNeuronsCurrentLayer = currentLayer->numNeurons;
		int numNeuronsPreviousLayer = previousLayer->numNeurons;
		std::cout << numNeuronsPreviousLayer << " " << numNeuronsCurrentLayer
				<< " " << weights->connections << std::endl;
		/*for (int currentNeuronIndex = 0, weightIndex = 1;
				currentNeuronIndex < numNeuronsCurrentLayer;
				currentNeuronIndex++) {
			double sum = weights->weightArray[0];
			//for (int weightIndex = 1; weightIndex <= weights->connections;
			//		weightIndex++) {
			/*for (int prevLyrNurnIndx = 0;
					prevLyrNurnIndx < numNeuronsPreviousLayer;
					prevLyrNurnIndx++, weightIndex++) {
				sum += previousLayer->neurons[prevLyrNurnIndx].output
						* weights->weightArray[weightIndex];
				//std::cout << weights->weightArray[weightIndex] << std::endl;
			}
			//
			//}
			currentLayer->neurons[currentNeuronIndex].input = sum;
			currentLayer->neurons[currentNeuronIndex].output = sigmoid(sum);
			//std::cout<<currentLayer->neurons[currentNeuronIndex].input<<" "<<currentLayer->neurons[currentNeuronIndex].output;
		}*/
		previousLayer = currentLayer;
	}
}

void NeuralNetwork::backPropogate(std::vector<double> outputVector) {
	double error = 0.0;
	//Calculate Cost or total error
	Layer outputLayer = *(this->layers.rbegin());
	for (int i = 0; i < outputLayer.numNeurons; i++) {
		error += 0.5
				* squaredError(outputVector[i], outputLayer.neurons[i].output);
		outputLayer.neurons[i].error = (outputVector[i]
				- outputLayer.neurons[i].output)
				* sigmoidDerivative(outputLayer.neurons[i].output);
	}
	auto nextLayerIterator = this->layers.end();
	auto weightIterator = this->weights.end();
	auto currentLayerIterator = this->layers.end() - 1;
	//find error of each neuron in every layer except for the input layer
	for (; currentLayerIterator != this->layers.begin();
			nextLayerIterator--, currentLayerIterator--, weightIterator--) {
		Layer currentLayer = *currentLayerIterator;
		Weight weights = *weightIterator;
		Layer nextLayer = *nextLayerIterator;
		int weightIndex = 1;
		for (int crNrnIndx = 0; crNrnIndx < currentLayer.numNeurons;
				crNrnIndx++) {
			for (int nxNrnIndx = 0; nxNrnIndx < nextLayer.numNeurons;
					nxNrnIndx++, weightIndex++) {
				currentLayer.neurons[crNrnIndx].error +=
						nextLayer.neurons[nxNrnIndx].error
								* weights.weightArray[weightIndex]
								* sigmoidDerivative(
										currentLayer.neurons[crNrnIndx].output);
			}
		}
	}
	currentLayerIterator = this->layers.begin();
	nextLayerIterator = this->layers.begin() + 1;
	weightIterator = this->weights.begin();
	//updating weights
	for (; nextLayerIterator != this->layers.end();
			currentLayerIterator++, weightIterator++, nextLayerIterator++) {
		Weight weights = *weightIterator;
		Layer currentLayer = *currentLayerIterator;
		Layer nextLayer = *nextLayerIterator;
		int weightIndex = 1;
		for (int crNrnIndx = 0; crNrnIndx < currentLayer.numNeurons;
				crNrnIndx++) {
			for (int nxNrnIndx = 0; nxNrnIndx < nextLayer.numNeurons;
					nxNrnIndx++, weightIndex++) {
				weights.weightArray[weightIndex] +=
						currentLayer.neurons[crNrnIndx].output
								* nextLayer.neurons[nxNrnIndx].error;
			}
		}
	}
}

void NeuralNetwork::setInput(std::vector<double> featureVector) {
	auto inputLayer = this->layers.begin();
	auto featureVectorItr = featureVector.begin();
	for (int i = 0; i < this->numNeuronsInInputLayer; i++) {
		inputLayer->neurons[i].input = inputLayer->neurons[i].output =
				*(featureVectorItr++);
	}
}

void NeuralNetwork::train(int epochs,
		std::multimap<std::vector<double>, std::vector<double>> trainData) {
	for (int i = 0; i < epochs; i++) {
		//std::map<double*, double *>::iterator itr;
		for (auto itr = trainData.begin(); itr != trainData.end(); itr++) {
			std::vector<double> featureVector = itr->first;
			std::vector<double> outputVector = itr->second;
			//std::cout<<featureVector.size()<<" "<<outputVector.size()<<std::endl;
			//std::cout<<"\n"<<*featureVector.begin()<<" "<<*(featureVector.end()-1)<<" "<<*outputVector.begin()<<std::endl;
			//std::cout<<"\n"<<featureVector[0]<<" "<<featureVector[1]<<" "<<outputVector[0]<<std::endl;
			this->setInput(featureVector);
			this->feedForward();
			/*this->backPropogate(outputVector);
			 for (auto weightsItr : this->weights) {
			 Weight weight = weightsItr;
			 weight.reInitialize();
			 }*/
		}
	}
}

void NeuralNetwork::test(
		std::multimap<std::vector<double>, std::vector<double>> &trainData) {
	//std::map<double *, double *>::iterator itr;
	for (auto itr = trainData.begin(); itr != trainData.end(); itr++) {
		std::vector<double> featureVector = itr->first;
		std::vector<double> outputVector = itr->second;
		/*		this->setInput(featureVector);
		 this->feedForward();
		 for (int i = 0; i < this->numNeuronsInOutputLayer; i++) {
		 std::cout << " " << outputVector[i] << std::endl;
		 }
		 std::cout << "\t";
		 Layer outputLayer = *(this->layers.end());
		 for (int i = 0; i < this->numNeuronsInOutputLayer; i++) {
		 std::cout << " ";
		 std::cout << outputLayer.neurons[i].output;
		 }*/
	}
}
