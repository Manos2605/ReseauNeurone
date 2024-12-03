#include <iostream>
#include "header/NeuralNetwork.h"
#include "header/Propagation.h"
#include "header/Struct.h"

#define EPOCHS 10000
#define LEARNING_RATE 0.1

int main() {
    // Initialisation des paramètres
    int nombreNeuronesParCouche[] = {2, 2, 1};
    int nombreCouches = 3;

    // Initialiser le réseau
    ReseauDeNeurones reseau;
    initialiserReseau(reseau, nombreNeuronesParCouche, nombreCouches);

    // données XOR
    float entrees[4][2] = {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1}
    };

    float sortiesAttendues[4] = {0, 1, 1, 0};

    // Entraînement
    for (int epoch = 0; epoch < EPOCHS; ++epoch) {
        float erreurTotale = 0;

        for (int i = 0; i < 4; ++i) {
            // Propagation avant
            propagation(&reseau, entrees[i]);

            // Calcul de l'erreur
            float erreur = calculer_MSE(&sortiesAttendues[i],
                                        &reseau.couches[nombreCouches - 1].neurones[0].sortie, 1);
            erreurTotale += erreur;

            // Rétropropagation
            retropropagation(&reseau, &sortiesAttendues[i], LEARNING_RATE);
        }

        // erreur moyenne pour chaque époque
        if (epoch % 1000 == 0) {
            std::cout << "Epoch " << epoch << ", Erreur Totale: " << erreurTotale / 4 << std::endl;
        }
    }

    // Test du réseau
    std::cout << "\nTest du réseau XOR:\n";
    for (int i = 0; i < 4; ++i) {
        propagation(&reseau, entrees[i]);
        std::cout << "Entrées: " << entrees[i][0] << ", " << entrees[i][1]
                  << " -> Sortie: " << reseau.couches[nombreCouches - 1].neurones[0].sortie
                  << " (Attendue: " << sortiesAttendues[i] << ")\n";
    }

    // Libérer la mémoire
    libererReseau(reseau);

    return 0;
}