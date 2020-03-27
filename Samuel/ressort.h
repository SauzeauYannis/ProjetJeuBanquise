/***** Structures *****/


//Definition du type ressort
typedef struct
{
    T_point position;
} T_ressort;


/***** Fonctions *****/


//Fonction qui initialise un ressort
//Complexité : O(1)
///Auteur : Samuel GOUBEAU
T_ressort initRessort(T_point position);


//Initialise un tableau de ressort
//Complexité : O(n)
///Auteur : Samuel GOUBEAU
T_ressort *initTabRessorts(T_banquise *banquise, int nombreRessorts);


//Fonction qui va modifier le vecteur du glaçon quand il touche une ressort
//Complexité : O(1)
///Auteur : Samuel GOUBEAU
void glaconToucheRessort(T_glacon *glacon);
