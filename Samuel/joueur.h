/***** Structures *****/


//Enumeration des etat d'un joueur
typedef enum
{
    ENCOURS,
    PIEGE,
    GAGNANT,
    PERDANT
} T_etat;


//Definition du type joueur
typedef struct
{
    char nom[20];       //Nom du joueur limite a 20 caractere
    T_couleur couleur;  //Couleur du joueur
    int identifiant;    //Entier qui identifie le joueur
    T_point position;   //Position du joueur dans la banquise
    T_vecteur vecteur;  //Deplacement du joueur sur la banquise
    int score;          //Score du joueur
    T_etat etat;        //Etat du joueur : Gagnant - Perdant
    int nbMort;         //Nombre de mort du joueur
} T_joueur;


/***** Fonctions *****/


//Fait choisir une couleur a l'utilisateur
T_couleur choixCouleur();


//Initialise un joueur
T_joueur *initJoueur(int numeroJoueur);


//Demande a l'utilisateur le nombre de joueurs
int demandeNombreJoueurs();


//Initialise un tableau de joueurs
T_joueur **initTabJoueurs(T_banquise *banquise, int nombreJoueurs);


//Fait apparaitre le joueur a sa case de depart
void departJoueur(T_banquise *banquise, T_joueur *joueur);


//Retourne un entier en fonction du d�placement du joueur, et modifie la position de celui-ci
//Complexit� : O(n)
///Auteur : Samuel GOUBEAU
int verifieDeplacement(T_banquise *banquise, T_joueur *joueur, int caseX, int caseY, int caseValeur);


//Applique le d�placement si possible ou retourne une erreur
//Complexit� : O(n)
///Auteur : Samuel GOUBEAU
int deplacementJoueur_bis(T_banquise *banquise, T_joueur *joueur, char deplacement);


//Applique le d�placement du joueur
//Complexit� : O(n*n)
///Auteur : Samuel GOUBEAU
int deplacementJoueur(T_banquise *banquise, T_joueur *joueur, char clavier);


//R�cup�re le joueur selon une position
//Complexit� : O(n)
///Auteur : Samuel GOUBEAU
T_joueur *joueurSelonPosition(T_joueur **joueurs, int posX, int posY, int nbJoueurs);


//Fonction qui s'occupe de tuer le joueur et de le ramener au point de d�part
//Complexit� : O(n)
///Auteur : Samuel GOUBEAU
void tuerJoueur(T_joueur *joueur, T_banquise *banquise);
