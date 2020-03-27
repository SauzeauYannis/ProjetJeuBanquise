#include "jeux.h"



//Retourne un type pi�ge pour v�rifier qu'une case est un pi�ge ou pas avec une probabilit� d'�tre pi�g� donn�e en param�tre par chancePiege
T_piege caseEstPiege(T_joueur *joueur, int chancePiege)
{
    T_piege piege = CASE_GLACE;             //Initialise le piege � glace
    int aleatoire = rand() % chancePiege;   //Stocke une valeur al�atoire modulo chancePiege

    if (aleatoire == 0 &&
        joueur->etat == ENCOURS)            //V�rifie que le joueur n'est pas pi�g� et que la valeur al�atoire est �gal � 0
    {
        piege = CASE_PIEGE;                 //Change le pi�ge en vrai pi�ge
    }

    return piege;                           //Retourne le pi�ge
}



//Retourne l'�tat du joueur qui est modifi� s'il est pi�g�
T_etat joueurEstPiege(T_joueur *joueur, int chancePiege)
{
    if (caseEstPiege(joueur, chancePiege) == CASE_PIEGE)   //V�rifie si le joueur est tomb� dans un pi�ge
    {
        joueur->etat = PIEGE;                              //Change l'�tat du joueur pour savoir qu'il est pi�g�
    }

    return joueur->etat;                                   //Retourne l'�tat du joueur
}
