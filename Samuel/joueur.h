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

//Fonction qui permet le déplacement du personnage
void deplacementJoeur(T_joueur *joueur, int taille);

//Fonction qui s'occupe du déplacement du personnage en fonction de ses paramettres, et renvoie un entier en fonction du déplacement
int deplacementJoeur_bis(T_joueur *j, int dx, int dy, int taille);

void affichePositionJoueur(T_joueur *joueur);
