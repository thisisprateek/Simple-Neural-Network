/*
 * Weight.h
 *
 *  Created on: 19-Aug-2018
 *      Author: prateek
 */

#ifndef SRC_WEIGHT_H_
#define SRC_WEIGHT_H_

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Weight {
public:
	int connections;
	//double *weightArray;
	std::vector<double> weightArray;
	Weight(int connections);
	virtual ~Weight();
	void initialize();
	void reInitialize();
	Weight(const Weight &w);
	
};

#endif /* SRC_WEIGHT_H_ */
