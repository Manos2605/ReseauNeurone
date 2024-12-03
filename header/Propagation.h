#include <iostream>
#include <cmath>
#include "NeuralNetwork.h"
#include "Struct.h"

#ifndef PROPAGATION_H
#define PROPAGATION_H

float sigmoid(float x);
// Propagation Avant
void propagation(ReseauDeNeurones* reseau, float* entree);
//retroproapagation
// Calcul de l'erreur quadratique moyenne
float calculer_MSE(float* sorties_reelles, float* sorties_predites, int taille);
void retropropagation(ReseauDeNeurones* reseau, float* sortie_reelle, float taux_apprentissage);

#endif