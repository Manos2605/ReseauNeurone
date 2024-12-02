#include "../header/Propagation.h"

// fonction sigmoïde
float sigmoid(float x) {
    return 1.0f / (1.0f + std::exp(-x));
}

// Fonction pour effectuer une propagation avant
void propagation(ReseauDeNeurones* reseau, float* entree) {
    // Sorties de la première couche (entrée)
    for (int i = 0; i < reseau->couches[0].nombre_neurones; ++i) {
        reseau->couches[0].neurones[i].sortie = entree[i];
    }

    // Propagation sur toutes les couches en retirant la couche d'entrée
    for (int c = 1; c < reseau->nombre_couches; ++c) {
        Couche* couche_precedente = &reseau->couches[c - 1];
        Couche* couche_actuelle = &reseau->couches[c];

        for (int n = 0; n < couche_actuelle->nombre_neurones; ++n) {
            Neurone* neurone_actuel = &couche_actuelle->neurones[n];

            // somme pondérée des entrées
            float somme = 0.0f;
            for (int p = 0; p < couche_precedente->nombre_neurones; ++p) {
                somme += neurone_actuel->poids[p] * couche_precedente->neurones[p].sortie;
            }

            // ajouter le biais
            somme += neurone_actuel->biais;

            // appliquer la fonction d'activation sigmoïde
            neurone_actuel->sortie = sigmoid(somme);
        }
    }
}