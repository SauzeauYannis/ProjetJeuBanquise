#include "jeux.h"

//Affiche le Menu du jeu
void afficheMenu()
{
    printf("Jeu de la banquise\n"
           "\n"
           "Nombre de joueurs : 1-4 joueurs\n"
           "\n"
           "Creer par :\n"
           "Samuel GOUBEAU\n"
           "Yannis SAUZEAU\n"
           "\n"
           "Bonne chance !\n"
           "\n"
           "Appuyer sur entree pour continuer");  //Affiche le Menu

    char entree;                                  //Stocke un caractere
    entree = getchar();                           //Attend que la touche entree soit pressee

    system("cls");                                //Nettoie l'ecran

    printf("Regles du jeux\n"
           "\n"
           "A venir\n"
           "\n"
           "Appuyer sur entree pour continuer");  //Affiche les regles du jeu

    entree = getchar();                           //Attend que la touche entree soit pressee

    system("cls");                                //Nettoie l'ecran

    printf("Controle\n"
           "\n"
           "Pour se deplacer, utiliser les "
           "touches du clavier suivante :\n"
           "Z : haut\n"
           "Q : gauche\n"
           "S : bas\n"
           "D : droite\n"
           "\n"
           "Appuyer sur entree pour commencer le jeu"); //Affiche les controles

    entree = getchar();                          //Attend que la touche entree soit pressee

    system("cls");                               //Nettoie l'ecran
}



//Change la couleur du texte selon la type couleur mis en parametre
void changeCouleurTexte(T_couleur couleur)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); //Declare la console windows du jeu

    switch (couleur)                                  //Change la couleur du texte de la console selon le type couleur mis en parametre
    {
    case ROUGE:
        SetConsoleTextAttribute(console, 12);
        break;
    case VERT :
        SetConsoleTextAttribute(console, 2);
        break;
    case BLEU:
        SetConsoleTextAttribute(console, 9);
        break;
    case JAUNE :
        SetConsoleTextAttribute(console, 14);
        break;
    case TURQUOISE :
        SetConsoleTextAttribute(console, 11);
        break;
    case ROSE :
        SetConsoleTextAttribute(console, 13);
        break;
    case GRIS :
        SetConsoleTextAttribute(console, 8);
        break;
    case BLEUFONCE :
        SetConsoleTextAttribute(console, 1);
        break;
    default :
        SetConsoleTextAttribute(console, 15);
    }
}



//Ajoute entre 1 et 4 joueurs au jeu
void ajouteJoueurs(T_jeu *jeu)
{
    int nbJoueurs = 0;                                 //Declare le nombre de joueurs

    while (nbJoueurs < 1 || nbJoueurs > 4)             //Verifie que l'utilisateur rentre un chiffre entre 1 et 4
    {
        printf("Nombre de joueurs (entre 1 et 4) : "); //Demande de rentrer un chiffre
        scanf("%d", &nbJoueurs);                       //Recupere le chiffre rentre
        system("cls");                                 //Nettoie la console
    }

    jeu->joueurs = (T_joueur **)realloc(jeu->joueurs, nbJoueurs * sizeof(T_joueur *));

    int i;                                             //Declare un entier pour la boucle

    for (i = 0; i < nbJoueurs; i++)                    //Rentre dans la boucle autant de fois qu'il y a de joueurs
    {

        jeu->joueurs[i] = initJoueur(i);                                                                   //Ajoute un joueur
        jeu->nombreJoueur++;                                                                               //Rajoute 1 au nombres de joueurs

        departJoueur(jeu->banquise, jeu->joueurs[i]);

        system("cls");                                 //Nettoie la console
    }
}

//Retourne un pointeur de type jeu en fonction du niveau et de la taille de la banquise
T_jeu *initJeux(int niveau, int taille)
{
    T_jeu *jeu = (T_jeu *)malloc(sizeof(T_jeu));               //Aloue de l'espace memoire a un pointeur de type jeu

    jeu->banquise = initBanquise(taille, 2);                      //Initialise la banquise dans le jeu
    jeu->joueurs = (T_joueur **)malloc(sizeof(T_joueur *));                                       //Aloue de la memoire pour creer un tableau de pointeur de joueur
    jeu->glacons = (T_glacon **)malloc(sizeof(T_glacon *));
    jeu->nombreJoueur = 0;                                     //Initialise le nombre de joueur
    jeu->nombreGlacon = 4;                                     //Initialise le nombre de glacon
    jeu->nombreTour = 0;                                       //Initialise le nombre de tour
    jeu->IdJeu = niveau;                                       //Initialise le niveau

    remplitBanquise(jeu->banquise);                  //Remplit la banquise
    ajouteJoueurs(jeu);                                        //Ajoute les joueurs
    ajouteGlacon(jeu);

    return jeu;                                                //Retourne le pointeur de type jeu
}



