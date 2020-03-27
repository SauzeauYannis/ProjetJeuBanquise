/***** Structures *****/


//Enumération du type piège
typedef enum
{
    CASE_GLACE,
    CASE_PIEGE
} T_piege;


/***** Fonctions *****/


//Dis si une case est un piège
//Compléxité linéaire
//Yannis
T_piege caseEstPiege(T_joueur *joueur, int chancePiege);


//Change l'etat du joueur si il est piégé
//Compléxité linéaire
//Yannis
T_etat joueurEstPiege(T_joueur *joueur, int chancePiege);
