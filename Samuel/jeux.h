#include <stdio.h>    //Pour les entr�s-sorties
#include <stdlib.h>   //Pour la gestion de la m�moire
#include <windows.h>  //Pour afficher les couleurs
#include <time.h>     //Pour l'al�atoire


/***** Structures *****/


//Enum�ration de differentes couleurs
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


//Enum�ration d'un booleen avec une valeur d'�chec en plus
typedef enum
{
    FAUX,
    VRAI,
    ECHEC
} T_booleen;


//Enum�ration des cases de la banquise
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


//D�finition du type point qui represente la position d'une case d'une banquise
typedef struct
{
    int x; //Point x = horizontal
    int y; //Point y = vertical
} T_point;


//D�finition du type vecteur
typedef struct
{
    int dx; //Vecteur x = deplacement horizontal
    int dy; //Vecteur y = deplacement vertical
} T_vecteur;


//Importe tous les headers des diff�rents fichiers C du projet
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
    int nombreJoueurs;    //Nombre de joueurs pr�sent sur le jeu
    int nombreGlacons;    //Nombre de glacons pr�sent sur le jeu
    int nombreMarteaux;   //Nombre de marteaux pr�sent sur le jeu
    int nombreRessorts;   //Nombre de ressorts pr�sent sur le jeu
    int nombreRochers;    //Nombre de rochers pr�sent sur le jeu
    int nombreTour;       //Nombre de tour actuel du jeu
    int rechauffement;    //Probabilit� de fonte de la banquise comme du glacon
    int probPiege;        //Probabilit� de tomber dans un piege
    int IdJeu;            //Identifiant de la partie en cours
} T_jeu;


/***** Fonctions *****/

//Affiche le menu du jeu
//Compl�xit� lin�aire
///Auteur : Yannis SAUZEAU
void afficheMenu(T_booleen debut);


//Change la couleur de la console selon le type couleur mis en param�tre
//Complexit� : O(1)
///Auteur : Samuel GOUBEAU
void changeCouleurConsole(T_couleur couleur);


//Fonction qui change la couleur du texte affich� sur le terminal
//Complexit� : O(1)
///Auteur : Samuel GOUBEAU
void changeCouleurTexte(T_couleur couleur);


//Cr�e une matrice booll�enne
//Compl�xit� n*n avec n le param�tre
///Auteur : Yannis SAUZEAU
T_booleen **tabChemin(int taille);


//V�rifie s'il y a un chemin menant � l'arriv�
//Compl�xit� au pire n*n*n avec n la taille de la matrice repr�sentant la banquise
///Auteur : Yannis SAUZEAU
T_booleen verifieChemin(T_jeu *jeu, T_booleen **tab, int caseX, int caseY, T_booleen affichage);


//V�rifie si chaque joueurs peut atteindre l'arriv�
//Compl�xit� au pire 4*n*n*n avec n la taille de la matric repr�sentant la banquise
///Auteur : Yannis SAUZEAU
T_booleen verifieCheminJoueurs(T_jeu *jeu, T_booleen affichage);


//Initialise le jeu
//Compl�xit� au pire n*n*n avec n la taille de la matrice repr�sentant la banquise
///Auteur : Yannis SAUZEAU
T_jeu *initJeux(int niveau, int tailleN, int tailleEau, int nombreGlacons, int nombreMarteaux, int nombreRessorts, int nombreRochers, int chanceFonte, int chancePiege);


//Re-initialise le jeu
//Compl�xit� au pire n*n*n-1 avec n la taille de la matrice repr�sentant la banquise
///Auteur : Yannis SAUZEAU
void reInitJeux(T_jeu *jeu);


//Initialise le jeu selon les d�sirs de l'utilisateur
//Compl�xit� lin�aire
///Auteur : Yannis SAUZEAU
T_jeu *initJeuxPersonalise();


//Initialise le niveau choisi par le joueur
//Compl�xit� �gal � initJeux()
///Auteur : Yannis SAUZEAU
T_jeu *initNiveau();


//Affiche le jeu
//Compl�xit� constante
///Auteur : Yannis SAUZEAU
void afficheJeu(T_jeu *jeu);


//Demande au joueur de saisir une touche
//Compl�xit� constante
///Auteur : Yannis SAUZEAU
char saisieTouche(T_joueur *joueur);


//S'occupe du deplacement du glacon apres que celui-ci se soit fait pousser par un joueur
//Complexit� : O(infini)
///Auteur : Samuel GOUBEAU
void joueurPousseGlacon(T_joueur *joueur, T_glacon *glacon, T_jeu *jeu);


//S'occupe de la fonte d'un glacon
//Compl�xit� lin�aire
///Auteur : Yannis SAUZEAU
void fonteGlacon(T_jeu *jeu);


//Fait bouger la t�te du marteau
//Compl�xit� au pire infinie
///Auteur : Yannis SAUZEAU
void bougeTeteMarteau(T_jeu *jeu, T_marteau *marteau, T_booleen sensHorraire);


//S'occupe d'effectuer le tour d'un joueur
//Complexit� : O(infini)
///Auteur : Samuel GOUBEAU
int tourJoueur(T_jeu *jeu, int numJoueur);


//Retourne un entier qui determine si la partie est finie ou non
//Complexit� : O(1)
///Auteur : Samuel GOUBEAU
int victoire(T_jeu *jeu, int caseVal, int i);


//Affiche le scrore � la fin de la partie
//Complexit� : O(n)
///Auteur : Samuel GOUBEAU
void afficheScore(T_jeu *jeu);


//Fonction qui joue un niveau selectionne jusqu'� la victoire d'un joueur
//Complexit� : O(infini)
///Auteur : Samuel GOUBEAU
void joueNiveau(T_jeu *jeu);


//Fonction qui renvoie un entier qui permet de rejouer une partie
//Complexit� : O(n)
///Auteur : Samuel GOUBEAU
int rejouer();


//Fonction qui est le corps du jeu, car elle lance le jeu
//Complexit� : O(infini)
///Auteur : Samuel GOUBEAU
void joue();
