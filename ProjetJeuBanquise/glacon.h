<<<<<<< HEAD

=======
>>>>>>> 1f32d699bab69a0c6b9c0255e17a453032ea1b06
/***** Structures *****/

//Définition du type glaçon
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


//Fonction qui initialise un glaçon
T_glacon *initGlacon(int caseX, int caseY);


//Fonction qui vérifie que le vecteur du glaçon est valide : HAUT BAS GAUCHE DROITE
int verifieVecteurGlacon(T_glacon *glacon);
<<<<<<< HEAD
=======


//Fonction qui vérifie si le glaçon touche  un rebord ou non
int verifieDeplacementGlacon(int caseX, int caseY,int caseValeur, int taille);
>>>>>>> 1f32d699bab69a0c6b9c0255e17a453032ea1b06
