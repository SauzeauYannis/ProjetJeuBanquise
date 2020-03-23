#include "jeux.h"



//
T_marteau *initMarteau(T_point position)
{
    T_marteau *marteau = (T_marteau *)malloc(sizeof(T_marteau));
    T_point posTete;
    T_vecteur vecteur;

    posTete.x = position.x - 1, posTete.y = position.y,
    vecteur.dx = vecteur.dy = 0;

    marteau->posCentre = position;
    marteau->tete.etat = HAUT;
    marteau->tete.position = posTete;
    marteau->tete.vecteur = vecteur;
    marteau->mouvement = FAUX;

    return marteau;
}



//
T_marteau **initTabMarteaux(T_banquise *banquise, int nombreMarteaux)
{
    T_marteau **marteaux = (T_marteau **)malloc(nombreMarteaux * sizeof(T_marteau *));

    int i;

    for (i = 0; i < nombreMarteaux; i++)
    {
        T_point posCentre,
                posTete;

        do
        {
            posCentre = caseGlaceAleatoire(banquise, 1);
            posTete.x = posCentre.x - 1, posTete.y = posCentre.y;
        } while (banquise->matrice[posTete.x][posTete.y] != GLACE);

        marteaux[i] = initMarteau(posCentre);

        enleveCaseGlace(banquise, marteaux[i]->posCentre.x, marteaux[i]->posCentre.y, MARTEAU_CENTRE);
        enleveCaseGlace(banquise, marteaux[i]->tete.position.x, marteaux[i]->tete.position.y, MARTEAU_TETE);
    }

    return marteaux;
}



//
T_marteau *marteauSelonPosition(T_marteau **tabMarteaux, T_point position, int nombreMarteaux)
{
    T_marteau *marteau = tabMarteaux[0];
    int i;

    for (i = 0; i < nombreMarteaux; i++)
    {
        marteau = tabMarteaux[i];

        if (marteau->tete.position.x == position.x
            &&marteau->tete.position.y == position.y)
        {
            break;
        }
    }

    return marteau;
}



//
void mouvementTete(T_banquise *banquise, T_marteau *marteau, T_booleen sensHorraire)
{
    ajouteCaseGlace(banquise, marteau->tete.position.x, marteau->tete.position.y);
    marteau->tete.vecteur.dx = marteau->tete.vecteur.dy = 0;

    if (sensHorraire == VRAI)
    {
        switch(marteau->tete.etat)
        {
        case HAUT_GAUCHE :
        case HAUT :
            marteau->tete.position.y += 1;
            marteau->tete.vecteur.dy += 1;
            break;
        case HAUT_DROITE :
        case DROITE :
            marteau->tete.position.x += 1;
            marteau->tete.vecteur.dx += 1;
            break;
        case BAS_DROITE :
        case BAS :
            marteau->tete.position.y -= 1;
            marteau->tete.vecteur.dy -= 1;
            break;
        default :
            marteau->tete.position.x -= 1;
            marteau->tete.vecteur.dx -= 1;
        }
        marteau->tete.etat += 1;
    }
    else
    {
        switch(marteau->tete.etat)
        {
        case HAUT_DROITE :
        case HAUT :
            marteau->tete.position.y -= 1;
            marteau->tete.vecteur.dy -= 1;
            break;
        case HAUT_GAUCHE :
        case GAUCHE :
            marteau->tete.position.x += 1;
            marteau->tete.vecteur.dx += 1;
            break;
        case BAS_GAUCHE :
        case BAS :
            marteau->tete.position.y += 1;
            marteau->tete.vecteur.dy += 1;
            break;
        default :
            marteau->tete.position.x -= 1;
            marteau->tete.vecteur.dx -= 1;
        }
        marteau->tete.etat = (marteau->tete.etat - 1) % 8;
    }

    enleveCaseGlace(banquise, marteau->tete.position.x, marteau->tete.position.y, MARTEAU_TETE);
}