//Affiche le jeu avec les joueurs en couleur
void afficheJeu(T_jeu *jeu)
{
    int taille = jeu->banquise->tailleN;        //Recupere la taille de la banquise
    int i, j;                                   //Declare deux entiers pour les boucles for

    for (i = 0; i < taille; i++)                //Boucle qui parcourt les lignes de la matrice
    {
        printf("| ");                           //Esthetique
        for (j = 0; j < taille; j++)            //Boucle qui parcourt les collones de la matrice
        {
            int pos = jeu->banquise->matrice[i][j]; //Declare la position parcouru

            switch (pos)
            {
            case JOUEUR :
                {
                T_joueur *joueur = joueurSelonPoisition(jeu->joueurs, i, j, jeu->nombreJoueur);

                changeCouleurTexte(joueur->couleur);
                break;
                }
            case DEPART :
                changeCouleurTexte(GRIS);       //Change la couleur en gris pour le depart
                break;
            case ARRIVE :
                changeCouleurTexte(ROSE);       //Change la couleur en rose pour l'arrive
                break;
            case GLACON :
                changeCouleurTexte(BLEUFONCE);  //Change la couleur en bleu-gris pour le glacon
                break;
            case EAU :
                changeCouleurTexte(TURQUOISE);  //Change la couleur en turquoise pour l'eau
                break;
            default :
                changeCouleurTexte(BLANC);            //Affiche la case de la matrice qui se trouve a la ligne i et la colonne j
            }

            printf("%d ", pos);

            changeCouleurTexte(BLANC);
        }
        printf("|\n");                          //Esthetique
    }
}



//Fonction qui change la valeur de la banquise en fonction de la position du joueur et d'une valeur
void rafraicheBanquise(T_jeu *jeu, T_joueur *joueur, T_case val)
{
    int posx = joueur->position.x, posy = joueur->position.y;  //Variables contenant la position du joueur

    if (val == GLACE)
    {
        ajouteCaseGlace(jeu->banquise, posx, posy);
    }
    else
    {
        enleveCaseGlace(jeu->banquise, posx, posy, val);
    }
}



//Fonction qui s'occupe d'effectuer le tour d'un joueur
int tourJoueur(T_jeu *jeu, int numJoueur)
{
    int caseValeur;
    int **matrice = jeu->banquise->matrice;
    int verifDep;
    T_joueur *joueur = jeu->joueurs[numJoueur];
    system("cls");                                                                           //efface le terminal
    printf("Tour %d\n", jeu->nombreTour);
    afficheJeu(jeu);                                                                         //Affiche la banquise dans le terminal
    rafraicheBanquise(jeu, joueur, GLACE);                                  //Met un 0 sur la futur ancienne case du joueur sur la banquise
    verifDep = deplacementJoueur(jeu->banquise, joueur);                 //Effectue le deplacement du joueur sur la banquise
    caseValeur = matrice[joueur->position.x][joueur->position.y];
    if(verifDep == 4)
    {
        for(int j = 0; j<jeu->nombreGlacon; j++)                                          //Regarde chaque glacon du tableau
        {
            if((joueur->position.x + joueur->vecteur.dx) == jeu->glacons[j]->position.x && (joueur->position.y+joueur->vecteur.dy) == jeu->glacons[j]->position.y)  //Condition qui regarde si le position en paramettre correspond � celle du glacon
            {
                printf("x = %d\ny = %d\n", jeu->glacons[j]->position.x, jeu->glacons[j]->position.y);
                joueurPousseGlacon(jeu->joueurs[numJoueur], jeu->glacons[j], jeu);
                break;
            }
        }
    }
    rafraicheBanquise(jeu, jeu->joueurs[numJoueur], JOUEUR);                                 // Met un 1 sur la nouvelle case du joueur sur la banquise
    fonteBanquise(jeu->banquise, 4);
    return caseValeur;
}


//Ressort un entier qui determine si la partie est finie ou non
int victoire(T_jeu *jeu, int caseVal, int i)
{
    if (caseVal == 3)                                                              //Valeur de l'entier correspondant � l'arrivee
    {
        jeu->joueurs[i]->etat = 1;                                                 //Change l'etat de ce joueur pour le designer en tant que gagnant
        printf("La partie est finie ! %s est victorieux !", jeu->joueurs[i]->nom); //Affiche que la partie est finie, ainsi que le nom du gagnant
        jeu->joueurs[i]->score += 1000;                                            //Le gagnant recois 1000 point
        Sleep(3000);                                                               //Attend 3s avant de passer � l'instruction suivante
        return 1;                                                                  //Retourne l'entier 1 pour signaler une victoire
    }
    else
    {
        return 0;                                                                  //Retourne l'entier 0 pour signaler que la partie continue
    }
}



//Affiche le scrore � la fin de la partie
void afficheScore(T_jeu *jeu)
{
    int i;
    system("cls");                                           //Efface le terminal
    printf("Score de la partie : \n\n");
    for(i = 0; i<jeu->nombreJoueur; i++)                 //Permet d'afficher le score de chaque joueur
    {
        printf("->Joueur %d\n", i+1);
        printf("    Nom : %s\n", jeu->joueurs[i]->nom);
        printf("    Mort : %d\n", jeu->joueurs[i]->nbMort);
        printf("    Score : %d\n", jeu->joueurs[i]->score);
        if (jeu->joueurs[i]->etat == 1)                      //Permet de savoir si le joueur est gagnant ou perdant
        {
            printf("    Etat : GAGNANT\n");
        }
        else
        {
            printf("    Etat : PERDANT\n");
        }
        printf("\n");
    }
}

