/***** Structures *****/


//Definition du type glace
typedef struct
{
    T_booleen estPresent;  //Verifie si la glace est sur la banquise
    T_point position;      //Donne la position de la glace
} T_glace;


//Definition du type banquise
typedef struct
{
    T_case **matrice;    //Matrice represantant la banquise
    int tailleN;         //Taille de la matrice (carree)
    int tailleEau;       //Taille de l'eau
    T_point depart;      //Case depart
    T_point arrive;      //Case arrive
    T_glace *tabGlaces;  //Tableau de glaces
    int nombreGlaces;    //Nombres de glaces dans la banquise
} T_banquise;


/***** Fonctions *****/


//Créér une matrice carrée
//Compléxité n*n avec n le paramètre
///Auteur : Yannis SAUZEAU
int **initMatrice(int tailleMatrice);


//Initialise un tableau de glaces
//Compléxité n avec n le paramètre
///Auteur : Yannis SAUZEAU
T_glace *initTabGlaces(int taille);


//Modifie une case de la banquise
//Compléxité constante
///Auteur : Yannis SAUZEAU
void modifieCaseBanquise(T_banquise *banquise, int caseX, int caseY, T_case valeur);


//Ajoute une position de glace dans le tableau de glaces de la banquise
//Compléxité au pire n*n avec n la taille de la matrice qui représente la banquise
///Auteur : Yannis SAUZEAU
void ajouteCaseGlace(T_banquise *banquise, int caseX, int caseY);


//Enlève une position de glace dans le tableau de glaces de la banquise
//Compléxité au pire n*n avec n la taille de la matrice qui représente la banquise
///Auteur : Yannis SAUZEAU
void enleveCaseGlace(T_banquise *banquise, int caseX, int caseY, T_case valeur);


//Ajoute la case de départ et d'arrivée
//Compléxité constante
///Auteur : Yannis SAUZEAU
void ajouteDepartArrive(T_banquise *banquise);


//Remplit la banquise d'eau, de glaces et de la case d'arrivée et de départ
//Compléxité n*n + m*m avec n la taille de la matrice et m le nombre de glace par ligne/colonnes
///Auteur : Yannis SAUZEAU
void remplitBanquise(T_banquise *banquise);


//Initialise le pointeur de type banquise
//Compléxité constante
///Auteur : Yannis SAUZEAU
T_banquise *initBanquise(int tailleMatrice, int tailleEau);


//Retourne une case de glace aleatoire
//Compléxité au pire n*n avec n la taille de la matrice qui représente la banquise
///Auteur : Yannis SAUZEAU
T_point caseGlaceAleatoire(T_banquise *banquise, T_booleen partout);


//Applique la fonte de la banquise
//Compléxité linéaire
///Auteur : Yannis SAUZEAU
void fonteBanquise(T_banquise *banquise, int chanceFonte);
