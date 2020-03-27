#include "jeux.h"



//Retourne un type piège pour vérifier qu'une case est un piège ou pas avec une probabilité d'être piégé donnée en paramètre par chancePiege
T_piege caseEstPiege(T_joueur *joueur, int chancePiege)
{
    T_piege piege = CASE_GLACE;             //Initialise le piege à glace
    int aleatoire = rand() % chancePiege;   //Stocke une valeur aléatoire modulo chancePiege

    if (aleatoire == 0 &&
        joueur->etat == ENCOURS)            //Vérifie que le joueur n'est pas piégé et que la valeur aléatoire est égal à 0
    {
        piege = CASE_PIEGE;                 //Change le piège en vrai piège
    }

    return piege;                           //Retourne le piège
}



//Retourne l'état du joueur qui est modifié s'il est piégé
T_etat joueurEstPiege(T_joueur *joueur, int chancePiege)
{
    if (caseEstPiege(joueur, chancePiege) == CASE_PIEGE)   //Vérifie si le joueur est tombé dans un piège
    {
        joueur->etat = PIEGE;                              //Change l'état du joueur pour savoir qu'il est piégé
    }

    return joueur->etat;                                   //Retourne l'état du joueur
}
