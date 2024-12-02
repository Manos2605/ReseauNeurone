#include <iostream>
#include <cstdlib>
#include <ctime>

// Structure représentant un neurone
struct Neurone {
    float* poids;   // Tableau des poids
    float biais;    // Biais du neurone
    float sortie;   // Sortie du neurone
};

// Structure représentant une couche
struct Couche {
    int nombre_neurones;  // Nombre de neurones d'une couche'
    Neurone* neurones;     // Tableau de neurones
};

// Stucture représentant un reseau de neurone
struct ReseauDeNeurones{
    int nombre_couches;
    Couche *couches;
};


#ifdef NEURALNETWORK_H
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