/***** Structures *****/

//Enumeration de differentes couleur
typedef enum
{
    ROUGE,
    VERT,
    BLEU,
    JAUNE,
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
} T_joueur;


/***** Fonctions *****/

//Fait choisir une couleur a l'utilisateur
T_couleur choixCouleur();

//Initialise un joueur
T_joueur *initJoueur(int numeroJoueur);

//Demande au joueur un deplacement
char saisieDeplacement();

//Verifie si le joueur est sorti du jeu
int deplacementJoeur_bis(T_joueur *joueur, int taille, char deplacement);

//Applique le deplacement du joueur
void deplacementJoeur(T_joueur *joueur, int taille);

//Fonction test
void affichePositionJoueur(T_joueur *joueur);
