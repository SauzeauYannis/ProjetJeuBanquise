#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

/***** Structures *****/

typedef enum
{
    GLACE,
    JOUEUR,
    DEPART,
    ARRIVE,
    GLACON,
    EAU
} T_case;

//Enumeration de differentes couleur
typedef enum
{
    ROUGE,
    VERT,
    BLEU,
    JAUNE,
    TURQUOISE,
    ROSE,
    GRIS,
    BLANC
} T_couleur;


//Definition du type point qui represente la case d'une banquise
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

#include "banquise.h"
#include "joueur.h"
#include "glacon.h"

//Definition du type jeu
typedef struct
{
    T_banquise *banquise; //Pointeur sur la banquise
    T_joueur **joueurs;   //Tableau de pointeurs de joueurs
    T_glacon **glacons;    //Tableau de pointeurs de glaçons
    int nombreJoueur;     //Nombre de joueur présent sur le jeu
    int nombreGlacon;     //Nombre de glaçon présent sur le jeu
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


//Affiche le jeu
void afficheJeu(T_jeu *jeu);


//Fonction qui met un zero sur (l'ancienne) position du joueur mis en paramettre
void rafraicheBanquise(T_jeu *jeu, T_joueur *joueur, T_case val);


//Fonction qui s'occupe d'effectuer le tour d'un joueur
int tourJoueur(T_jeu *jeu, int numJoueur);


//Ressort un entier qui détermine si la partie est finie ou non
int victoire(T_jeu *jeu, int caseVal, int i);


//Affiche le scrore à la fin de la partie
void afficheScore(T_jeu *jeu);


//Fonction qui retourne le glaçon sur lequel le joueur va buter
/*T_glacon *returnGlaconJoueur(T_joueur **glacons, int posX, int posY, int nbGlacons);*/


//Fonction qui joue un niveau sélectionné jusqu'à la victoire d'un joueur
void joueNiveau(T_jeu *jeu);


//Fonction qui renvoie un entier qui permet de rejouer une partie
int rejouer();


//Ajoute un glaçon sur la banquise
void ajouteGlacon(T_jeu *jeu);


//S'occupe du déplacement du glaçon après que celui-ci se soit fait pousser par un joueur
void joueurPousseGlacon(T_joueur *joueur, T_glacon *glacon, T_jeu *jeu);

