/***** Structures *****/


//Enum�ration des �tats de la t�te du marteau
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


//D�finition du type t�te
typedef struct
{
    T_etatTete etat;    //Etats de la t�te
    T_point position;   //Position de la t�te
    T_vecteur vecteur;  //Vecteur de la t�te
    T_case sousTete;    //Case se trouvant sous la t�te
} T_tete;


//D�finition du type marteau
typedef struct
{
    T_point posCentre;    //Position du centre du marteau (statique)
    T_tete tete;          //La t�te du marteau
    T_booleen mouvement;  //Pour savoir si le marteau bouge
} T_marteau;


/***** Fonctions *****/


//Initialise le martau
//Compl�xit� lin�aire
///Auteur : Yannis SAUZEAU
T_marteau *initMarteau(T_point position);


//Initialise le tableau de marteaux
//Compl�xit� lin�aire
///Auteur : Yannis SAUZEAU
T_marteau **initTabMarteaux(T_banquise *banquise, int nombreMarteaux);


//Savoir quel marteau se trouve � tel position
//Compl�xit� lin�aire
///Auteur : Yannis SAUZEAU
T_marteau *marteauSelonPosition(T_marteau **tabMarteaux, int posX, int posY, int nombreMarteaux);


//Permet de faire bouger la t�te du marteau
//Compl�xit� lin�aire
///Auteur : Yannis SAUZEAU
void mouvementTete(T_banquise *banquise, T_marteau *marteau, T_booleen sensHorraire);


//Fonction qui retourne un bool�en par rapport au sens de rotation
//Complexit� : O(1)
///Auteur : Samuel GOUBEAU
T_booleen marteauSensRotation(T_marteau *marteau, T_glacon *glacon);
