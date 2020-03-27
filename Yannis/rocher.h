/***** Structures *****/


//Definition du type rocher
typedef struct
{
    T_point position;
} T_rocher;


/***** Fonctions *****/


//Initialise un rocher
//Compléxité linéaire
///Auteur : Yannis SAUZEAU
T_rocher initRocher(T_point position);


//Initialise un tableau de rocher
//Compléxité linaire
///Auteur : Yannis SAUZEAU
T_rocher *initTabRochers(T_banquise *banquise, int nombreRochers);
