/***** Structures *****/

//Definition du type joueur
typedef struct
{
    char nom[20];       //Nom du joueur limite a 20 caractere
    T_couleur couleur;  //Couleur du joueur
    int identifiant;    //Entier qui identifie le joueur
    T_point position;   //Position du joueur dans la banquise
    T_vecteur vecteur;  //Deplacement du joueur sur la banquise (Ne sert � rien �  rien pour le moment)
    int score;          //Score du joueur
    int etat;           //Etat du joueur : Gagnant - Perdant
    int nbMort;
} T_joueur;


/***** Fonctions *****/


//Fait choisir une couleur a l'utilisateur
T_couleur choixCouleur();


//Initialise un joueur
T_joueur *initJoueur(int numeroJoueur);


//Fait apparaitre le joueur a sa case de depart
void departJoueur(T_banquise *banquise, T_joueur *joueur);


//Demande au joueur un deplacement
char saisieDeplacement();


//Retourne un entier en fonction du deplacement du joueur, et modifie la position de celui-ci
int verifieDeplacement(T_banquise *banquise, T_joueur *joueur, int caseX, int caseY, int caseValeur);


//Applique le deplacement si possible ou retourne une erreur
int deplacementJoueur_bis(T_banquise *banquise, T_joueur *joueur, char deplacement);


//Applique le deplacement du joueur
int deplacementJoueur(T_banquise *banquise, T_joueur *joueur);


//Fonction qui s'occupe de tuer le joueur et de le ramener au point de depart
void tuerJoueur(T_joueur *joueur, T_banquise *banquise);


//
T_joueur *joueurSelonPoisition(T_joueur **joueurs, int posX, int posY, int nbJoueurs);
