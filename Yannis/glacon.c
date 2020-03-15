#include "jeux.h"



//Fonction qui initialise un glacon
T_glacon *initGlacon(int caseX, int caseY)
{
    T_point pos;                                              //Creer un point qui sera la position du glacon
    T_vecteur vect;                                           //Creer le vecteur du glacon
    T_glacon *glacon = (T_glacon *)malloc(sizeof(T_glacon));  //Alloue de la memoire pour le glacon

    pos.x = caseX, pos.y = caseY;                             //Initialise la postion du glacon via les parametres
    vect.dx = vect.dy = 0;                                    //Initialise le vecteur à 0

    glacon->position = pos;                                   //Initialise la position
    glacon->vecteur = vect;                                   //Initialise le vecteur
    glacon->pourcentage_fondre = 0;                           //Initialise le pourcentage de fonte

    return glacon;                                            //Retourne le glacon
}



//Initialise un tableau remplit de n glacons (n est un paramettre de l fonction)
T_glacon **initTabGlacon(T_banquise *banquise, int nbGlacons)
{
    T_glacon **glaconTab = (T_glacon **)malloc(nbGlacons * sizeof(T_glacon *));  //Alloue de la memoire pour le tableau de glacons
    int i;                                                                       //Variable pour la boucle for

    for(i = 0; i < nbGlacons; i++)                                               //Ajoute n glacons initialises à des positions alleatoires sur la banquise
    {
        T_point pos = caseGlaceAleatoire(banquise, 1);                           //Recupere une position de glace aleatoire

        glaconTab[i] = initGlacon(pos.x, pos.y);                                 //Ajoute le glacon dans le tableau
    }

    return glaconTab;                                                            //Retourne le tableau de glaces initialisee
}



//Fonction qui verifie que le vecteur du glacon est valide : HAUT BAS GAUCHE DROITE
int verifieVecteurGlacon(T_glacon *glacon)
{
    int dx = glacon->vecteur.dx, dy = glacon->vecteur.dy;                              //Recupere les vecteurs du glacon en parametre

    if(dx != 0 && dy != 0)                                                             //Verifie si il n'y a aucun des deux vecteurs a zero
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



//Fonction qui se charge de deplacer le glacon en paramettre
int deplacementGlacon(T_glacon *glacon, T_banquise *banquise, T_joueur **joueurs, int nbJoueurs)
{
    ajouteCaseGlace(banquise, glacon->position.x, glacon->position.y);

    int posx = glacon->position.x, posy = glacon->position.y;          //Position du glacon avant son deplacement
    int x = posx + glacon->vecteur.dx, y = posy + glacon->vecteur.dy;  //Position vers laquelle le glacon se deplace
    int taille = banquise->tailleN;
    int caseValeur;
    T_joueur *joueur;

    if(x < 0 || x >= taille || y < 0 || y >= taille)                   //Verifie si le glacon se deplace en dehors du cadre
    {
        caseValeur = -1;
    }
    else
    {
        caseValeur = banquise->matrice[x][y];
    }

    switch(caseValeur)
    {
        case ERREUR :
        case DEPART :
        case ARRIVE :
            glacon->vecteur.dx = glacon->vecteur.dy = 0;
            return 0;
            break;
        case JOUEUR :
            glacon->position.x = x, glacon->position.y = y;
            joueur = joueurSelonPoisition(joueurs, x, y, nbJoueurs);
            tuerJoueur(joueur, banquise);
            return 0;
            break;
        case EAU :
            glacon->position.x = x, glacon->position.y = y;
            glacon->vecteur.dx = glacon->vecteur.dy = 0;
            return 2;
            break;
        default :
            glacon->position.x = x, glacon->position.y = y;
            return 0;
    }
}
