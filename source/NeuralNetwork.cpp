#include "../header/NeuralNetwork.h"

// fonction pour générer un float entre -1 et 1
float genererAlea() {
    return static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f;
}

// fonction pour initialiser une couche
void initialiserCouche(Couche& couche, int nombre_neurones, int nombre_poids_par_neurone) {
    couche.nombre_neurones = nombre_neurones;
    couche.neurones = new Neuron[nombre_neurones];

    for (int i = 0; i < nombre_neurones; ++i) {
        // tableau de poids pour chaque neurone
        couche.neurones[i].poids = new float[nombre_poids_par_neurone];
        
        // poids aléatoirement entre -1 et 1
        for (int j = 0; j < nombre_poids_par_neurone; ++j) {
            couche.neurones[i].poids[j] = genererAlea();
        }

        // biais aléatoirement entre -1 et 1
        couche.neurones[i].biais = genererAlea();
        
        // ortie à 0
        couche.neurones[i].sortie = 0.0f;
    }
}

// fonction pour libérer la mémoire d'une couche
void libererCouche(Couche& couche, int nombre_poids_par_neurone) {
    for (int i = 0; i < couche.nombre_neurones; ++i) {
        // Libérer le tableau de poids pour chaque neurone
        delete[] couche.neurones[i].poids;
    }
    // Libérer le tableau de neurones
    delete[] couche.neurones;
    couche.neurones = nullptr;
    couche.nombre_neurones = 0;
}