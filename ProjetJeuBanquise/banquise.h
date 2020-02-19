/***** Structures *****/

//Definition du type banquise
typedef struct
{
    int **tab;   //Matrice represantant la banquise
    int tailleN; //Taille de la matrice (carree)
} T_banquise;

//Definition du type point qui represente la case d'une banquise
typedef struct
{
    int x; //Point x = horizontal
    int y; //Point y = vertical
} T_point;


/***** Fonctions *****/

//Definition de la fonction qui initialise le pointeur de type banquise
T_banquise *initBanquise(int taille);

//Remplit la banquise avec une valeur donnee
void remplitBanquise(T_banquise *banquise, int valeur);

//Modifie une case de la banquise
void modifieCaseBanquise(T_banquise *banquise, T_point point, int valeur);

//Affiche la banquise
void afficheBanquise(T_banquise *banquise);
