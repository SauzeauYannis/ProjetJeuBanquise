/***** Structures *****/


//Definition du type rocher
typedef struct
{
    T_point position;
} T_rocher;


/***** Fonctions *****/


//Initialise un rocher
//Compl�xit� lin�aire
//Yannis
T_rocher initRocher(T_point position);


//Initialise un tableau de rocher
//Compl�xit� linaire
//Yannis
T_rocher *initTabRochers(T_banquise *banquise, int nombreRochers);
