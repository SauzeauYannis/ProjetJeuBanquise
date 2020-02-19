#include "banquise.h"
#include "joueur.h"

/***** Structures *****/

//Definition du type jeu
typedef struct
{
    T_banquise *banquise; //Pointeur sur la banquise
    T_joueur **joueurs;
    int nombreJoueur;     //Nombre de joueur présent sur le jeu
    int nombreTour;       //Nombre de tour actuel du jeu
    int IdJeu;            //Identifiant de la partie en cours
} T_jeu;


/***** Fonctions *****/

//Affiche le menu du jeu
void afficheMenu();

//Ajoute des joueurs sur la banquise
void ajouteJoueurs(T_jeu *jeu);

//Initialise le jeu
T_jeu *initJeux(int niveau, int taille);
