#include "jeux.h"



//Fonction qui initialise un glacon
T_glacon *initGlacon(T_point position, int chanceFonte)
{
    T_vecteur vect;                                           //Créé le vecteur du glacon
    T_glacon *glacon = (T_glacon *)malloc(sizeof(T_glacon));  //Alloue de la mémoire pour le glacon

    vect.dx = vect.dy = 0;                                    //Initialise les vecteurs a 0

    glacon->position = position;                              //Initialise la position
    glacon->vecteur = vect;                                   //Initialise le vecteur
    glacon->pourcentage_fondre = chanceFonte;                 //Initialise le pourcentage de fonte

    return glacon;                                            //Retourne le glacon
}



//Initialise un tableau de glacons
T_glacon **initTabGlacons(T_banquise *banquise, int nombreGlacons, int rechauffement)
{
    T_glacon **glacons = (T_glacon **)malloc(nombreGlacons * sizeof(T_glacon *));           //Alloue de la memoire pour le tableau de glacons

    int i;                                                                                  //Variable pour la boucle suivante

    for (i = 0; i < nombreGlacons; i++)                                                     //Boucle qui parcourt le tableau de glacons
    {
        T_point positionGlacon = caseGlaceAleatoire(banquise, 1);                           //Initialise une position aleatoire pour le glacon i

        glacons[i] = initGlacon(positionGlacon, rechauffement);                             //Initialise le glacon i

        enleveCaseGlace(banquise, glacons[i]->position.x, glacons[i]->position.y, GLACON);  //Met le glacon i a la place d'une glace
    }

    return glacons;                                                                         //Retourne le tableau de glaçons
}


//Fonction qui vérifie que le vecteur du glacon est valide : HAUT BAS GAUCHE DROITE
int verifieVecteurGlacon(T_glacon *glacon)
{
    int dx = glacon->vecteur.dx, dy = glacon->vecteur.dy;                              //Récupère les vecteurs du glacon en paramètre

    if(dx != 0 && dy != 0)                                                             //Vérifie si il n'y a aucun des deux vecteurs à 0
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



//Fonction qui retourne le glacon à la position donnée si il existe
T_glacon *glaconSelonPosition(T_glacon **glacons, int posX, int posY, int nbGlacons)
{
    int i;                                     //Variable pour la boucle suivante

    for(i = 0; i < nbGlacons; i++)             //Boucle qui parcourt le tableau de glacons
    {
        if(posX == glacons[i]->position.x
           && posY == glacons[i]->position.y)  //Condition qui regarde si la position en paramètre correspond à celle du glacon
        {
            break;                             //Sort de la boucle
        }
    }
    return glacons[i];                         //Retourne le glacon qui verifie la condition du dessus
}



//Fonction qui se charge de déplacer le glacon en paramètre
int verifieDeplacementGlacon(T_glacon *glacon, T_banquise *banquise, T_joueur **joueurs, int nbJoueurs)
{

    int posx = glacon->position.x, posy = glacon->position.y,          //Position du glacon avant son déplacement
        x = posx + glacon->vecteur.dx, y = posy + glacon->vecteur.dy,  //Position vers laquelle le glacon se déplace
        taille = banquise->tailleN,                                    //Récupère la taille de la banquise
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
        case MARTEAU_CENTRE :
            glacon->vecteur.dx = glacon->vecteur.dy = 0;               //Arrete le glacon
            return 0;
        case JOUEUR :
            {
            T_joueur *joueur;                                          //Variable pour recuperer le joueur touche

            glacon->position.x = x, glacon->position.y = y;            //Fais bouger le glaçon
            joueur = joueurSelonPosition(joueurs, x, y, nbJoueurs);    //Récupère le joueur que touche le glacon
            tuerJoueur(joueur, banquise);                              //Tue le joueur touché par le glaçon
            return 0;
            }
        case GLACON :
            return 1;
        case EAU :
            glacon->position.x = x, glacon->position.y = y;             //Fais bouger le glacon
            glacon->vecteur.dx = glacon->vecteur.dy = 0;                //Arrete le glacon
            return 2;
        case RESSORT :
            glaconToucheRessort(glacon);                                //Fonction qui va décider de là où le glaçon va se déplacer
            return 0;
        case MARTEAU_TETE :
            return 3;
        default :
            glacon->position.x = x, glacon->position.y = y;             //Fais bouger le glacon
            return 0;
    }
}



//Fonction qui regarde si le glaçon va fondre
int verifFonteGlacon(T_glacon *glacon)
{
    if ((rand() % glacon->pourcentage_fondre) == 0)  //Condition qui verifie si le glaçon va fondre ou non
    {
        return 1;                                    //Retourne un entier qui valide la fonte du glaçon
    }
    else
    {
        return 0;                                    //Retourne un entier qui interdit la fonte du glaçon
    }
}
