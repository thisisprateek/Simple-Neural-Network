/*
 * ErrorFunctions.cpp
 *
 *  Created on: 19-Aug-2018
 *      Author: prateek
 */
#include "ErrorFunctions.h"

double squaredError(double actual, double predicted){
	return 0.5 * pow((actual - predicted), 2);
}



