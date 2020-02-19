#include "banquise.h"

/***** Structures *****/

//Enumeration de differentes couleur
typedef enum
{
    ROUGE,
    VERT,
    BLEU,
    JAUNE
} T_couleur;

//Definition du type point
typedef struct
{
    int x; //Point x = horizontal
    int y; //Point y = vertical
} T_point;

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

T_jeu *initJeux(int niveau, int taille);
