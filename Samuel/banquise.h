/***** Structures *****/


//Definition du type glace
typedef struct
{
    int estPresent;    //Valeur booleenne qui verifie si la glace est sur la banquise
    T_point position;  //Donne la position de la glace
} T_glace;


//Definition du type banquise
typedef struct
{
    int **matrice;       //Matrice represantant la banquise
    int tailleN;         //Taille de la matrice (carree)
    int tailleEau;       //Taille de l'eau
    T_point depart;      //Case depart
    T_point arrive;      //Case arrive
    T_glace *tabGlaces;  //Tableau de glaces
    int nombreGlaces;    //Nombres de glaces dans la banquise
} T_banquise;


/***** Fonctions *****/


//Initialise la matrice qui represente la banquise
int **initMatrice(int tailleMatrice);


//Initialise le tableau de glaces
T_glace *initTabGlaces(int taille);


//Modifie une case de la banquise
void modifieCaseBanquise(T_banquise *banquise, int caseX, int caseY, T_case valeur);


//Ajoute une position de glace dans le tableau de glaces de la banquise
void ajouteCaseGlace(T_banquise *banquise, int caseX, int caseY);


//Enleve une position de glace dans le tableau de glaces de la banquise
void enleveCaseGlace(T_banquise *banquise, int caseX, int caseY, T_case valeur);


//Ajoute la case de depart et arrive
void ajouteDepartArrive(T_banquise *banquise);


//Remplit la banquise avec une valeur donnee
void remplitBanquise(T_banquise *banquise);


//Initialise le pointeur de type banquise
T_banquise *initBanquise(int tailleMatrice, int tailleEau);


//Retourne une case de glace aleatoire
T_point caseGlaceAleatoire(T_banquise *banquise, int choix);


//Applique la fonte de la banquise
void fonteBanquise(T_banquise *banquise, int chanceFonte);
