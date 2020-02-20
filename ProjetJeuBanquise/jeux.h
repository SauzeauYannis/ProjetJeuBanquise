#include "banquise.h"
#include "joueur.h"

/***** Structures *****/

//Definition du type etat
typedef enum
{
    ENCOURS,
    PERDU,
    GAGNE
} T_etat;

//Definition du type jeu
typedef struct
{
    T_banquise *banquise; //Pointeur sur la banquise
    T_joueur **joueurs;   //Tableau de pointeurs de joueurs
    T_etat etat;          //Etat du jeu
    int nombreJoueur;     //Nombre de joueur présent sur le jeu
    int nombreTour;       //Nombre de tour actuel du jeu
    int IdJeu;            //Identifiant de la partie en cours
} T_jeu;


/***** Fonctions *****/

//Affiche le menu du jeu
void afficheMenu();

//Change la couleur du texte
void changeCouleurTexte(T_couleur couleur);

//Ajoute des joueurs sur la banquise
void ajouteJoueurs(T_jeu *jeu);

//Initialise le jeu
T_jeu *initJeux(int niveau, int taille);

//void joueTour(T_jeu *jeu, T_joueur *joueur);

//Affiche le jeu
void afficheJeu(T_jeu *jeu);
