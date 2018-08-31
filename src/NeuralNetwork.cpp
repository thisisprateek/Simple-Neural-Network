/*
 * NeuralNetwork.cpp
 *
 *  Created on: 19-Aug-2018
 *      Author: prateek
 */

#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork()
{
	// TODO Auto-generated constructor stub
	this->numNeuronsInInputLayer = 0;
	this->numNeuronsInOutputLayer = 0;
	this->numHiddenLayers = 0;
	this->numNeuronsInPreviousLayer = 0;
}

NeuralNetwork::~NeuralNetwork()
{
	// TODO Auto-generated destructor stub
	//std::cout << "\nNeuralNetwork's destructor called" << std::endl;
}

void NeuralNetwork::addInputLayer(int numNeurons)
{
	this->numNeuronsInInputLayer = numNeurons;
	Layer *layer = new Layer(numNeurons);
	this->layers.push_back(*layer);
	this->numNeuronsInPreviousLayer = numNeurons;
}

void NeuralNetwork::addHiddenLayer(int numNeurons)
{
	Layer *layer = new Layer(numNeurons);
	this->layers.push_back(*layer);
	this->numHiddenLayers++;
	Weight *weight = new Weight(this->numNeuronsInPreviousLayer * numNeurons);
	weight->initialize();
	weight->reInitialize();
	this->weights.push_back(*weight);
	this->numNeuronsInPreviousLayer = numNeurons;
}

void NeuralNetwork::addOutputLayer(int numNeurons)
{
	this->numNeuronsInOutputLayer = numNeurons;
	Layer *layer = new Layer(numNeurons);
	this->layers.push_back(*layer);
	Weight *weight = new Weight(this->numNeuronsInPreviousLayer * numNeurons);
	weight->initialize();
	weight->reInitialize();
	this->weights.push_back(*weight);
	//std::cout<<weight->connections<<std::endl;
}

void NeuralNetwork::feedForward()
{
	//Total Number of layers is numHiddenLayers + 1 input Layer + 1 output layer
	auto previousLayer = &(this->layers[0]);
	for (int i = 0; i < previousLayer->numNeurons; i++)
		std::cout << previousLayer->neurons[i].output << std::endl;

	//j for layers, k for weights
	for (int j = 1, k = 0; j < this->numHiddenLayers + 2; j++, k++)
	{
		int numNeuronsCurrentLayer = this->layers[j].numNeurons;
		int numNeuronsPreviousLayer = previousLayer->numNeurons;
		std::cout << numNeuronsPreviousLayer << " " << numNeuronsCurrentLayer
				  << " " << this->weights[k].connections << std::endl;
		for (int currentNeuronIndex = 0, weightIndex = 1;
			 currentNeuronIndex < numNeuronsCurrentLayer;
			 currentNeuronIndex++)
		{
			double sum = this->weights[k].weightArray[0];
			for (int prevLyrNurnIndx = 0;
				 prevLyrNurnIndx < numNeuronsPreviousLayer;
				 prevLyrNurnIndx++, weightIndex++)
			{
				sum += previousLayer->neurons[prevLyrNurnIndx].output * this->weights[k].weightArray[weightIndex];
			}
			this->layers[j].neurons[currentNeuronIndex].input = sum;
			this->layers[j].neurons[currentNeuronIndex].output = tanh(sum);
			std::cout << this->layers[j].neurons[currentNeuronIndex].input << " " << this->layers[j].neurons[currentNeuronIndex].output << std::endl;
		}
		previousLayer = &(this->layers[j]);
	}
	std::cout << "Feed forward finihsed" << std::endl;
	Layer *outputLyr = &(this->layers[this->numHiddenLayers + 1]);
	std::cout << outputLyr->numNeurons << std::endl;
	for (auto outputItr : outputLyr->neurons)
		std::cout << outputItr.output << " ";
}

