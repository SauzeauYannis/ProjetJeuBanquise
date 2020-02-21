#include "banquise.h"
#include "joueur.h"

/***** Structures *****/

//Definition du type jeu
typedef struct
{
    T_banquise *banquise; //Pointeur sur la banquise
    T_joueur **joueurs;   //Tableau de pointeurs de joueurs
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

//Fonction qui met un zero sur (l'ancienne) position du joueur mis en paramettre
void rafraicheBanquise(T_jeu *jeu, T_joueur *joueur, int val);

//Fonction qui s'occupe d'effectuer le tour d'un joueur
void tourJoueur(T_jeu *jeu, int numJoueur);

//Fonction qui joue un niveau sélectionné jusqu'à la victoire d'un joueur
void joueNiveau(T_jeu *jeu);