//Fonction qui retourne le glacon sur lequel le joueur va buter
T_glacon *returnGlaconJoueur(T_glacon **glacons, int posX, int posY, int nbGlacons)
{
    int i;

    for(i = 0; i < nbGlacons; i++)                                          //Regarde chaque glacon du tableau
    {
        if(posX == glacons[i]->position.x && posY == glacons[i]->position.y)  //Condition qui regarde si le position en paramettre correspond � celle du glacon
        {
            break;
        }
    }
    return glacons[i];
}

//Fonction qui joue un niveau selectionne jusqu'� la victoire d'un joueur
void joueNiveau(T_jeu *jeu)
{
    jeu->nombreTour = 1;
    int caseVal, finPartie = 0; //caseVal sert � connaitre la valeur de la case, et finPartie sert � mettre fin � la partie en cours
    int i;
    T_glacon *glacon;

    while(finPartie == 0)
    {
        for(i = 0; i<jeu->nombreJoueur; i++)    //Boucle for qui permet � chaque joueur de jouer pour un tour
        {
            caseVal = tourJoueur(jeu, i);           //Tour du joueur i
            finPartie = victoire(jeu, caseVal, i);  //Donne un entier si la partie est gagnee, ou si elle continue
            if (caseVal == ARRIVE)                       //Permet de reellement stopper le jeu, pour ainsi eviter les joueurs suivant de jouer
                break;                              //Brise la boucle for
            if (caseVal == GLACON)
            {
                glacon = returnGlaconJoueur(jeu->glacons, jeu->joueurs[i]->position.x, jeu->joueurs[i]->position.y, jeu->nombreGlacon);
                printf("x = %d\ny = %d\n", glacon->position.x, glacon->position.y);
                Sleep(2000);
                joueurPousseGlacon(jeu->joueurs[i], glacon, jeu);
            }
        }
        jeu->nombreTour += 1;
    }
    afficheScore(jeu);  //Affiche le score du jeu
    Sleep(5000);        //Donne 5s au joueur pour lire les scores
    system("cls");
    printf("Merci d'avoir joue !\n");
}




//Fonction qui renvoie un entier qui permet de rejouer une partie
int rejouer()
{
    char c;  //Enregistre la valeur saisie par l'utilisateur
    printf("\nVoulez vous rejouer ? (Tapez \"y\" pour oui ou \"n\" pour non) : "); //Permet au joueur de relancer une partie
    c = getchar();
    c = getchar();

    while (c != 'n' && c != 'y')
    {
        printf("\nChoix inconnue ! Veuillez reessayer : ");
        c = getchar();
    }

    if (c == 'y')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


//Ajoute un glacon sur la banquise
void ajouteGlacon(T_jeu *jeu)
{
    int nbGlacons = jeu->nombreGlacon;

    jeu->glacons = (T_glacon **)realloc(jeu->glacons,jeu->nombreGlacon * sizeof(T_glacon *));

    for(int i = 0; i < nbGlacons; i++)
    {
        T_point glacon = caseGlaceAleatoire(jeu->banquise, 1);

        jeu->glacons[i] = (T_glacon *)initGlacon(glacon.x, glacon.y);

        enleveCaseGlace(jeu->banquise, jeu->glacons[i]->position.x, jeu->glacons[i]->position.y, GLACON);
    }
}



//S'occupe du deplacement du glacon apres que celui-ci se soit fait pousser par un joueur
void joueurPousseGlacon(T_joueur *joueur, T_glacon *glacon, T_jeu *jeu)
{
    int Jdx = joueur->vecteur.dx, Jdy = joueur->vecteur.dy;  //Enregistre le vecteur du joueur
    glacon->vecteur.dx = Jdx, glacon->vecteur.dy = Jdy;      //Transfert le vecteur du joueur au glacon
    int Gdx = glacon->vecteur.dx, Gdy = glacon->vecteur.dy;
    int verifDep, stop = 0;
    while(stop == 0)
    {
        verifDep = deplacementGlacon(glacon, jeu->banquise, jeu->joueurs, jeu->nombreJoueur);
        Sleep(200);
        Gdx = glacon->vecteur.dx, Gdy = glacon->vecteur.dy;

        if(Gdx == 0 && Gdy == 0)
            stop = 1;

        switch(verifDep)
        {
            case 2 :
                ajouteCaseGlace(jeu->banquise, glacon->position.x, glacon->position.y);
                free(glacon);
                break;
            default :
                enleveCaseGlace(jeu->banquise, glacon->position.x, glacon->position.y, GLACON);
                system("cls");
                printf("Tour %d\n", jeu->nombreTour);
                afficheJeu(jeu);
        }
    }
}

