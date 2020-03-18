/***** Structures *****/


//Definition du type glacon
typedef struct
{
    T_point position;        //Position du glacon
    T_vecteur vecteur;       //Vecteur du glacon
    int pourcentage_fondre;  //Entier de probabilite de fonte du glacon
} T_glacon;


/***** Fonctions *****/


//Initialise un glacon
T_glacon *initGlacon(T_point position, int chanceFonte);


//Initialise un tableau de glacons
T_glacon **initTabGlacons(T_banquise *banquise, int nombreGlacons, int rechauffement);


//Fonction qui verifie que le vecteur du glacon est valide : HAUT BAS GAUCHE DROITE
int verifieVecteurGlacon(T_glacon *glacon);


//Fonction qui retourne le glacon a la position donnee
T_glacon *glaconSelonPosition(T_glacon **glacons, int posX, int posY, int nbGlacons);


//Fonction qui se charge de deplacer le glacon en paramettre
int verifieDeplacementGlacon(T_glacon *glacon, T_banquise *banquise, T_joueur **joueurs, int nbJoueurs);


//
int verifFonteGlacon(T_glacon *glacon);
