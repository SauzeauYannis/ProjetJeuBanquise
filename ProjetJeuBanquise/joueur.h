#include "jeux.h"

/***** Structures *****/

//Definition du type joueur
typedef struct
{
    char nom[20];       //Nom du joueur limite a 20 caractere
    T_couleur couleur;  //Couleur du joueur
    int identifiant;    //Entier qui identifie le joueur
    T_point position;   //Position du joueur dans la banquise
    T_vecteur vecteur;  //Deplacement du joueur sur la banquise
    int score;          //Score du joueur
} T_joueur;

/***** Fonctions *****/

//Ajoute un joueur sur la banquise
void ajouteJoueur(T_banquise *banquise);
