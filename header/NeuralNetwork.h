#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Struct.h"

#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

float genererAlea();
// Couche
void libererCouche(Couche& couche, int nombre_poids_par_neurone);
void initialiserNeurone(Neurone& neurone, int nombreConnexions);
void initialiserCouche(Couche& couche, int nombre_neurones, int nombre_poids_par_neurone);
// réseau de neurones
void initialiserReseau(ReseauDeNeurones& reseau, const int* nombreNeuronesParCouche, int nombreCouches);
void afficherReseau(const ReseauDeNeurones& reseau);
void libererReseau(ReseauDeNeurones& reseau);   

#endif