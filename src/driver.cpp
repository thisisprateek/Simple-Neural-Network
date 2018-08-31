/*
 * driver.cpp
 *
 *  Created on: 20-Aug-2018
 *      Author: prateek
 */

#include <iostream>
#include "NeuralNetwork.h"
#include <array>
using namespace std;

int main(){

	multimap<vector<double>, vector<double>> trainDataset, testDataset;
	vector<double> featureVector1 = {9,1};
	vector<double> outputVector1 = {1};
	//trainDataset.insert(pair<vector<double>, vector<double>>	(featureVector1, outputVector1));
	trainDataset.insert(make_pair(featureVector1, outputVector1));
	vector<double> featureVector2 = {13,1};
	vector<double> outputVector2 = {1};
	trainDataset.insert(pair<vector<double>, vector<double>>	(featureVector2, outputVector2));

	vector<double> featureVector3 = {13,0};
	vector<double> outputVector3 = {0};
	trainDataset.insert(pair<vector<double>, vector<double>>	(featureVector3, outputVector3));

	vector<double> featureVector4 = {18,1};
	vector<double> outputVector4 = {0};
	trainDataset.insert(pair<vector<double>, vector<double>>	(featureVector4, outputVector4));

	vector<double> featureVector5 = {23,1};
	vector<double> outputVector5 = {0};
	trainDataset.insert(pair<vector<double>, vector<double>>	(featureVector5, outputVector5));

	vector<double> featureVector6 = {45,0};
	vector<double> outputVector6 = {1};
	trainDataset.insert(pair<vector<double>, vector<double>>	(featureVector6, outputVector6));

	vector<double> featureVector7 = {27,1};
	vector<double> outputVector7 = {1};
	trainDataset.insert(pair<vector<double>, vector<double>>	(featureVector7, outputVector7));

	/*vector<double> featureVector8 = {8,1};
	double outputVector8 = {2};
	testDataset.insert(pair<vector<double>, vector<double>>	(featureVector8, outputVector8));

	vector<double> featureVector9 = {23,1};
	vector<double> outputVector9 = {2};
	testDataset.insert(pair<vector<double>, vector<double>>	(featureVector9, outputVector9));

	vector<double> featureVector10 = {34,1};
	vector<double> outputVector10 = {1};
	testDataset.insert(pair<vector<double>, vector<double>>	(featureVector10, outputVector10));
 */
	cout<<"\ndatasets created"<<endl;

	/*int sizeFeatureVector = sizeof(featureVector1)/sizeof(featureVector1[0]);
	cout<<"sizeof featureVector = "<<sizeFeatureVector;*/
	NeuralNetwork *nn = new NeuralNetwork();
	nn->addInputLayer(2);
	cout<<"\nInput Layer Added"<<endl;
	nn->addHiddenLayer(3);
	cout<<"\nHidden Layer Added"<<endl;
	nn->addHiddenLayer(5);
	cout<<"\nHidden Layer Added"<<endl;
	/* nn->addHiddenLayer(5);
	cout<<"\nHidden Layer Added"<<endl;
	nn->addHiddenLayer(5);
	cout<<"\nHidden Layer Added"<<endl;
	nn->addHiddenLayer(5);
	cout<<"\nHidden Layer Added"<<endl;  
	nn->addHiddenLayer(4);
	cout<<"\nHidden Layer Added"<<endl;*/
	nn->addOutputLayer(1);
	cout<<"\nOutput Layer Added"<<endl; 
	cout<<"\nTraining.."<<endl;
	nn->train(1, trainDataset);
	//nn->test(testDataset);
	delete nn;

	return 0;
}





