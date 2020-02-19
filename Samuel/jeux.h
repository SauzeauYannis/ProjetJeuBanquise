#include "banquise.h"

/***** Structures *****/

//Enumeration de differentes couleur
typedef enum
{
    ROUGE,
    VERT,
    BLEU,
    JAUNE,
    ERREUR
} T_couleur;

//Definition du type vecteur
typedef struct
{
    int dx; //Vecteur x = deplacement horizontal
    int dy; //Vecteur y = deplacement vertical
} T_vecteur;

//Definition du type jeu
typedef struct
{
    T_banquise *banquise; //Pointeur sur la banquise
    int nombreJoueur;     //Nombre de joueur présent sur le jeu
    int nombreTour;       //Nombre de tour actuel du jeu
    int IdJeu;            //Identifiant de la partie en cours
} T_jeu;


/***** Fonctions *****/

//Affiche le menu du jeu
void afficheMenu();

//Initialise le jeu
T_jeu *initJeux(int niveau, int taille);

//Fait choisir une couleur a l'utilisateur
T_couleur choixCouleur();
