<<<<<<< HEAD

=======
>>>>>>> 1f32d699bab69a0c6b9c0255e17a453032ea1b06
/***** Structures *****/

//D�finition du type gla�on
typedef struct
{
    T_point position;
    T_vecteur vecteur;
    int pourcentage_fondre;
<<<<<<< HEAD
}T_glacon;
=======
} T_glacon;
>>>>>>> 1f32d699bab69a0c6b9c0255e17a453032ea1b06




/***** Fonctions *****/


//Fonction qui initialise un gla�on
T_glacon *initGlacon(int caseX, int caseY);


//Fonction qui v�rifie que le vecteur du gla�on est valide : HAUT BAS GAUCHE DROITE
int verifieVecteurGlacon(T_glacon *glacon);
<<<<<<< HEAD
=======


//Fonction qui v�rifie si le gla�on touche  un rebord ou non
int verifieDeplacementGlacon(int caseX, int caseY,int caseValeur, int taille);
>>>>>>> 1f32d699bab69a0c6b9c0255e17a453032ea1b06
