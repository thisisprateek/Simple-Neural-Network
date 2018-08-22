/*
 * Weight.h
 *
 *  Created on: 19-Aug-2018
 *      Author: prateek
 */

#ifndef SRC_WEIGHT_H_
#define SRC_WEIGHT_H_

#include <cstdlib>

class Weight {
public:
	int connections;
	double *weightArray;
	Weight(int connections);
	virtual ~Weight();
	void initialize();
	void reInitialize();
};

#endif /* SRC_WEIGHT_H_ */
