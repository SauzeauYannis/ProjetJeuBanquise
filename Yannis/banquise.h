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


//Cr��r une matrice carr�e
//Compl�xit� n*n avec n le param�tre
//Yannis
int **initMatrice(int tailleMatrice);


//Initialise un tableau de glaces
//Compl�xit� n avec n le param�tre
//Yannis
T_glace *initTabGlaces(int taille);


//Modifie une case de la banquise
//Compl�xit� constante
//Yannis
void modifieCaseBanquise(T_banquise *banquise, int caseX, int caseY, T_case valeur);


//Ajoute une position de glace dans le tableau de glaces de la banquise
//Compl�xit� au pire n*n avec n la taille de la matrice qui repr�sente la banquise
//Yannis
void ajouteCaseGlace(T_banquise *banquise, int caseX, int caseY);


//Enl�ve une position de glace dans le tableau de glaces de la banquise
//Compl�xit� au pire n*n avec n la taille de la matrice qui repr�sente la banquise
//Yannis
void enleveCaseGlace(T_banquise *banquise, int caseX, int caseY, T_case valeur);


//Ajoute la case de d�part et d'arriv�e
//Compl�xit� constante
//Yannis
void ajouteDepartArrive(T_banquise *banquise);


//Remplit la banquise d'eau, de glaces et de la case d'arriv�e et de d�part
//Compl�xit� n*n + m*m avec n la taille de la matrice et m le nombre de glace par ligne/colonnes
//Yannis
void remplitBanquise(T_banquise *banquise);


//Initialise le pointeur de type banquise
//Compl�xit� constante
//Yannis
T_banquise *initBanquise(int tailleMatrice, int tailleEau);


//Retourne une case de glace aleatoire
//Compl�xit� au pire n*n avec n la taille de la matrice qui repr�sente la banquise
//Yannis
T_point caseGlaceAleatoire(T_banquise *banquise, T_booleen partout);


//Applique la fonte de la banquise
//Compl�xit� lin�aire
//Yannis
void fonteBanquise(T_banquise *banquise, int chanceFonte);
