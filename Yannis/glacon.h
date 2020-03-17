/***** Structures *****/


//Definition du type glacon
typedef struct
{
    T_point position;        //Position du glacon
    T_vecteur vecteur;       //Vecteur du glacon
    int pourcentage_fondre;  //Entier de probabilite de fonte du glacon
} T_glacon;


/***** Fonctions *****/


//Fonction qui initialise un glacon
T_glacon *initGlacon(int caseX, int caseY, int chanceFonte);


//Fonction qui verifie que le vecteur du glacon est valide : HAUT BAS GAUCHE DROITE
int verifieVecteurGlacon(T_glacon *glacon);


//Fonction qui retourne le glacon a la position donnee
T_glacon *glaconSelonPosition(T_glacon **glacons, int posX, int posY, int nbGlacons);


//Fonction qui se charge de deplacer le glacon en paramettre
int deplacementGlacon(T_glacon *glacon, T_banquise *banquise, T_joueur **joueurs, int nbJoueurs);


//
int verifFonteGlacon(T_glacon *glacon);
