
/***** Structures *****/

//D�finition du type gla�on
typedef struct
{
    T_point position;
    T_vecteur vecteur;
    int pourcentage_fondre;
}T_glacon;




/***** Fonctions *****/

//Fonction qui initialise un gla�on
T_glacon *initGlacon(int caseX, int caseY);
