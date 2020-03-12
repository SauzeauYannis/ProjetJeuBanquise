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
    int **tab;           //Matrice represantant la banquise
    int tailleN;         //Taille de la matrice (carree)
    T_point depart;      //Case depart
    T_point arrive;      //Case arrive
    T_glace *tabGlaces;  //Tableau de glaces
} T_banquise;



/***** Fonctions *****/

//Definition de la fonction qui initialise le pointeur de type banquise
T_banquise *initBanquise(int taille);


//Remplit la banquise avec une valeur donnee
void remplitBanquise(T_banquise *banquise, T_case valeur, int tailleEau);


//Modifie une case de la banquise
void modifieCaseBanquise(T_banquise *banquise, int caseX, int caseY, T_case valeur);


//Ajoute la case de depart et arrive
void ajouteDepartArrive(T_banquise *banquise, int tailleEau);


//Ajoute une position de glace dans le tableau de glaces de la banquise
void ajouteCaseGlace(T_banquise *banquise, int caseX, int caseY);


//Enleve une position de glace dans le tableau de glaces de la banquise
void enleveCaseGlace(T_banquise *banquise, int caseX, int caseY, T_case valeur);
