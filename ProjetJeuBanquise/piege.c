#include "jeux.h"



//
T_piege caseEstPiege(T_joueur *joueur, int chancePiege)
{
    T_piege piege = CASE_GLACE;
    int aleatoire = rand() % chancePiege;

    if (aleatoire == 0
        && joueur->etat == ENCOURS)
    {
        piege = CASE_PIEGE;
    }

    return piege;
}



//
T_etat joueurEstPiege(T_joueur *joueur, int chancePiege)
{
    if (caseEstPiege(joueur, chancePiege) == CASE_PIEGE)
    {
        joueur->etat = PIEGE;
    }

    return joueur->etat;
}
