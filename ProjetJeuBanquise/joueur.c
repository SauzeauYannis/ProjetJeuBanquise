#include "jeux.h"



//Retourne le type couleur qu'a choisi l'utilisateur
T_couleur choixCouleur()
{
    int couleur = -1;                                     //Declare un entier

    printf("\nChoisisez une couleur parmis : \n"
           "0 : Rouge\n"
           "1 : Vert\n"
           "2 : Bleu\n"
           "3 : Jaune\n");                                //Affiche le choix de couleur a l'utlisateur

    scanf("%d", &couleur);                                //Prend l'entier saisi par l'utilisateur

    if (couleur < 0 || couleur > 3)                       //Verifie que l'entier est compris entre 0 et 3
    {
        while (couleur < 0 || couleur > 3)                //Boucle jusqu'a ce que l'entier soit compris entre 0 et 3
        {
            printf("\nValeur incorrect, reessayer : ");   //Redemande a l'utilisateur de saisir une valeur
            scanf("%d", &couleur);                        //Recupere l'entier saisie
        }
    }

    return couleur;                                       //Retourne la couleur choisie
}



//Fonction qui retourne un type joueur selon un numero qui va l'identifier
T_joueur *initJoueur(int numeroJoueur)
{
    T_joueur *joueur = (T_joueur *)malloc(sizeof(T_joueur));                         //Alloue de la memoire au type joueur

    printf("Veuillez choisir un nom pour le joueur numero %d : ", numeroJoueur + 1); //Demande le nom au joueur
    scanf("%s", joueur->nom);                                                        //Initialise le nom du joueur

    joueur->couleur = choixCouleur();                                                  //Initialise la couleur du joueur
    joueur->identifiant = numeroJoueur;                                              //Initialise l'identifiant du joueur
    joueur->position.x = joueur->position.y = 0;                                     //Initialise la position du joueur
    joueur->vecteur.dx = joueur->vecteur.dy = 0;                                     //Initialise le veteur deplacement du joueur
    joueur->score = 1000;                                                            //Initialise le score du joueur
    joueur->etat = ENCOURS;                                                          //Initialise l'etat du joueur
    joueur->nbMort = 0;                                                              //Initialise le nombre de mort

    return joueur;                                                                   //Retourne un pointeur de type joueur
}



//Fait apparaitre le joueur sur sa case de depart
void departJoueur(T_banquise *banquise, T_joueur *joueur)
{
    T_point pos;                                      //Declare la position du joueur
    T_point depart = banquise->depart;                //Recupere la psotion de la case de depart

    switch (joueur->identifiant)                      //Retourne la case de depart du joueur selon son identifiant
    {
    case 0:                                           //Joueur 0 a droite de la case de depart
        pos.x = depart.x;
        pos.y = depart.y + 1;
        break;
    case 1:                                           //Joueur 1 en bas de la case de depart
        pos.x = depart.x + 1;
        pos.y = depart.y;
        break;
    case 2:                                           //Joueur 2 en gauche de la case de depart
        pos.x = depart.x;
        pos.y = depart.y - 1;
        break;
    default:                                          //Joueur 3 en haut de la case de depart
        pos.x = depart.x - 1;
        pos.y = depart.y;
    }

    joueur->position = pos;                           //Change la position du joueur

    enleveCaseGlace(banquise, pos.x, pos.y, JOUEUR);  //Ajoute le joueur sur la banquise
}



