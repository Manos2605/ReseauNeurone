#include "../header/NeuralNetwork.h"

// fonction pour générer un réel entre -1 et 1
float genererAlea() {
    return static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f;
}

// fonction pour initialiser une couche
void initialiserCouche(Couche& couche, int nombre_neurones, int nombre_poids_par_neurone) {
    couche.nombre_neurones = nombre_neurones;
    couche.neurones = new Neurone[nombre_neurones];

    for (int i = 0; i < nombre_neurones; ++i) {
        // tableau de poids pour chaque neurone
        couche.neurones[i].poids = new float[nombre_poids_par_neurone];
        
        // poids aléatoirement entre -1 et 1
        for (int j = 0; j < nombre_poids_par_neurone; ++j) {
            couche.neurones[i].poids[j] = genererAlea();
        }

        couche.neurones[i].biais = genererAlea();
        couche.neurones[i].sortie = 0.0f;
    }
}

// fonction pour initialiser un neurone
void initialiserNeurone(Neurone& neurone, int nombreConnexions) {
    neurone.poids = new float[nombreConnexions];
    for (int i = 0; i < nombreConnexions; i++) {
        neurone.poids[i] = genererAlea();
    }
    neurone.biais = genererAlea();
    neurone.sortie = 0.0f;
}

// fonction pour libérer la mémoire d'une couche
void libererCouche(Couche& couche, int nombre_poids_par_neurone) {
    for (int i = 0; i < couche.nombre_neurones; ++i) {
        // Libérer poids neurone
        delete[] couche.neurones[i].poids;
    }
    // Libérer tableau neurones
    delete[] couche.neurones;
    couche.neurones = nullptr;
    couche.nombre_neurones = 0;
}

// Fonction d'initialisation d'un réseau de neurones
void initialiserReseau(ReseauDeNeurones& reseau, const int* nombreNeuronesParCouche, int nombreCouches) {
    reseau.nombre_couches = nombreCouches;
    reseau.couches = new Couche[nombreCouches];
    for (int i = 0; i < nombreCouches; i++) {
        int connexionsParNeurone = (i == 0) ? 0 : nombreNeuronesParCouche[i - 1];
        initialiserCouche(reseau.couches[i], nombreNeuronesParCouche[i], connexionsParNeurone);
    }
}
