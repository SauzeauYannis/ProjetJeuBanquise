/***** Structures *****/


//Définition du type glacon
typedef struct
{
    T_point position;        //Position du glaçon
    T_vecteur vecteur;       //Vecteur du glaçon
    int pourcentage_fondre;  //Entier de probabilité de fonte du glaçon
} T_glacon;


/***** Fonctions *****/


//Initialise un glaçon
//Complexité : O(1)
///Auteur : Samuel GOUBEAU
T_glacon *initGlacon(T_point position, int chanceFonte);


//Initialise un tableau de glacons
//Complexité : O(n)
///Auteur : Samuel GOUBEAU
T_glacon **initTabGlacons(T_banquise *banquise, int nombreGlacons, int rechauffement);


//Fonction qui vérifie que le vecteur du glacon est valide : HAUT BAS GAUCHE DROITE
//Complexité : O(1)
///Auteur : Samuel GOUBEAU
T_booleen verifieVecteurGlacon(T_glacon *glacon);


//Fonction qui retourne le glacon a la position donnée
//Complexité : O(n)
///Auteur : Samuel GOUBEAU
T_glacon *glaconSelonPosition(T_glacon **glacons, int posX, int posY, int nbGlacons);


//Fonction qui se charge de deplacer le glacon en paramètre
//Complexité : O(n)
///Auteur : Samuel GOUBEAU
int verifieDeplacementGlacon(T_glacon *glacon, T_banquise *banquise, T_joueur **joueurs, int nbJoueurs);


//Fonction qui regarde si le glaçon va fondre
//Complexité : O(1)
///Auteur : Samuel GOUBEAU
T_booleen verifFonteGlacon(T_glacon *glacon);
