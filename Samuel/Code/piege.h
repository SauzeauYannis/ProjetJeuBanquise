/***** Structures *****/


//Enum�ration du type pi�ge
typedef enum
{
    CASE_GLACE,
    CASE_PIEGE
} T_piege;


/***** Fonctions *****/


//Dis si une case est un pi�ge
//Compl�xit� lin�aire
///Auteur : Yannis SAUZEAU
T_piege caseEstPiege(T_joueur *joueur, int chancePiege);


//Change l'etat du joueur si il est pi�g�
//Compl�xit� lin�aire
///Auteur : Yannis SAUZEAU
T_etat joueurEstPiege(T_joueur *joueur, int chancePiege);
