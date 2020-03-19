#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>


/***** Structures *****/


//Enumeration des cases de la banquise
typedef enum
{
    ERREUR = -1,
    GLACE,
    JOUEUR,
    DEPART,
    ARRIVE,
    GLACON,
    EAU,
    ROCHER,
    RESSORT,
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
    BLEUFONCE,
    NOIR,
    MARRON,
    BLANC,
    DEFAULT
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
#include "rocher.h"
#include "ressort.h"
#include "piege.h"


//Definition du type jeu
typedef struct
{
    T_banquise *banquise; //Pointeur sur la banquise
    T_joueur **joueurs;   //Tableau de pointeurs de joueurs
    T_glacon **glacons;   //Tableau de pointeurs de glacons
    T_rocher *rochers;    //Tableau de rochers
    T_ressort *ressorts;  //Tableau de ressort
    int nombreJoueur;     //Nombre de joueurs present sur le jeu
    int nombreGlacon;     //Nombre de glacons present sur le jeu
    int nombreRochers;    //Nombre de rochers present sur le jeu
    int nombreRessorts;   //Nombre de ressorts present sur le jeu
    int nombreTour;       //Nombre de tour actuel du jeu
    int rechauffement;    //Probabilite de fonte de la banquise comme du glacon
    int probPiege;
    int IdJeu;            //Identifiant de la partie en cours
} T_jeu;


/***** Fonctions *****/

//Affiche le menu du jeu
void afficheMenu();


//Change la couleur de la console
void changeCouleurConsole(T_couleur couleur);


//Change la couleur du texte
void changeCouleurTexte(T_couleur couleur);


//Ajoute des joueurs sur la banquise
void ajouteJoueurs(T_jeu *jeu);


//Ajoute des glacons sur la banquise
void ajouteGlacons(T_jeu *jeu);


//Ajoute des rochers sur la banquise
void ajouteRochers(T_jeu *jeu);


//Ajoute des ressorts sur la banquise
void ajouteRessorts(T_jeu *jeu);


//Initialise le jeu
T_jeu *initJeux(int niveau, int tailleN, int tailleEau, int nombreGlacons, int nombreRochers, int nombreRessorts, int chanceFonte, int chancePiege);


//Affiche le jeu
void afficheJeu(T_jeu *jeu);


//S'occupe du deplacement du glacon apres que celui-ci se soit fait pousser par un joueur
void joueurPousseGlacon(T_joueur *joueur, T_glacon *glacon, T_jeu *jeu);


//S'occupe de la fonte d'un glacon
void fonteGlacon(T_jeu *jeu);


//S'occupe d'effectuer le tour d'un joueur
int tourJoueur(T_jeu *jeu, int numJoueur);


//Retourne un entier qui determine si la partie est finie ou non
int victoire(T_jeu *jeu, int caseVal, int i);


//Affiche le scrore à la fin de la partie
void afficheScore(T_jeu *jeu);


//Fonction qui joue un niveau selectionne jusqu'à la victoire d'un joueur
void joueNiveau(T_jeu *jeu);


//Fonction qui renvoie un entier qui permet de rejouer une partie
int rejouer();
