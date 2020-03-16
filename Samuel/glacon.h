/***** Structures *****/

//Definition du type glacon
typedef struct
{
    T_point position;
    T_vecteur vecteur;
    int pourcentage_fondre;
} T_glacon;




/***** Fonctions *****/


//Fonction qui initialise un glacon
T_glacon *initGlacon(int caseX, int caseY);


//Fonction qui verifie que le vecteur du glacon est valide : HAUT BAS GAUCHE DROITE
int verifieVecteurGlacon(T_glacon *glacon);


//Fonction qui se charge de deplacer le glacon en paramettre
int deplacementGlacon(T_glacon *glacon, T_banquise *banquise, T_joueur **joueurs, int nbJoueurs);


//Fonction qui regarde si le glaçon va fondre
int verifFonteGlacon(T_glacon *glacon);
