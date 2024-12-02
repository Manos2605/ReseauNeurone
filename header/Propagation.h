#include <iostream>
#include <cmath>
#include "NeuralNetwork.h"

#ifdef PROPAGATION_H
#define PROPAGATION_H

float sigmoid(float x);
void propagation(ReseauDeNeurones* reseau, float* entree);

#endif