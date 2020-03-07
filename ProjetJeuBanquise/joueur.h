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
    ERREUR
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



//Definition du type joueur
typedef struct
{
    char nom[20];       //Nom du joueur limite a 20 caractere
    T_couleur couleur;  //Couleur du joueur
    int identifiant;    //Entier qui identifie le joueur
    T_point position;   //Position du joueur dans la banquise
    T_vecteur vecteur;  //Deplacement du joueur sur la banquise (Ne sert à rien à  rien pour le moment)
    int score;          //Score du joueur
    int etat;           //Etat du joueur : Gagnant - Perdant
} T_joueur;




/***** Fonctions *****/

//Fait choisir une couleur a l'utilisateur
T_couleur choixCouleur();


//Initialise un joueur
T_joueur *initJoueur(int numeroJoueur);


//Demande au joueur un deplacement
char saisieDeplacement();


//Retourne un entier en fonction du deplacement du joueur, et modifie la position de celui-ci
int verifieDeplacement(T_joueur *joueur, int caseX, int caseY, int caseValeur, int taille);


//Applique le deplacement si possible ou retourne une erreur
int deplacementJoueur_bis(T_joueur *joueur, int taille, char deplacement, int **tab);


//Applique le deplacement du joueur
void deplacementJoueur(T_joueur *joueur, int taille, int **tab);


//Fonction test
void affichePositionJoueur(T_joueur *joueur);
