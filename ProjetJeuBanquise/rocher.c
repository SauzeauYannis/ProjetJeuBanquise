#include "jeux.h"



//
T_rocher initRocher(T_point pos)
{
    T_rocher rocher;

    rocher.position = pos;

    return rocher;
}



//
T_rocher *initTabRochers(T_banquise *banquise, int nombreRochers)
{
    T_rocher *rochers = (T_rocher *)malloc(nombreRochers * sizeof(T_rocher));

    int i;

    for (i = 0; i < nombreRochers; i++)
    {
        T_point positionRocher = caseGlaceAleatoire(banquise, 1);

        rochers[i] = initRocher(positionRocher);

        enleveCaseGlace(banquise, rochers[i].position.x, rochers[i].position.y, ROCHER);
    }

    return rochers;
}
