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

