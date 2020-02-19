/***** Structures *****/

//Definition du type banquise
typedef struct
{
    int **tab;   //Matrice represantant la banquise
    int tailleN; //Taille de la matrice (carree)
    int nombreJ; //Nombre de joueurs sur la banquise
} T_banquise;


/***** Fonctions *****/

//Definition de la fonction qui initialise le pointeur de type banquise
T_banquise *initBanquise(int taille);

//Remplit la banquise avec une valeur donnee
void remplitBanquise(T_banquise *banquise, int valeur);

//Affiche la banquise
void afficheBanquise(T_banquise *banquise);
