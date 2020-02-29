
/***** Structures *****/

//Définition du type glaçon
typedef struct
{
    T_point position;
    T_vecteur vecteur;
    int pourcentage_fondre;
}T_glacon;




/***** Fonctions *****/


//Fonction qui initialise un glaçon
T_glacon *initGlacon(int caseX, int caseY);


//Fonction qui vérifie que le vecteur du glaçon est valide : HAUT BAS GAUCHE DROITE
int verifieVecteurGlacon(T_glacon *glacon);
