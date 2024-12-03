#ifndef __STRUCT_H__
#define __STRUCT_H__

// Structure représentant un neurone
struct Neurone {
    float* poids;   // Tableau des poids
    float biais;    // Biais du neurone
    float sortie;   // Sortie du neurone
    float delta;    // L'erreur calculée lors de la rétropropagation
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

#endif