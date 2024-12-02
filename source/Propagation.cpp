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

#include <cmath>
#include <iostream>

// Fonction pour calculer l'erreur quadratique moyenne (MSE)
float calculer_MSE(float* sorties_reelles, float* sorties_predites, int taille) {
    float somme_erreurs = 0.0f;
    for (int i = 0; i < taille; ++i) {
        float erreur = sorties_predites[i] - sorties_reelles[i];
        somme_erreurs += erreur * erreur;
    }
    return somme_erreurs / taille;
}

// Rétropropagation
void retropropagation(ReseauDeNeurones* reseau, float* sortie_reelle, float taux_apprentissage) {
    int couche_sortie = reseau->nombre_couches - 1;

    // Calcul de l'erreur pour la couche de sortie
    for (int n = 0; n < reseau->couches[couche_sortie].nombre_neurones; ++n) {
        Neurone* neurone = &reseau->couches[couche_sortie].neurones[n];
        float sortie = neurone->sortie;
        neurone->delta = (sortie - sortie_reelle[n]) * sortie * (1 - sortie); // δ = (ŷ - y) · f'(x)
    }

    // Rétropropagation vers les couches précédentes
    for (int c = couche_sortie - 1; c >= 0; --c) {
        Couche* couche_actuelle = &reseau->couches[c];
        Couche* couche_suivante = &reseau->couches[c + 1];

        for (int n = 0; n < couche_actuelle->nombre_neurones; ++n) {
            Neurone* neurone = &couche_actuelle->neurones[n];
            float somme_erreurs = 0.0f;

            // Calcul de l'erreur propagée à partir de la couche suivante
            for (int ns = 0; ns < couche_suivante->nombre_neurones; ++ns) {
                somme_erreurs += couche_suivante->neurones[ns].poids[n] * couche_suivante->neurones[ns].delta;
            }

            neurone->delta = somme_erreurs * neurone->sortie * (1 - neurone->sortie); // δ = (δ(l) · poids(l)^T) · f'(sortie(l-1))
        }
    }

    // Mise à jour des poids et des biais
    for (int c = 1; c < reseau->nombre_couches; ++c) {
        Couche* couche_actuelle = &reseau->couches[c];
        Couche* couche_precedente = &reseau->couches[c - 1];

        for (int n = 0; n < couche_actuelle->nombre_neurones; ++n) {
            Neurone* neurone = &couche_actuelle->neurones[n];

            // Mettre à jour les poids
            for (int p = 0; p < couche_precedente->nombre_neurones; ++p) {
                neurone->poids[p] -= taux_apprentissage * neurone->delta * couche_precedente->neurones[p].sortie; // poids[i] ← poids[i] − η · δ · entrée[i]
            }

            // Mettre à jour le biais
            neurone->biais -= taux_apprentissage * neurone->delta; // biais ← biais − η · δ
        }
    }
}

