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
T_marteau *marteauSelonPosition(T_marteau **tabMarteaux, int posX, int posY, int nombreMarteaux)
{
    T_marteau *marteau = tabMarteaux[0];
    int i;

    for (i = 0; i < nombreMarteaux; i++)
    {
        marteau = tabMarteaux[i];

        if (marteau->tete.position.x == posX
            &&marteau->tete.position.y == posY)
        {
            break;
        }
    }

    return marteau;
}



//
void mouvementTete(T_banquise *banquise, T_marteau *marteau, T_booleen sensHorraire)
{
    int posFutX, posFutY;

    posFutX = marteau->tete.position.x + marteau->tete.vecteur.dx, posFutY = marteau->tete.vecteur.dy + marteau->tete.position.y;

    if(banquise->matrice[posFutX][posFutY] == GLACON)
    {
        marteau->mouvement = FAUX;
    }
    else
    {
        if(marteau->tete.sousTete == GLACE)
        {
            ajouteCaseGlace(banquise, marteau->tete.position.x, marteau->tete.position.y);
        }
        else
        {
            enleveCaseGlace(banquise, marteau->tete.position.x, marteau->tete.position.y, marteau->tete.sousTete);
        }

        marteau->tete.vecteur.dx = marteau->tete.vecteur.dy = 0;

        if (sensHorraire == VRAI)
        {
            switch(marteau->tete.etat)
            {
            case HAUT_GAUCHE :
                marteau->tete.position.y += 1;
                marteau->tete.vecteur.dy = 1;
                break;
            case HAUT :
                marteau->tete.position.y += 1;
                marteau->tete.vecteur.dx = 1;
                break;
            case HAUT_DROITE :
                marteau->tete.position.x += 1;
                marteau->tete.vecteur.dx = 1;
                break;
            case DROITE :
                marteau->tete.position.x += 1;
                marteau->tete.vecteur.dy = -1;
                break;
            case BAS_DROITE :
                marteau->tete.position.y -= 1;
                marteau->tete.vecteur.dy = -1;
                break;
            case BAS :
                marteau->tete.position.y -= 1;
                marteau->tete.vecteur.dx = -1;
                break;
            case BAS_GAUCHE :
                marteau->tete.position.x -= 1;
                marteau->tete.vecteur.dx = -1;
                break;
            default :
                marteau->tete.position.x -= 1;
                marteau->tete.vecteur.dy = 1;
            }
            marteau->tete.etat = (marteau->tete.etat + 1) % 8;
        }
        else if (sensHorraire == FAUX)
        {
            switch(marteau->tete.etat)
            {
            case HAUT_DROITE :
                marteau->tete.position.y -= 1;
                marteau->tete.vecteur.dy = -1;
                break;
            case HAUT :
                marteau->tete.position.y -= 1;
                marteau->tete.vecteur.dx = 1;
                break;
            case HAUT_GAUCHE :
                marteau->tete.position.x += 1;
                marteau->tete.vecteur.dx = 1;
                break;
            case GAUCHE :
                marteau->tete.position.x += 1;
                marteau->tete.vecteur.dy = 1;
                break;
            case BAS_GAUCHE :
                marteau->tete.position.y += 1;
                marteau->tete.vecteur.dy = 1;
                break;
            case BAS :
                marteau->tete.position.y += 1;
                marteau->tete.vecteur.dx = -1;
                break;
            case BAS_DROITE :
                marteau->tete.position.x -= 1;
                marteau->tete.vecteur.dx = -1;
                break;
            default :
                marteau->tete.position.x -= 1;
                marteau->tete.vecteur.dy = -1;
            }
            marteau->tete.etat = (marteau->tete.etat - 1) % 8;
        }
        else
        {
            marteau->mouvement = FAUX;
        }

        marteau->tete.sousTete = banquise->matrice[marteau->tete.position.x][marteau->tete.position.y];

        enleveCaseGlace(banquise, marteau->tete.position.x, marteau->tete.position.y, MARTEAU_TETE);
    }
}


