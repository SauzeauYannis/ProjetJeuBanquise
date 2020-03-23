#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>


/***** Structures *****/


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
    KAKI,
    BLANC,
    DEFAULT
} T_couleur;


//Enumeration d'un booleen
typedef enum
{
    FAUX,
    VRAI
} T_booleen;


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
    MARTEAU_CENTRE,
    MARTEAU_TETE,
} T_case;


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
#include "marteau.h"
#include "piege.h"
#include "ressort.h"
#include "rocher.h"


//Definition du type jeu
typedef struct
{
    T_banquise *banquise; //Pointeur sur la banquise
    T_joueur **joueurs;   //Tableau de pointeurs de joueurs
    T_glacon **glacons;   //Tableau de pointeurs de glacons
    T_marteau **marteaux;  //Tableau de marteaux
    T_ressort *ressorts;  //Tableau de ressort
    T_rocher *rochers;    //Tableau de rochers
    int nombreJoueurs;    //Nombre de joueurs present sur le jeu
    int nombreGlacons;    //Nombre de glacons present sur le jeu
    int nombreMarteaux;   //Nombre de marteaux present sur le jeu
    int nombreRessorts;   //Nombre de ressorts present sur le jeu
    int nombreRochers;    //Nombre de rochers present sur le jeu
    int nombreTour;       //Nombre de tour actuel du jeu
    int rechauffement;    //Probabilite de fonte de la banquise comme du glacon
    int probPiege;        //Probabilite de tomber dans un piege
    int IdJeu;            //Identifiant de la partie en cours
} T_jeu;


/***** Fonctions *****/

//Affiche le menu du jeu
void afficheMenu(T_booleen debut);


//Change la couleur de la console
void changeCouleurConsole(T_couleur couleur);


//Change la couleur du texte
void changeCouleurTexte(T_couleur couleur);


//
T_booleen **tabChemin(int taille);


//
T_booleen verifieChemin(T_jeu *jeu, T_booleen **tab, int caseX, int caseY, T_booleen affichage);


//
T_booleen verifieCheminJoueurs(T_jeu *jeu, T_booleen **tab, T_booleen affichage);


//Initialise le jeu
T_jeu *initJeux(int niveau, int tailleN, int tailleEau, int nombreGlacons, int nombreMarteaux, int nombreRessorts, int nombreRochers, int chanceFonte, int chancePiege);


//
void reInitJeux(T_jeu *jeu);


//Affiche le jeu
void afficheJeu(T_jeu *jeu);


//
char saisieTouche(T_joueur *joueur, T_booleen bug);


//S'occupe du deplacement du glacon apres que celui-ci se soit fait pousser par un joueur
void joueurPousseGlacon(T_joueur *joueur, T_glacon *glacon, T_jeu *jeu);


//S'occupe de la fonte d'un glacon
void fonteGlacon(T_jeu *jeu);


//
void bougeTeteMarteau(T_jeu *jeu, T_marteau *marteau, T_booleen sensHorraire);


//S'occupe d'effectuer le tour d'un joueur
int tourJoueur(T_jeu *jeu, int numJoueur, T_booleen bugToucheEntree);


//Retourne un entier qui determine si la partie est finie ou non
int victoire(T_jeu *jeu, int caseVal, int i);


//Affiche le scrore � la fin de la partie
void afficheScore(T_jeu *jeu);


//Fonction qui joue un niveau selectionne jusqu'� la victoire d'un joueur
void joueNiveau(T_jeu *jeu);


//Fonction qui renvoie un entier qui permet de rejouer une partie
int rejouer();
