/*
 * Neuron.h
 *
 *  Created on: 18-Aug-2018
 *      Author: prateek
 */

#ifndef SRC_NEURON_H_
#define SRC_NEURON_H_

class Neuron {
private:
public:
	double input, output;
	double error;
	Neuron();
	virtual ~Neuron();
};

#endif /* SRC_NEURON_H_ */
