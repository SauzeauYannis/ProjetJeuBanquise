#include "jeux.h"



//Fonction qui initialise un glacon
T_glacon *initGlacon(int caseX, int caseY, int chanceFonte)
{
    T_point pos;                                              //Creer un point qui sera la position du glacon
    T_vecteur vect;                                           //Creer le vecteur du glacon
    T_glacon *glacon = (T_glacon *)malloc(sizeof(T_glacon));  //Alloue de la memoire pour le glacon

    pos.x = caseX, pos.y = caseY;                             //Initialise la postion du glacon via les parametres
    vect.dx = vect.dy = 0;                                    //Initialise le vecteur à 0

    glacon->position = pos;                                   //Initialise la position
    glacon->vecteur = vect;                                   //Initialise le vecteur
    glacon->pourcentage_fondre = chanceFonte;                 //Initialise le pourcentage de fonte
    //glacon->estFondu = PRESENT;

    return glacon;                                            //Retourne le glacon
}



//Fonction qui verifie que le vecteur du glacon est valide : HAUT BAS GAUCHE DROITE
int verifieVecteurGlacon(T_glacon *glacon)
{
    int dx = glacon->vecteur.dx, dy = glacon->vecteur.dy;                              //Recupere les vecteurs du glacon en parametre

    if(dx != 0 && dy != 0)                                                             //Verifie si il n'y a aucun des deux vecteurs a 0
    {
        printf("Le vecteur du glacon à la position x = %d y = %d est incorrecte !",
               glacon->position.x, glacon->position.y);                                //Affiche un message d'erreur

        return -1;                                                                     //Retourne une valeur d'echec
    }
    else                                                                               //Si les vecteurs sont bons
    {
        return 0;                                                                      //Retourne une valeur de succes
    }
}



//Fonction qui retourne le glacon a la position donnee
T_glacon *glaconSelonPosition(T_glacon **glacons, int posX, int posY, int nbGlacons)
{
    int i;                                     //Variable pour la boucle suivante

    for(i = 0; i < nbGlacons; i++)             //Boucle qui parcourt les glacons du tableau de glacons
    {
        if(posX == glacons[i]->position.x
           && posY == glacons[i]->position.y)  //Condition qui regarde si le position en paramettre correspond à celle du glacon
        {
            break;                             //Sort de la boucle
        }
    }
    return glacons[i];                         //Retourne le glacon qui verifie la condition du dessus
}



//Fonction qui se charge de deplacer le glacon en paramettre
int verifieDeplacementGlacon(T_glacon *glacon, T_banquise *banquise, T_joueur **joueurs, int nbJoueurs)
{

    int posx = glacon->position.x, posy = glacon->position.y,          //Position du glacon avant son deplacement
        x = posx + glacon->vecteur.dx, y = posy + glacon->vecteur.dy,  //Position vers laquelle le glacon se deplace
        taille = banquise->tailleN,                                    //Recupere la taille de la banquise
        caseValeur;                                                    //Variable pour prendre la valeur de la case

    ajouteCaseGlace(banquise, posx, posy);                             //Remplace le glacon par de la glace

    if(x < 0 || x >= taille || y < 0 || y >= taille)                   //Verifie si le glacon est dans la matrice
    {
        caseValeur = ERREUR;                                           //Met la valeur de la case a ERREUR
    }
    else                                                               //Si le glacon va bien dans la matrice
    {
        caseValeur = banquise->matrice[x][y];                          //Met la valeur de la case selon le deplacement du glacon
    }

    switch(caseValeur)                                                 //Selon la valeur de la case
    {
        case ERREUR :
        case DEPART :
        case ARRIVE :
        case ROCHER :
            glacon->vecteur.dx = glacon->vecteur.dy = 0;               //Arrete le glacon
            return 0;
            break;
        case JOUEUR :
            {
            T_joueur *joueur;                                          //Variable pour recuperer le joueur touche

            glacon->position.x = x, glacon->position.y = y;            //Fais bouger le glacon
            joueur = joueurSelonPosition(joueurs, x, y, nbJoueurs);    //Recupere le joueur que touche le glacon
            tuerJoueur(joueur, banquise);                              //Tue le joueur touche par le glacon
            return 0;
            break;
            }
        case GLACON :
            return 1;
            break;
        case EAU :
            glacon->position.x = x, glacon->position.y = y;             //Fais bouger le glacon
            glacon->vecteur.dx = glacon->vecteur.dy = 0;                //Arrete le glacon
            return 2;
            break;
        default :
            glacon->position.x = x, glacon->position.y = y;             //Fais bouger le glacon
            return 0;
    }
}



//Fonction qui regarde si le glaçon va fondre
int verifFonteGlacon(T_glacon *glacon)
{
    int chanceFonteGlacon = glacon->pourcentage_fondre;  //Récupère la valeur du pourcentage de fonte du glaçon

    if ((rand() % chanceFonteGlacon) == 0)                 //Condition qui verifie si le glaçon va fondre ou non
    {
        return 1;                                        //Retourne un entier qui valide la fonte du glaçon
    }
    else
    {
        return 0;                                        //Retourne un entier qui interdit la fonte du glaçon
    }
}
