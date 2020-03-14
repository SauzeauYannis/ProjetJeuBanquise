/***** Structures *****/

//D�finition du type gla�on
typedef struct
{
    T_point position;
    T_vecteur vecteur;
    int pourcentage_fondre;
} T_glacon;




/***** Fonctions *****/


//Fonction qui initialise un gla�on
T_glacon *initGlacon(int caseX, int caseY);


//Initialise un tableau remplit de n gla�ons (n est un paramettre de l fonction)
/*T_glacon **initTabGlacon(int nbGlacons);*/


//Fonction qui v�rifie que le vecteur du gla�on est valide : HAUT BAS GAUCHE DROITE
int verifieVecteurGlacon(T_glacon *glacon);


//Fonction qui v�rifie si le gla�on touche  un rebord ou non
int verifieDeplacementGlacon(int caseX, int caseY, int caseValeur, int taille);


//Cherche un joueur en fonction d'une position en paramettre
T_joueur *retourneJoueurGlacon(T_joueur **joueurs, int posX, int posY, int nbJoueurs);


//Fonction qui se charge de d�placer le gla�on en paramettre
int deplacementGlacon(T_glacon *glacon, T_banquise *banquise, T_joueur **joueurs, int nbJoueurs);
