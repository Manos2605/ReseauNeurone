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

// Fonction d'initialisation d'un réseau de neurones
void initialiserReseau(ReseauDeNeurones& reseau, const int* nombreNeuronesParCouche, int nombreCouches) {
    reseau.nombre_couches = nombreCouches;
    reseau.couches = new Couche[nombreCouches];
    for (int i = 0; i < nombreCouches; i++) {
        int connexionsParNeurone = (i == 0) ? 0 : nombreNeuronesParCouche[i - 1];
        initialiserCouche(reseau.couches[i], nombreNeuronesParCouche[i], connexionsParNeurone);
    }
}

// Fonction pour afficher les poids et les biais
void afficherReseau(const ReseauDeNeurones& reseau) {
    for (int i = 0; i < reseau.nombre_couches; i++) {
        std::cout << "Couche " << i + 1 << " :\n";
        for (int j = 0; j < reseau.couches[i].nombre_neurones; j++) {
            std::cout << "  Neurone " << j + 1 << " :\n";
            std::cout << "    Biais : " << reseau.couches[i].neurones[j].biais << "\n";
            std::cout << "    Poids : ";
            for (int k = 0; k < (i == 0 ? 0 : reseau.couches[i - 1].nombre_neurones); k++) {
                std::cout << reseau.couches[i].neurones[j].poids[k] << " ";
            }
            std::cout << "\n";
        }
    }
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

// fonction pour libérer la mémoire du reseau
void libererReseau(ReseauDeNeurones& reseau) {
    for (int i = 0; i < reseau.nombre_couches; i++) {
        for (int j = 0; j < reseau.couches[i].nombre_neurones; j++) {
            delete[] reseau.couches[i].neurones[j].poids; // Libère les poids de chaque neurone
        }
        delete[] reseau.couches[i].neurones; // Libère les neurones de chaque couche
    }
    delete[] reseau.couches; // Libère les couches du réseau
}

// Sauvergarde du Modèle
void sauvegarderPoidsEtBiais(const ReseauDeNeurones& reseau, const std::string& nomFichier) {
    std::ofstream fichier(nomFichier);

    // Vérifier si le fichier existe ou pas
    if (!fichier.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << nomFichier << " pour la sauvegarde." << std::endl;
        return;
    }

    for (int i = 0; i < reseau.nombre_couches; ++i) {
        const Couche& couche = reseau.couches[i];
        for (int j = 0; j < couche.nombre_neurones; ++j) {
            const Neurone& neurone = couche.neurones[j];

            // Poids
            for (int k = 0; k < (i == 0 ? 0 : reseau.couches[i - 1].nombre_neurones); ++k) {
                fichier << neurone.poids[k] << " ";
            }

            // Biais
            fichier << neurone.biais << std::endl;
        }
    }

    fichier.close();
    std::cout << "Les poids et biais ont été sauvegardés sur : " << nomFichier << std::endl;
}