#include "jeux.h"

//Fonction qui initialise un glaçon
T_glacon *initGlacon(int caseX, int caseY)
{
    T_glacon *glacon = (T_glacon *)malloc(sizeof(T_glacon));  //Alloue de la mémoire pour le glaçon
    T_point pos;            //Créer un point qui sera la position du glaçon
    pos.x = caseX;          //Initialise la postion du glaçon via les paramètres
    pos.y = caseY;
    T_vecteur vect;         //Créer le vecteur du glacon
    vect.dx = 0;
    vect.dy = 0;            //Initialise le vecteur à 0

    glacon->position = pos;
    glacon->vecteur = vect;
    glacon->pourcentage_fondre = 0;

    return glacon;         //Retourne le glaçon
}


//Initialise un tableau remplit de n glaçons (n est un paramettre de l fonction)
/*T_glacon **initTabGlacon(int nbGlacons)
{
    T_glacon **glaconTab;                                        //Créé un tableau de pointeurs de glaçons
    glaconTab = (T_glacon **)malloc(nbGlacons * sizeof(int *));  //Alloue de la mémoire pour le tableau

    for(int i = 0; i<nbGlacons; i++)                             //Ajoute n glaçons initialisés à des positions alléatoires sur la banquise
    {
        glaconTab[i] = initGlacon(i, 3);
    }
    return glaconTab;
}*/



//Fonction qui vérifie que le vecteur du glaçon est valide : HAUT BAS GAUCHE DROITE
int verifieVecteurGlacon(T_glacon *glacon)
{
    int dx = glacon->vecteur.dx, dy = glacon->vecteur.dy;

    if(dx != 0 && dy != 0)
    {
        printf("Le vecteur du glacon à la position x = %d y = %d est incorrecte !", glacon->position.x, glacon->position.y);
        return -1;
    }
    else
    {
        return 0;
    }
}



//Fonction qui vérifie si le glaçon touche  un rebord ou non
int verifieDeplacementGlacon(int caseX, int caseY, int caseValeur, int taille)
{
    switch (caseValeur)
    {
    case -1:                                                                        //Retourne une valeur d'echec pour prevenir la fonction suivante
    case DEPART:
    case ARRIVE:
        return -1;
        break;
    case JOUEUR:
        return 1;                                                                   //Retourne une valeur pour dire que le glaçon touche un joueur
        break;
    case EAU:
        return 2;                                                                   //Retourne une valeur pour indiquer que la glaçon touche de l'eau
        break;
    default :
        return 0;                                                                   //Entier de validation
    }
}


//Cherche un joueur en fonction d'une position en paramettre
T_joueur *retourneJoueurGlacon(T_joueur **joueurs, int posX, int posY, int nbJoueurs)
{
    int i;
    T_joueur *joueur;

    for(i = 0; i < nbJoueurs; i++)                                            //Regarde chaque joueur du tableau
    {
        if (posX == joueurs[i]->position.x && posY == joueurs[i]->position.y) //Condition qui regarde si le position en paramettre correspond à celle du joueur
        {
            joueur = joueurs[i];                                              //Si la condition est vrai, retourne le joueur
            break;
        }
    }

    return joueur;
}

//Fonction qui se charge de déplacer le glaçon en paramettre
int deplacementGlacon(T_glacon *glacon, T_banquise *banquise, T_joueur **joueurs, int nbJoueurs)
{
    ajouteCaseGlace(banquise, glacon->position.x, glacon->position.y);

    int posx = glacon->position.x, posy = glacon->position.y;          //Position du glaçon avant son déplacement
    int x = posx + glacon->vecteur.dx, y = posy + glacon->vecteur.dy;  //Position vers laquelle le glaçon se déplace
    int taille = banquise->tailleN;
    int caseValeur, verif;
    T_joueur *joueur;

    if(x < 0 || x >= taille || y < 0 || y >= taille)                   //Vérifie si le glaçon se déplace en dehors du cadre
    {
        caseValeur = -1;
    }
    else
    {
        caseValeur = banquise->tab[x][y];
    }

    verif = verifieDeplacementGlacon(x, y, caseValeur, taille);

    switch(verif)
    {
        case -1 :
            glacon->vecteur.dx = glacon->vecteur.dy = 0;
            return 0;
            break;
        case 1 :
            glacon->position.x = x, glacon->position.y = y;
            joueur = retourneJoueurGlacon(joueurs, x, y, nbJoueurs);
            tuerJoueur(joueur, banquise);
            return 0;
            break;
        case 2 :
            glacon->position.x = x, glacon->position.y = y;
            glacon->vecteur.dx = glacon->vecteur.dy = 0;
            return 2;
            break;
        default :
            glacon->position.x = x, glacon->position.y = y;
            return 0;
    }
}
