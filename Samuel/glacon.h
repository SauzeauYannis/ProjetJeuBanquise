
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
