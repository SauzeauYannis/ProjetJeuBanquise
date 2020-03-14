/***** Structures *****/

//Définition du type glaçon
typedef struct
{
    T_point position;
    T_vecteur vecteur;
    int pourcentage_fondre;
} T_glacon;




/***** Fonctions *****/


//Fonction qui initialise un glaçon
T_glacon *initGlacon(int caseX, int caseY);


//Initialise un tableau remplit de n glaçons (n est un paramettre de l fonction)
/*T_glacon **initTabGlacon(int nbGlacons);*/


//Fonction qui vérifie que le vecteur du glaçon est valide : HAUT BAS GAUCHE DROITE
int verifieVecteurGlacon(T_glacon *glacon);


//Fonction qui vérifie si le glaçon touche  un rebord ou non
int verifieDeplacementGlacon(int caseX, int caseY, int caseValeur, int taille);


//Cherche un joueur en fonction d'une position en paramettre
T_joueur *retourneJoueurGlacon(T_joueur **joueurs, int posX, int posY, int nbJoueurs);


//Fonction qui se charge de déplacer le glaçon en paramettre
int deplacementGlacon(T_glacon *glacon, T_banquise *banquise, T_joueur **joueurs, int nbJoueurs);
