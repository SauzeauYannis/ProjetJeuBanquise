#include <stdio.h>    //Pour les entrés-sorties
#include <stdlib.h>   //Pour la gestion de la mémoire
#include <windows.h>  //Pour afficher les couleurs
#include <time.h>     //Pour l'aléatoire


/***** Structures *****/


//Enumération de differentes couleurs
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


//Enumération d'un booleen avec une valeur d'échec en plus
typedef enum
{
    FAUX,
    VRAI,
    ECHEC
} T_booleen;


//Enumération des cases de la banquise
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
    ABANDON
} T_case;


//Définition du type point qui represente la position d'une case d'une banquise
typedef struct
{
    int x; //Point x = horizontal
    int y; //Point y = vertical
} T_point;


//Définition du type vecteur
typedef struct
{
    int dx; //Vecteur x = deplacement horizontal
    int dy; //Vecteur y = deplacement vertical
} T_vecteur;


//Importe tous les headers des différents fichiers C du projet
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
    T_marteau **marteaux; //Tableau de marteaux
    T_ressort *ressorts;  //Tableau de ressort
    T_rocher *rochers;    //Tableau de rochers
    int nombreJoueurs;    //Nombre de joueurs présent sur le jeu
    int nombreGlacons;    //Nombre de glacons présent sur le jeu
    int nombreMarteaux;   //Nombre de marteaux présent sur le jeu
    int nombreRessorts;   //Nombre de ressorts présent sur le jeu
    int nombreRochers;    //Nombre de rochers présent sur le jeu
    int nombreTour;       //Nombre de tour actuel du jeu
    int rechauffement;    //Probabilité de fonte de la banquise comme du glacon
    int probPiege;        //Probabilité de tomber dans un piege
    int IdJeu;            //Identifiant de la partie en cours
} T_jeu;


/***** Fonctions *****/

//Affiche le menu du jeu
//Compléxité linéaire
///Auteur : Yannis SAUZEAU
void afficheMenu(T_booleen debut);


//Change la couleur de la console selon le type couleur mis en paramètre
//Complexité : O(1)
///Auteur : Samuel GOUBEAU
void changeCouleurConsole(T_couleur couleur);


//Fonction qui change la couleur du texte affiché sur le terminal
//Complexité : O(1)
///Auteur : Samuel GOUBEAU
void changeCouleurTexte(T_couleur couleur);


//Crée une matrice boolléenne
//Compléxité n*n avec n le paramètre
///Auteur : Yannis SAUZEAU
T_booleen **tabChemin(int taille);


//Vérifie s'il y a un chemin menant à l'arrivé
//Compléxité au pire n*n*n avec n la taille de la matrice représentant la banquise
///Auteur : Yannis SAUZEAU
T_booleen verifieChemin(T_jeu *jeu, T_booleen **tab, int caseX, int caseY, T_booleen affichage);


//Vérifie si chaque joueurs peut atteindre l'arrivé
//Compléxité au pire 4*n*n*n avec n la taille de la matric représentant la banquise
///Auteur : Yannis SAUZEAU
T_booleen verifieCheminJoueurs(T_jeu *jeu, T_booleen affichage);


//Initialise le jeu
//Compléxité au pire n*n*n avec n la taille de la matrice représentant la banquise
///Auteur : Yannis SAUZEAU
T_jeu *initJeux(int niveau, int tailleN, int tailleEau, int nombreGlacons, int nombreMarteaux, int nombreRessorts, int nombreRochers, int chanceFonte, int chancePiege);


//Re-initialise le jeu
//Compléxité au pire n*n*n-1 avec n la taille de la matrice représentant la banquise
///Auteur : Yannis SAUZEAU
void reInitJeux(T_jeu *jeu);


//Initialise le jeu selon les désirs de l'utilisateur
//Compléxité linéaire
///Auteur : Yannis SAUZEAU
T_jeu *initJeuxPersonalise();


//Initialise le niveau choisi par le joueur
//Compléxité égal à initJeux()
///Auteur : Yannis SAUZEAU
T_jeu *initNiveau();


//Affiche le jeu
//Compléxité constante
///Auteur : Yannis SAUZEAU
void afficheJeu(T_jeu *jeu);


//Demande au joueur de saisir une touche
//Compléxité constante
///Auteur : Yannis SAUZEAU
char saisieTouche(T_joueur *joueur);


//S'occupe du deplacement du glacon apres que celui-ci se soit fait pousser par un joueur
//Complexité : O(infini)
///Auteur : Samuel GOUBEAU
void joueurPousseGlacon(T_joueur *joueur, T_glacon *glacon, T_jeu *jeu);


//S'occupe de la fonte d'un glacon
//Compléxité linéaire
///Auteur : Yannis SAUZEAU
void fonteGlacon(T_jeu *jeu);


//Fait bouger la tête du marteau
//Compléxité au pire infinie
///Auteur : Yannis SAUZEAU
void bougeTeteMarteau(T_jeu *jeu, T_marteau *marteau, T_booleen sensHorraire);


//S'occupe d'effectuer le tour d'un joueur
//Complexité : O(infini)
///Auteur : Samuel GOUBEAU
int tourJoueur(T_jeu *jeu, int numJoueur);


//Retourne un entier qui determine si la partie est finie ou non
//Complexité : O(1)
///Auteur : Samuel GOUBEAU
int victoire(T_jeu *jeu, int caseVal, int i);


//Affiche le scrore à la fin de la partie
//Complexité : O(n)
///Auteur : Samuel GOUBEAU
void afficheScore(T_jeu *jeu);


//Fonction qui joue un niveau selectionne jusqu'à la victoire d'un joueur
//Complexité : O(infini)
///Auteur : Samuel GOUBEAU
void joueNiveau(T_jeu *jeu);


//Fonction qui renvoie un entier qui permet de rejouer une partie
//Complexité : O(n)
///Auteur : Samuel GOUBEAU
int rejouer();


//Fonction qui est le corps du jeu, car elle lance le jeu
//Complexité : O(infini)
///Auteur : Samuel GOUBEAU
void joue();
