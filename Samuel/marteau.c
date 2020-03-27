#include "jeux.h"



//Retourne un pointeur de type marteau dont le centre est la position en param�tre
T_marteau *initMarteau(T_point position)
{
    T_marteau *marteau = (T_marteau *)malloc(sizeof(T_marteau));  //Alloue de la m�moire pour un pointeur de marteau
    T_point posTete;                                              //Variable qui stocke la position de la t�te du marteau
    T_vecteur vecteur;                                            //Variable qui stocke le vecteur de la t�te du marteau

    posTete.x = position.x - 1, posTete.y = position.y,           //Met la t�te du marteau en haut de son centre
    vecteur.dx = vecteur.dy = 0;                                  //Initialise le vecteur � 0

    marteau->posCentre = position;                                //Initialise la position du centre du marteau
    marteau->tete.etat = HAUT;                                    //Initialise l'�tat de la t�te du marteau
    marteau->tete.position = posTete;                             //Initialise la position de la t�te du marteau
    marteau->tete.vecteur = vecteur;                              //Initialise le vecteur de la t�te du marteau
    marteau->mouvement = FAUX;                                    //Initialise le marteau sans mouvement

    return marteau;                                               //Retourne le marteau
}



//Retourne un tableau de marteaux selon une quantit� mise en param�tre
T_marteau **initTabMarteaux(T_banquise *banquise, int nombreMarteaux)
{
    T_marteau **marteaux = (T_marteau **)malloc(nombreMarteaux * sizeof(T_marteau *));                        //Alloue de la m�moire pour le tableau de marteaux

    int i;                                                                                                    //Variable pour la boucle suivante

    for (i = 0; i < nombreMarteaux; i++)                                                                      //Parcourt les marteaux
    {
        T_point posCentre, posTete;                                                                           //Variables qui stockent les positions de la t�te et du centre du marteau

        do
        {
            posCentre = caseGlaceAleatoire(banquise, 1);                                                      //Affecte une position al�atoire pour le centre
            posTete.x = posCentre.x - 1, posTete.y = posCentre.y;                                             //Met la t�te au-dessus du centre
        } while (banquise->matrice[posTete.x][posTete.y] != GLACE);                                           //Recommencen tant que la case au-dessus du centre est diff�rente d'une case de glace

        marteaux[i] = initMarteau(posCentre);                                                                 //Initialise le marteau i

        enleveCaseGlace(banquise, marteaux[i]->posCentre.x, marteaux[i]->posCentre.y, MARTEAU_CENTRE);        //Met le centre du marteau sur la banquise
        enleveCaseGlace(banquise, marteaux[i]->tete.position.x, marteaux[i]->tete.position.y, MARTEAU_TETE);  //Met la t�te du marteau sur la banquise
    }

    return marteaux;                                                                                          //Retourne le tableaux de marteau
}



//Retourne un marteau selon une position donn�e en param�tre
T_marteau *marteauSelonPosition(T_marteau **tabMarteaux, int posX, int posY, int nombreMarteaux)
{
    T_marteau *marteau = tabMarteaux[0];         //Ininitialise le marteau
    int i;                                       //Variable pour la boucle

    for (i = 0; i < nombreMarteaux; i++)         //Parcourt le tableau de marteaux
    {
        marteau = tabMarteaux[i];                //R�cup�re le i�me marteau

        if (marteau->tete.position.x == posX &&
            marteau->tete.position.y == posY)    //Verifie que la t�te du marteau se trouve � la position donn�e en param�tre
        {
            break;                               //Sort de la boucle
        }
    }

    return marteau;                              //Retourne le marteau qui se trouve � la position donn�e en param�tre
}



//Fait bouger la t�te du marteau d'une case selon le sens donn� par le param�tre sensHorraire
void mouvementTete(T_banquise *banquise, T_marteau *marteau, T_booleen sensHorraire)
{
    int posFutX = marteau->tete.position.x + marteau->tete.vecteur.dx,
        posFutY = marteau->tete.vecteur.dy + marteau->tete.position.y;                                              //Affecte la future position de la t�te du marteau

    if (banquise->matrice[posFutX][posFutY] == GLACON)                                                              //V�rifie si la position future est une case de type glacon
    {
        marteau->mouvement = FAUX;                                                                                  //Arrete le mouvement dans ce cas la
    }
    else                                                                                                            //Si la position future n'est pas une case de type glacon
    {
        if(marteau->tete.sousTete == GLACE)                                                                         //V�rifie que l'ancinne position du glacon �tait une glace
        {
            ajouteCaseGlace(banquise, marteau->tete.position.x, marteau->tete.position.y);                          //Met de la glace � l'ancienne position
        }
        else                                                                                                        //Si l'ancienne position n'est pas une glace
        {
            enleveCaseGlace(banquise, marteau->tete.position.x, marteau->tete.position.y, marteau->tete.sousTete);  //Met ce qu'il se trouvait � l'ancienne position de la t�te
        }

        marteau->tete.vecteur.dx = marteau->tete.vecteur.dy = 0;                                                    //Met les vecteurs du marteau � 0

        if (sensHorraire == VRAI)                                                                                   //V�rifie que le marteau bouge dans le sens horraire
        {
            switch(marteau->tete.etat)                                                                              //Change la position et les vetceurs du marteau selon son �tat
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

            marteau->tete.etat = (marteau->tete.etat + 1) % 8;                                                      //Incr�mente l'�tat du marteau modulo 8
        }
        else if (sensHorraire == FAUX)                                                                              //Si le marteau bouge dans le sens anti-horraire
        {
            switch(marteau->tete.etat)                                                                              //Change la position et les vetceurs du marteau selon son �tat
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

            marteau->tete.etat = (marteau->tete.etat - 1) % 8;                                                      //D�cr�mente l'�tat du marteau modulo 8
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