//Retourne une lettre du clavier qui correspond a un deplacement
char saisieDeplacement(T_joueur *joueur)
{
    char clavier = getchar();                                                                //Declare un caractere et l'initialise pour eviter un bug que nous comprenons pas

    changeCouleurTexte(joueur->couleur);                                                     //Change la couleur selon la couleur choisi par le joueur
    printf("%s", joueur->nom);                                                               //Affiche le nom du joueur choisi
    changeCouleurTexte(DEFAULT);                                                               //Remet la couleur blanche
    printf(" deplacez vous : ");                                                             //Demande au joueur ou il veut se deplacer
    scanf("%c", &clavier);                                                                   //Recupere la touche qui a ete frappe

    while (clavier != 'z'
           && clavier != 'q'
           && clavier != 's'
           && clavier != 'd'
           && clavier != 'Z'
           && clavier != 'Q'
           && clavier != 'S'
           && clavier != 'D')                                                                //Boucle qui fini quand l'utilisateur a rentree une bonne touche
    {
        printf("\r\nTouche incorrect, veuillez saisir une touche entre \"z, q, s, d\" : ");  //Re-demande le deplacement en rappellant les bonnes touches
        scanf("%c", &clavier);                                                               //Recupere la touche qui a ete frappe
    }

    return clavier;                                                                          //Retourne la bonne touche
}



//Retourne un entier en fonction du deplacement du joueur, et modifie la position de celui-ci
int verifieDeplacement(T_banquise *banquise, T_joueur *joueur, int caseX, int caseY, int caseValeur)
{
    switch (caseValeur)                                                                  //Retourne un entier selon la valeur de la case
    {
    case ERREUR:
        printf("\nDeplacement impossible : le joueur est en dehors des limites\n");      //Previens le joueur dans ce cas la
        return -1;                                                                       //Retourne une valeur d'echec pour prevenir la fonction suivante
        break;
    case JOUEUR:
        printf("\nDeplacement impossible : un autre joueur occupe deja la case\n");      //Previens le joueur dans ce cas la
        return -1;                                                                       //Retourne une valeur d'echec pour prevenir la fonction suivante
        break;
    case DEPART:
        printf("\nDeplacement impossible : le joueur ne peut pas aller sur le spawn\n"); //Previens le joueur dans ce cas la
        return -1;                                                                       //Retourne une valeur d'echec pour prevenir la fonction suivante
        break;
    case ROCHER:
        printf("\nDeplacement impossible : le joueur ne peut pas aller sur un rocher\n"); //Previens le joueur dans ce cas la
        return -1;                                                                        //Retourne une valeur d'echec pour prevenir la fonction suivante
        break;
    case RESSORT:
        printf("\nDeplacement impossible : le joueur ne peut pas interagir avec un ressort\n"); //Previens le joueur dans ce cas la
        return -1;                                                                        //Retourne une valeur d'echec pour prevenir la fonction suivante
        break;
    case GLACON:
        printf("\nDeplacement d'un glacon\n");                                           //Previens le joueur dans ce cas la
        return -2;                                                                       //Retourne une valeur d'echec pour prevenir la fonction suivante
        break;
    case EAU:
		tuerJoueur(joueur, banquise);
        return 0;                                                                        //Retourne une valeur d'echec pour prevenir la fonction suivante
        break;
    default :
        joueur->position.x = caseX;                                                      //Affectation de sa nouvelle position
        joueur->position.y = caseY;
        return 0;                                                                        //Retourne une valeur de succes pour la fonction suivante
    }
}