//Fonction qui retourne un bool�en par rapport au sens de rotation
T_booleen marteauSensRotation(T_marteau *marteau, T_glacon *glacon)
{
    int Gdx = glacon->vecteur.dx, Gdy = glacon->vecteur.dy;   //Enregistre le vecteur du gla�on
    marteau->tete.vecteur.dx = marteau->tete.vecteur.dy = 0;  //Met le vecteur du marteau � 0 et arrete le mouvement de la t�te

    switch(marteau->tete.etat)                                //Switch qui permet de connaitre le sens de rotation du marteau en fonction de l� o� se trouve la t�te et de l� o� tappe le gla�on
    {
    case HAUT :
        if (Gdy == 1)                                         //Si le gla�on se d�place vers la droite
        {
            glacon->vecteur.dx = -1, glacon->vecteur.dy = 0;  //Change le vecteur du gla�on pour son prochain d�placement
            marteau->tete.vecteur.dy = 1;                     //Change le vecteur de la t�te du marteau
            return VRAI;                                      //Renvoie VRAI pour que la t�te du marteau se d�place dans le sens horaire
        }
        else if (Gdy == -1)                                   //Si le gla�on se d�place vers la gauche
        {
            glacon->vecteur.dx = -1, glacon->vecteur.dy = 0;  //Change le vecteur du gla�on pour son prochain d�placement
            marteau->tete.vecteur.dy = -1;                    //Change le vecteur de la t�te du marteau
            return FAUX;                                      //Renvoie FAUX pour que la t�te du marteau se d�place dans le sens antihoraire
        }
        else  //Si le gla�on se d�place sur l'axe x
        {
            glacon->vecteur.dx = 0, glacon->vecteur.dy = 0;  //Arr�te le gla�on pour son prochain d�placement
            return ECHEC;                                    //Renvoir ECHEC pour signifier que le marteau ne fasse rien
        }
    case DROITE :
        if (Gdx == 1)                                        //Si le gla�on se d�place vers le bas
        {
            glacon->vecteur.dx = 0, glacon->vecteur.dy = 1;
            marteau->tete.vecteur.dx = 1;
            return VRAI;
        }
        else if (Gdx == -1)                                  //Si le gla�on se d�place vers le haut
        {
            glacon->vecteur.dx = 0, glacon->vecteur.dy = 1;
            marteau->tete.vecteur.dx = -1;
            return FAUX;
        }
        else
        {
            glacon->vecteur.dx = 0, glacon->vecteur.dy = 0;
            return ECHEC;
        }
    case BAS :
        if (Gdy == -1)                                       //Si le gla�on se d�place vers la gauche
        {
            glacon->vecteur.dx = 1, glacon->vecteur.dy = 0;
            marteau->tete.vecteur.dy = -1;
            return VRAI;
        }
        else if (Gdy == 1)                                   //Si le gla�o  se d�place vers la droite
        {
            glacon->vecteur.dx = 1, glacon->vecteur.dy = 0;
            marteau->tete.vecteur.dy = 1;
            return FAUX;
        }
        else
        {
            glacon->vecteur.dx = 0, glacon->vecteur.dy = 0;
            return ECHEC;
        }
    case GAUCHE :
        if (Gdx == -1)                                        //Si le gla�on se d�place vers le haut
        {
            glacon->vecteur.dx = 0, glacon->vecteur.dy = -1;
            marteau->tete.vecteur.dx = -1;
            return VRAI;
        }
        else if (Gdx == 1)                                    //Si le gla�on se d�place vers le bas
        {
            glacon->vecteur.dx = 0, glacon->vecteur.dy = -1;
            marteau->tete.vecteur.dx = 1;
            return FAUX;
        }
        else
        {
            glacon->vecteur.dx = 0, glacon->vecteur.dy = 0;
            return ECHEC;
        }
    }
}
