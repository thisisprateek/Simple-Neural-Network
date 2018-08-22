#include "ActivationFunctions.h"

double sigmoid(double input){
	return 1/(1 + exp(-input));
}

double sigmoidDerivative(double input){
	return input * (1 - input);
}