void NeuralNetwork::backPropogate(std::vector<double> &outputVector)
{
	//SSE
	for (auto &op : outputVector)
		std::cout << op << " ";
	std::cout << std::endl;
	double error = 0.0;
	//Calculate Cost or total error
	Layer *outputLayer = &(this->layers[this->numHiddenLayers + 1]);
	for (int i = 0; i < outputLayer->numNeurons; i++)
	{
		std::cout << "output = " << outputLayer->neurons[i].output;
		error += 0.5 * squaredError(outputVector[i], outputLayer->neurons[i].output);
		/* outputLayer->neurons[i].error = (outputVector[i] - outputLayer->neurons[i].output) * sigmoidDerivative(outputLayer->neurons[i].output);
		std::cout << " expected error = " << (outputVector[i] - outputLayer->neurons[i].output) * sigmoidDerivative(outputLayer->neurons[i].output); */
		outputLayer->neurons[i].error = (outputVector[i] - outputLayer->neurons[i].output) * tanhDer(outputLayer->neurons[i].output);
		std::cout << " expected error = " << (outputVector[i] - outputLayer->neurons[i].output) * tanhDer(outputLayer->neurons[i].output);
		std::cout << " error  = " << outputLayer->neurons[i].error << std::endl;
	}

	//j for nextlayer ,k for weight and l for current layer
	//find error of each neuron in every layer except for the input layer
	for (int j = this->numHiddenLayers + 1, k = this->numHiddenLayers, l = this->numHiddenLayers; l >= 0;
		 j--, l--, k--)
	{
		Layer *currentLayer = &(this->layers[l]);
		Weight *weights = &(this->weights[k]);
		Layer *nextLayer = &(this->layers[j]);
		int weightIndex = 1;
		std::cout << "neurons in current layer: " << currentLayer->numNeurons;
		std::cout << " associated weights: " << weights->connections;
		std::cout << " neurons in next layers: " << nextLayer->numNeurons << std::endl;
		for (int crNrnIndx = 0; crNrnIndx < this->layers[l].numNeurons;
			 crNrnIndx++)
		{

			for (int nxNrnIndx = 0; nxNrnIndx < this->layers[j].numNeurons;
				 nxNrnIndx++, weightIndex++)
			{

				std::cout << "neuron error: " << this->layers[l].neurons[crNrnIndx].error;
				std::cout << " Weight " << this->weights[k].weightArray[weightIndex];
				std::cout << " Output " << this->layers[l].neurons[crNrnIndx].output;
				std::cout << " sigDer(output) " << sigmoidDerivative(this->layers[l].neurons[crNrnIndx].output);
				this->layers[l].neurons[crNrnIndx].error +=
					this->layers[j].neurons[nxNrnIndx].error * this->weights[k].weightArray[weightIndex] * sigmoidDerivative(this->layers[l].neurons[crNrnIndx].output);
				std::cout << " neuron error updated " << this->layers[l].neurons[crNrnIndx].error << std::endl;
			}
			//std::cout << this->layers[l].neurons[crNrnIndx].output << std::endl;
		}
		std::cout << std::endl;
	}

	//updating weights
	for (int l = 0, j = 1, k = 0; j <= numHiddenLayers + 1;
		 l++, j++, k++)
	{
		Layer *currentLayer = &(this->layers[l]);
		Weight *weights = &(this->weights[k]);
		Layer *nextLayer = &(this->layers[j]);
		int weightIndex = 1;
		for (int crNrnIndx = 0; crNrnIndx < currentLayer->numNeurons;
			 crNrnIndx++)
		{
			for (int nxNrnIndx = 0; nxNrnIndx < nextLayer->numNeurons;
				 nxNrnIndx++, weightIndex++)
			{
				weights->weightArray[weightIndex] +=
					currentLayer->neurons[crNrnIndx].output * nextLayer->neurons[nxNrnIndx].error;
			}
		}
	}
}

void NeuralNetwork::setInput(std::vector<double> &featureVector)
{
	auto inputLayer = &(this->layers[0]);
	for (int i = 0; i < this->numNeuronsInInputLayer; i++)
	{
		inputLayer->neurons[i].input = inputLayer->neurons[i].output = featureVector[i];
		std::cout << "input " << inputLayer->neurons[i].input << " output " << inputLayer->neurons[i].output << std::endl;
	}
}

void NeuralNetwork::train(int epochs,
						  std::multimap<std::vector<double>, std::vector<double>> trainData)
{
	for (int i = 0; i < epochs; i++)
	{
		//std::map<double*, double *>::iterator itr;
		for (auto itr = trainData.begin(); itr != trainData.end(); itr++)
		{
			std::vector<double> featureVector = itr->first;
			std::vector<double> outputVector = itr->second;
			//std::cout<<featureVector.size()<<" "<<outputVector.size()<<std::endl;
			//std::cout<<"\n"<<*featureVector.begin()<<" "<<*(featureVector.end()-1)<<" "<<*outputVector.begin()<<std::endl;
			//std::cout<<"\n"<<featureVector[0]<<" "<<featureVector[1]<<" "<<outputVector[0]<<std::endl;
			std::cout << "\nset input" << std::endl;
			this->setInput(featureVector);
			for (auto weightsItr : this->weights)
			{
				Weight weight = weightsItr;
				weight.reInitialize();
			}
			std::cout << "\nFeedforward" << std::endl;
			this->feedForward();
			std::cout << "\nbackpropogate" << std::endl;
			this->backPropogate(outputVector);
			/* for (auto weightsItr : this->weights)
			{
				Weight weight = weightsItr;
				weight.reInitialize();
			} */
		}
		std::cout << "Epoch " << i + 1 << " completed." << std::endl
				  << "\n";
	}
}

void NeuralNetwork::test(
	std::multimap<std::vector<double>, std::vector<double>> &trainData)
{
	//std::map<double *, double *>::iterator itr;
	for (auto itr = trainData.begin(); itr != trainData.end(); itr++)
	{
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
