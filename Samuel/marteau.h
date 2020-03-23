/***** Structures *****/



typedef enum
{
    HAUT,
    HAUT_DROITE,
    DROITE,
    BAS_DROITE,
    BAS,
    BAS_GAUCHE,
    GAUCHE,
    HAUT_GAUCHE
} T_etatTete;


//
typedef struct
{
    T_etatTete etat;
    T_point position;
    T_vecteur vecteur;
    T_case sousTete;    //Case se trouvant sous le marteau
} T_tete;


//
typedef struct
{
    T_point posCentre;
    T_tete tete;
    T_booleen mouvement;
} T_marteau;


/***** Fonctions *****/


//
T_marteau *initMarteau(T_point position);


//
T_marteau **initTabMarteaux(T_banquise *banquise, int nombreMarteaux);


//
T_marteau *marteauSelonPosition(T_marteau **tabMarteaux, int posX, int posY, int nombreMarteaux);


//
void mouvementTete(T_banquise *banquise, T_marteau *marteau, T_booleen sensHorraire);

//Fonction qui retourne un booléen par rapport au sens de rotation
T_booleen marteauSensRotation(T_marteau *marteau, T_glacon *glacon);
