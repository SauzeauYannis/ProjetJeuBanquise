/***** Structures *****/


//Enumération des états de la tête du marteau
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


//Définition du type tête
typedef struct
{
    T_etatTete etat;    //Etats de la tête
    T_point position;   //Position de la tête
    T_vecteur vecteur;  //Vecteur de la tête
    T_case sousTete;    //Case se trouvant sous la tête
} T_tete;


//Définition du type marteau
typedef struct
{
    T_point posCentre;    //Position du centre du marteau (statique)
    T_tete tete;          //La tête du marteau
    T_booleen mouvement;  //Pour savoir si le marteau bouge
} T_marteau;


/***** Fonctions *****/


//Initialise le martau
//Compléxité linéaire
///Auteur : Yannis SAUZEAU
T_marteau *initMarteau(T_point position);


//Initialise le tableau de marteaux
//Compléxité linéaire
///Auteur : Yannis SAUZEAU
T_marteau **initTabMarteaux(T_banquise *banquise, int nombreMarteaux);


//Savoir quel marteau se trouve à tel position
//Compléxité linéaire
///Auteur : Yannis SAUZEAU
T_marteau *marteauSelonPosition(T_marteau **tabMarteaux, int posX, int posY, int nombreMarteaux);


//Permet de faire bouger la tête du marteau
//Compléxité linéaire
///Auteur : Yannis SAUZEAU
void mouvementTete(T_banquise *banquise, T_marteau *marteau, T_booleen sensHorraire);


//Fonction qui retourne un booléen par rapport au sens de rotation
//Complexité : O(1)
///Auteur : Samuel GOUBEAU
T_booleen marteauSensRotation(T_marteau *marteau, T_glacon *glacon);
