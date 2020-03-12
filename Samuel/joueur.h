/***** Structures *****/

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

//Fait spawner le joueur a son emplacement
void spawnJoueur(T_banquise *banquise, T_joueur *joueur);

//Demande au joueur un deplacement
char saisieDeplacement();


//Retourne un entier en fonction du deplacement du joueur, et modifie la position de celui-ci
int verifieDeplacement(T_banquise *banquise, T_joueur *joueur, int caseX, int caseY, int caseValeur, int taille);


//Applique le deplacement si possible ou retourne une erreur
int deplacementJoueur_bis(T_banquise *banquise, T_joueur *joueur, int taille, char deplacement, int **tab);


//Applique le deplacement du joueur
int deplacementJoueur(T_banquise *banquise, T_joueur *joueur, int taille, int **tab);


//Fonction test
void affichePositionJoueur(T_joueur *joueur);
