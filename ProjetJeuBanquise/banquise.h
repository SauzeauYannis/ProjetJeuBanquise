/***** Structures *****/

//Definition du type banquise
typedef struct
{
    int **tab;      //Matrice represantant la banquise
    int tailleN;    //Taille de la matrice (carree)
    T_point depart;  //Case depart
    T_point arrive;  //Case arrive
} T_banquise;




/***** Fonctions *****/

//Definition de la fonction qui initialise le pointeur de type banquise
T_banquise *initBanquise(int taille);


//Remplit la banquise avec une valeur donnee
void remplitBanquise(T_banquise *banquise, int valeur);


//Modifie une case de la banquise
void modifieCaseBanquise(T_banquise *banquise, int caseX, int caseY, int valeur);


//Ajoute la case de depart et arrive
void ajouteDepartArrive(T_banquise *banquise);
