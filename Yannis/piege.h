/***** Structures *****/


//
typedef enum
{
    CASE_GLACE,
    CASE_PIEGE
} T_piege;


/***** Fonctions *****/


//
T_piege caseEstPiege(T_joueur *joueur, int chancePiege);


//
T_etat joueurEstPiege(T_joueur *joueur, int chancePiege);
