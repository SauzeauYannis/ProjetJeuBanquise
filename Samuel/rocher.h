/***** Structures *****/


//Definition du type rocher
typedef struct
{
    T_point position;
} T_rocher;


/***** Fonctions *****/


//Fonction qui initialise un glacon
T_rocher initRocher(T_point position);
