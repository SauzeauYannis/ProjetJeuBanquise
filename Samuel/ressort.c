#include "jeux.h"



T_ressort initRessort(T_point position)
{
    T_ressort ressort;

    ressort.position = position;

    return ressort;
}



//
T_ressort *initTabRessorts(T_banquise *banquise, int nombreRessorts)
{
    T_ressort *ressorts = (T_ressort *)malloc(nombreRessorts * sizeof(T_ressort));

    int i;

    for (i = 0; i < nombreRessorts; i++)
    {
        T_point positionRessort = caseGlaceAleatoire(banquise, 1);

        ressorts[i] = initRessort(positionRessort);

        enleveCaseGlace(banquise, ressorts[i].position.x, ressorts[i].position.y, RESSORT);
    }

    return ressorts;
}


void glaconToucheRessort(T_glacon *glacon)
{
    int direction = rand()% 3;
    int Gdx = glacon->vecteur.dx, Gdy = glacon->vecteur.dy;

    switch(direction)
    {
    case 0 :
        glacon->vecteur.dx *= -1, glacon->vecteur.dy *= -1;
        break;
    case 1 :
        glacon->vecteur.dx = Gdy * -1, glacon->vecteur.dy = Gdx * -1;
        break;
    default :
        glacon->vecteur.dx = Gdy, glacon->vecteur.dy = Gdx;
    }
}
