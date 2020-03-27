/***** Structures *****/


//Enum�ration des �tats d'un joueur
typedef enum
{
    ENCOURS,
    PIEGE,
    GAGNANT,
    PERDANT
} T_etat;


//D�finition du type joueur
typedef struct
{
    char nom[20];       //Nom du joueur limit� � 20 caract�res
    T_couleur couleur;  //Couleur du joueur
    int identifiant;    //Entier qui identifie le joueur
    T_point position;   //Position du joueur dans la banquise
    T_vecteur vecteur;  //D�placement du joueur sur la banquise
    int score;          //Score du joueur
    T_etat etat;        //Etat du joueur : Gagnant - Perdant
    int nbMort;         //Nombre de mort du joueur
} T_joueur;


/***** Fonctions *****/


//Fait choisir une couleur a l'utilisateur
//Compl�xit� lin�aire
//Yannis
T_couleur choixCouleur();


//Initialise un joueur
//Compl�xit� constante
//Yannis
T_joueur *initJoueur(int numeroJoueur);


//Demande a l'utilisateur le nombre de joueurs
//Compl�xit� constante
//Yannis
int demandeNombreJoueurs();


//Initialise un tableau de joueurs
//Compl�xit� constante
//Yannis
T_joueur **initTabJoueurs(T_banquise *banquise, int nombreJoueurs);


//Fait apparaitre le joueur a sa case de depart
//Compl�xit� constante
//Yannis
void departJoueur(T_banquise *banquise, T_joueur *joueur);


//Retourne un entier en fonction du deplacement du joueur, et modifie la position de celui-ci
int verifieDeplacement(T_banquise *banquise, T_joueur *joueur, int caseX, int caseY, int caseValeur);


//Applique le deplacement si possible ou retourne une erreur
int deplacementJoueur_bis(T_banquise *banquise, T_joueur *joueur, char deplacement);


//Applique le deplacement du joueur
int deplacementJoueur(T_banquise *banquise, T_joueur *joueur, char clavier);


//Recupere le joueur selon une position
T_joueur *joueurSelonPosition(T_joueur **joueurs, int posX, int posY, int nbJoueurs);


//Fonction qui s'occupe de tuer le joueur et de le ramener au point de depart
void tuerJoueur(T_joueur *joueur, T_banquise *banquise);