//Fonction qui s'occupe du deplacement du personnage en fonction de ses paramettres, et renvoie un entier en fonction du deplacement
int deplacementJoueur_bis(T_banquise *banquise, T_joueur *joueur, char deplacement)
{
    int jx = joueur->position.x,                                     //Recupere la position du joueur
        jy = joueur->position.y,
        x, y,                                                        //Variable pour simuler le deplacement du joueur
        taille = banquise->tailleN,                                  //Recupere la taille de la banquise
        caseValeur;                                                  //Variable qui recupere la valeur de la case ou le joueur va aller

    switch (deplacement)                                             //Effectue le decalage selon la touche mis en parametre et change le vecteur du joueur (utile pour la collision avec un glacon immobile)
    {
    case 'z' :
    case 'Z' :
        joueur->vecteur.dx = -1;
        joueur->vecteur.dy = 0;
        break;
    case 'q' :
    case 'Q' :
        joueur->vecteur.dx = 0;
        joueur->vecteur.dy = -1;
        break;
    case 's' :
    case 'S' :
        joueur->vecteur.dx = 1;
        joueur->vecteur.dy = 0;
        break;
    case 'd' :
    default :
        joueur->vecteur.dx = 0;
        joueur->vecteur.dy = 1;
    }


    x = jx + joueur->vecteur.dx;                                     //Simule la nouvelle position du joueur
    y = jy + joueur->vecteur.dy;

    if (x >= 0 && x < taille && y >= 0 && y < taille)                //Verifie si le joueur ne sort pas de la matrice
    {
        caseValeur = banquise->matrice[x][y];                        //Affecte la valeur de la case ou le joueur va
    }
    else                                                             //Si le joueur sort de la matrice
    {
        caseValeur = ERREUR;                                         //Affecte une valeur de case d'erreur
    }

    return verifieDeplacement(banquise, joueur, x, y, caseValeur);   //Retourne la valeur de la fonction qui verifie la case ou le joueur va aller
}



//Fonction qui permet le deplacement du personnage
int deplacementJoueur(T_banquise *banquise, T_joueur *joueur)
{

    char clavier = saisieDeplacement(joueur);                        //Recupere la bonne touche saisie par le joueur
    int correct = deplacementJoueur_bis(banquise, joueur, clavier);  //Stocke la valeur de la fonction precedente

    while (correct == -1)                                            //Tant que la valeur est mauvaise
    {
        clavier = saisieDeplacement(joueur);                         //On re-recupere la bonne touche saisie par le joueur
        correct = deplacementJoueur_bis(banquise, joueur, clavier);  //On re-stocke la valeur de la fonction precedente
    }

    if (correct == -2)                                               //Verifie si le joueur pousse un glacon
    {
        joueur->score += 100;                                        //Incremente le score du joueur
        return GLACON;                                               //Retourne la valeur qui correspond au glacon
    }
    else                                                             //Si le joueur va vers une case de glace
    {
        joueur->score -= 10;                                         //Decremente le score du joueur
        return GLACE;                                                //Retourne la valeur qui correspond a la glace
    }
}



//Cherche un joueur en fonction d'une position en paramettre
T_joueur *joueurSelonPosition(T_joueur **joueurs, int posX, int posY, int nbJoueurs)
{
    T_joueur *joueur;                           //Variable pour retourner le joueur
    int i;                                      //Variable pour la boucle suivante

    for(i = 0; i < nbJoueurs; i++)              //Regarde chaque joueur du tableau
    {
        if (posX == joueurs[i]->position.x
            && posY == joueurs[i]->position.y)  //Condition qui regarde si le position en paramettre correspond à celle du joueur
        {
            joueur = joueurs[i];                //Affecte le bon joueur
            break;                              //Sort de la boucle
        }
    }

    return joueur;                              //Retourne le joueur
}



//Fonction qui s'occupe de tuer le joueur et de le ramener au point de depart
void tuerJoueur(T_joueur *joueur, T_banquise *banquise)
{
    int posx = joueur->position.x, posy = joueur->position.y;  //Enregistre la position du joueur dans 2 varibles

    printf("\nLe joueur ");                                    //Affichage du message de mort du joueur
    changeCouleurTexte(joueur->couleur);
    printf("%s ", joueur->nom);
    changeCouleurTexte(BLANC);
    printf("est mort !\n");
    Sleep(2000);                                               //Attend 2 secondes pour laisser le temps au joueur de lire le message

    joueur->score -= 150;                                      //Enleve des points au joueur qui meurt
    joueur->nbMort += 1;                                       //Ajoute 1 au nombre de mort du joueur

    ajouteCaseGlace(banquise, posx, posy);                     //Ajoute une case GLACE sur la position où le joueur est mort
    departJoueur(banquise, joueur);                            //Fait reapparaitre le joueur sur sa case de depart
}
