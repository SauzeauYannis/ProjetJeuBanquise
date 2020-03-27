/***** Structures *****/


//Definition du type ressort
typedef struct
{
    T_point position;
} T_ressort;


/***** Fonctions *****/


//Fonction qui initialise un ressort
T_ressort initRessort(T_point position);


//Initialise un tableau de ressort
T_ressort *initTabRessorts(T_banquise *banquise, int nombreRessorts);


//Fonction qui va modifier le vecteur du glaçon quand il touche une ressort
void glaconToucheRessort(T_glacon *glacon);
