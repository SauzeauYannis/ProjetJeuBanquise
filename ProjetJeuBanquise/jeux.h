/***** Structures *****/

//Enumeration de differentes couleur
typedef enum
{
    ROUGE,
    VERT,
    BLEU,
    JAUNE
} T_couleur;

//Definition du type point
typedef struct
{
    int x; //Point x = horizontal
    int y; //Point y = vertical
} T_point;

//Definition du type vecteur
typedef struct
{
    int dx; //Vecteur x = deplacement horizontal
    int dy; //Vecteur y = deplacement vertical
} T_vecteur;
