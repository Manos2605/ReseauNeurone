#include <iostream>
#include <cstdlib>
#include <ctime>

// Structure représentant un neurone
struct Neuron {
    float* poids;   // Tableau des poids
    float biais;    // Biais du neurone
    float sortie;   // Sortie du neurone
};

// Structure représentant une couche
struct Couche {
    int nombre_neurones;  // Nombre de neurones d'une couche'
    Neuron* neurones;     // Tableau de neurones
};

#ifdef NEURALNETWORK_H
#define NEURALNETWORK_H

float genererAlea();
void initialiserCouche(Couche& couche, int nombre_neurones, int nombre_poids_par_neurone);
void libererCouche(Couche& couche, int nombre_poids_par_neurone);

#endif