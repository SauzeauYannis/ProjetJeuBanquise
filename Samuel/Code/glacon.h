/***** Structures *****/


//D�finition du type glacon
typedef struct
{
    T_point position;        //Position du gla�on
    T_vecteur vecteur;       //Vecteur du gla�on
    int pourcentage_fondre;  //Entier de probabilit� de fonte du gla�on
} T_glacon;


/***** Fonctions *****/


//Initialise un gla�on
//Complexit� : O(1)
///Auteur : Samuel GOUBEAU
T_glacon *initGlacon(T_point position, int chanceFonte);


//Initialise un tableau de glacons
//Complexit� : O(n)
///Auteur : Samuel GOUBEAU
T_glacon **initTabGlacons(T_banquise *banquise, int nombreGlacons, int rechauffement);


//Fonction qui v�rifie que le vecteur du glacon est valide : HAUT BAS GAUCHE DROITE
//Complexit� : O(1)
///Auteur : Samuel GOUBEAU
T_booleen verifieVecteurGlacon(T_glacon *glacon);


//Fonction qui retourne le glacon a la position donn�e
//Complexit� : O(n)
///Auteur : Samuel GOUBEAU
T_glacon *glaconSelonPosition(T_glacon **glacons, int posX, int posY, int nbGlacons);


//Fonction qui se charge de deplacer le glacon en param�tre
//Complexit� : O(n)
///Auteur : Samuel GOUBEAU
int verifieDeplacementGlacon(T_glacon *glacon, T_banquise *banquise, T_joueur **joueurs, int nbJoueurs);


//Fonction qui regarde si le gla�on va fondre
//Complexit� : O(1)
///Auteur : Samuel GOUBEAU
T_booleen verifFonteGlacon(T_glacon *glacon);
