#include "jeux.h"



//Affiche le Menu du jeu
void afficheMenu(T_booleen debut)
{
    char entree;                                        //Stocke un caractere

    if (debut)
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
               "Appuyer sur entree pour continuer");        //Affiche le Menu

        entree = getchar();                                 //Attend que la touche entree soit pressee

        system("cls");                                      //Nettoie l'ecran

        printf("Regles du jeux\n"
               "\n"
               "Votre but est de rejoindre la case "
               "d'arrive en evitant tous les obstacles\n"
               "\n"
               "Attention, les glacons se deplacent et "
               "peuvent vous tuer s'ils vous touchent\n"
               "\n"
               "Appuyer sur entree pour continuer");        //Affiche les regles du jeu

    }

    entree = getchar();                                 //Attend que la touche entree soit pressee

    system("cls");                                      //Nettoie l'ecran

    printf("Touches a utiliser :\n"
           "\n"
           "Pour se deplacer, utiliser les "
           "touches du clavier suivante :\n"
           "Z : haut\n"
           "Q : gauche\n"
           "S : bas\n"
           "D : droite\n"
           "\n"
           "Pour d'autres actions, utiliser les "
           "touches du clavier suivante :\n"
           "P : passer son tour\n"
           "V : verifier si le joueur peut rejoindre l'arrive\n"
           "M : afficher le menu\n"
           "F : finir la partie\n"
           "\n"
           "\n"
           "Signifiaction des cases :\n"
           "\n");

    changeCouleurConsole(BLANC);
    printf("%d ", GLACE);
    changeCouleurConsole(DEFAULT);
    printf(" : glace\n");

    changeCouleurConsole(NOIR);
    printf("%d ", DEPART);
    changeCouleurConsole(DEFAULT);
    printf(" : depart\n");

    changeCouleurConsole(ROSE);
    printf("%d ", ARRIVE);
    changeCouleurConsole(DEFAULT);
    printf(" : arrive\n");

    changeCouleurConsole(TURQUOISE);
    printf("%d ", GLACON);
    changeCouleurConsole(DEFAULT);
    printf(" : glacon\n");

    changeCouleurConsole(BLEUFONCE);
    printf("%d ", EAU);
    changeCouleurConsole(DEFAULT);
    printf(" : eau\n");

    changeCouleurConsole(GRIS);
    printf("%d ", ROCHER);
    changeCouleurConsole(DEFAULT);
    printf(" : rocher\n");

    changeCouleurConsole(MARRON);
    printf("%d ", RESSORT);
    changeCouleurConsole(DEFAULT);
    printf(" : ressort\n");

    changeCouleurConsole(KAKI);
    printf("%d ", MARTEAU_TETE);
    changeCouleurConsole(DEFAULT);
    printf(" : tete du marteau\n");

    changeCouleurConsole(NOIR);
    printf("%d ", MARTEAU_CENTRE);
    changeCouleurConsole(DEFAULT);
    printf(" : centre du marteau\n\n");

    if (debut)
    {
        printf("Appuyer sur entree pour commencer le jeu");
    }
    else
    {
        printf("Appuyer sur entree pour continuer le jeu");
    }

    entree = getchar();                                 //Attend que la touche entree soit pressee

    (void)entree;

    system("cls");                                      //Nettoie l'ecran
}



//Change la couleur du texte selon la type couleur mis en parametre
void changeCouleurConsole(T_couleur couleur)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); //Declare la console windows du jeu

    switch (couleur)                                  //Change la couleur du texte de la console selon le type couleur mis en parametre
    {
    case ROUGE:
        SetConsoleTextAttribute(console, 12*16+12);
        break;
    case VERT :
        SetConsoleTextAttribute(console, 2*16+2);
        break;
    case BLEU:
        SetConsoleTextAttribute(console, 9*16+9);
        break;
    case JAUNE :
        SetConsoleTextAttribute(console, 14*16+14);
        break;
    case TURQUOISE :
        SetConsoleTextAttribute(console, 11*16+11);
        break;
    case ROSE :
        SetConsoleTextAttribute(console, 13*16+13);
        break;
    case GRIS :
        SetConsoleTextAttribute(console, 8*16+8);
        break;
    case BLEUFONCE :
        SetConsoleTextAttribute(console, 1*16+1);
        break;
    case NOIR :
        SetConsoleTextAttribute(console, 0);
        break;
    case MARRON :
        SetConsoleTextAttribute(console, 4*16+4);
        break;
    case KAKI :
        SetConsoleTextAttribute(console, 6*16+6);
        break;
    case BLANC :
        SetConsoleTextAttribute(console, 15*16+15);
        break;
    default :
        SetConsoleTextAttribute(console, 15);
    }
}



//Fonction qui retourne un entier en fonction de la couleur du joueur
void changeCouleurTexte(T_couleur couleur)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); //Declare la console windows du jeu

    switch (couleur)
    {
    case ROUGE :
        SetConsoleTextAttribute(console, 12);
        break;
    case VERT :
        SetConsoleTextAttribute(console, 2);
        break;
    case BLEU :
        SetConsoleTextAttribute(console, 9);
        break;
    case JAUNE :
        SetConsoleTextAttribute(console, 14);
        break;
    default :
        SetConsoleTextAttribute(console, 15);
    }
}



//
T_booleen **tabChemin(int taille)
{
    T_booleen **tab = (T_booleen **)initMatrice(taille);
    int i, j;

    for (i = 0; i < taille; i++)
    {
        for (j = 0; j < taille; j++)
        {
            tab[i][j] = VRAI;
        }
    }

    return tab;
}



//
T_booleen verifieChemin(T_jeu *jeu, T_booleen **tab, int caseX, int caseY, T_booleen affichage)
{
    int taille = jeu->banquise->tailleN;

    if (caseX < 0 || caseX >= taille
        || caseY < 0 || caseY >= taille)
    {
        return FAUX;
    }

    T_case caseValeur = jeu->banquise->matrice[caseX][caseY];
    T_booleen tabValeur = tab[caseX][caseY];

    if (caseValeur == ARRIVE)
    {
        return VRAI;
    }

    if ((caseValeur != GLACE
        && caseValeur != JOUEUR
        && caseValeur != GLACON)
        || !tabValeur)
    {
        return FAUX;
    }

    tab[caseX][caseY] = FAUX;

    if (affichage)
    {
        jeu->banquise->matrice[caseX][caseY] = DEPART;
        afficheJeu(jeu);
        Sleep(20);
        jeu->banquise->matrice[caseX][caseY] = caseValeur;
    }

    if (verifieChemin(jeu, tab, caseX, caseY + 1, affichage)
        ||verifieChemin(jeu, tab, caseX - 1, caseY, affichage)
        || verifieChemin(jeu, tab, caseX + 1, caseY, affichage)
        || verifieChemin(jeu, tab, caseX, caseY - 1, affichage))
    {
        return VRAI;
    }

    return FAUX;
}



//
T_booleen verifieCheminJoueurs(T_jeu *jeu, T_booleen **tab, T_booleen affichage)
{
    T_booleen cheminExiste;
    int i;

    for (i = 0; i < jeu->nombreJoueurs; i++)
    {
        T_booleen **tab = tabChemin(jeu->banquise->tailleN);

        if (!verifieChemin(jeu, tab, jeu->joueurs[i]->position.x, jeu->joueurs[i]->position.y, affichage))
        {
            cheminExiste = FAUX;
            break;
        }

        cheminExiste = VRAI;

        free(tab);
    }

    return cheminExiste;
}



//Retourne un pointeur de type jeu en fonction du niveau et de la taille de la banquise
T_jeu *initJeux(int niveau, int tailleN, int tailleEau, int nombreGlacons, int nombreMarteaux, int nombreRessorts, int nombreRochers, int chanceFonte, int chancePiege)
{
    T_jeu *jeu = (T_jeu *)malloc(sizeof(T_jeu));                               //Aloue de l'espace memoire a un pointeur de type jeu

    int nombreJoueurs = demandeNombreJoueurs();                                //Recupere le nombre de joueurs saisi par l'utilisateur

    jeu->banquise = initBanquise(tailleN, tailleEau);                          //Initialise la banquise dans le jeu
    jeu->joueurs = initTabJoueurs(jeu->banquise, nombreJoueurs);               //Initialise le tableau de joueurs
    jeu->glacons = initTabGlacons(jeu->banquise, nombreGlacons, chanceFonte);  //Initialise le tableau de glacons
    jeu->marteaux = initTabMarteaux(jeu->banquise, nombreMarteaux);            //Initialise le tableau de marteaux
    jeu->ressorts = initTabRessorts(jeu->banquise, nombreRessorts);            //Initialise le tableau de ressorts
    jeu->rochers = initTabRochers(jeu->banquise, nombreRochers);               //Initialise le tableau de rochers
    jeu->nombreJoueurs = nombreJoueurs;                                        //Initialise le nombre de joueurs
    jeu->nombreGlacons = nombreGlacons;                                        //Initialise le nombre de glacons
    jeu->nombreMarteaux = nombreMarteaux;                                      //Initialise le nombre de marteaux
    jeu->nombreRessorts = nombreRessorts;                                      //Initialise le nombre de ressorts
    jeu->nombreRochers = nombreRochers;                                        //Initialise le nombre de rochers
    jeu->nombreTour = 0;                                                       //Initialise le nombre de tour
    jeu->rechauffement = chanceFonte;                                          //Initialise la probabilite de chance de fonte
    jeu->probPiege = chancePiege;                                              //Initialise la probabilite de chance d'etre piege
    jeu->IdJeu = niveau;                                                       //Initialise le niveau

    return jeu;                                                                //Retourne le pointeur de type jeu
}



//Retourne un pointeur de type jeu en fonction du niveau et de la taille de la banquise
void reInitJeux(T_jeu *jeu)
{
    free(jeu->banquise);
    free(jeu->glacons);
    free(jeu->marteaux);
    free(jeu->ressorts);
    free(jeu->rochers);

    int i;

    jeu->banquise = initBanquise(jeu->banquise->tailleN, jeu->banquise->tailleEau);       //Re Initialise la banquise dans le jeu
    for (i = 0; i < jeu->nombreJoueurs; i++)
    {
        departJoueur(jeu->banquise, jeu->joueurs[i]);                                     //Met le joueur a sa case depart
    }
    jeu->glacons = initTabGlacons(jeu->banquise, jeu->nombreGlacons, jeu->rechauffement); //Re Initialise le tableau de glacons
    jeu->marteaux = initTabMarteaux(jeu->banquise, jeu->nombreMarteaux);                  //Re Initialise le tableau de marteaux
    jeu->ressorts = initTabRessorts(jeu->banquise, jeu->nombreRessorts);                  //Re Initialise le tableau de ressorts
    jeu->rochers = initTabRochers(jeu->banquise, jeu->nombreRochers);                     //Re Initialise le tableau de rochers
}



//
T_jeu *initJeuxPersonalise()
{
    T_jeu *jeu;
    int taille = 0;

    while (taille < 1)
    {
        printf("Nombre de cases de la banquise par ligne/colonne (doit etre positif) : ");
        scanf("%d", &taille);
        system("cls");
    }

    int nombreCasesDispo = taille * taille,
        tailleEauMax = (taille - 4) / 2,
        tailleEau = -1;

    while (tailleEau < 0 || tailleEau > tailleEauMax)
    {
        printf("Nombre de cases d'eau par ligne/colonne entourant "
               "la banquise (ne doit pas depasser %d) : ", tailleEauMax);
        scanf("%d", &tailleEau);
        system("cls");
    }

    nombreCasesDispo = (taille - (tailleEau * 2)) * (taille - (tailleEau * 2));

    int nombreGlacons = -1;

    while (nombreGlacons < 0 || nombreGlacons > nombreCasesDispo)
    {
        printf("Nombre de glacons dans le jeu "
               "(ne doit pas depasser %d) : ", nombreCasesDispo);
        scanf("%d", &nombreGlacons);
        system("cls");
    }

    nombreCasesDispo -= nombreGlacons;

    int nombreMarteaux = -1;

    while (nombreMarteaux < 0 || nombreMarteaux > nombreCasesDispo)
    {
        printf("Nombre de marteaux dans le jeu "
               "(ne doit pas depasser %d) : ", nombreCasesDispo / 2);
        scanf("%d", &nombreMarteaux);
        system("cls");
    }

    nombreCasesDispo -= 2 * nombreMarteaux;

    int nombreRessorts = -1;

    while (nombreRessorts < 0 || nombreRessorts > nombreCasesDispo)
    {
        printf("Nombre de ressorts dans le jeu "
               "(ne doit pas depasser %d) : ", nombreCasesDispo);
        scanf("%d", &nombreRessorts);
        system("cls");
    }

    nombreCasesDispo -= nombreRessorts;

    int nombreRochers = -1;

    while (nombreRochers < 0 || nombreRochers > nombreCasesDispo)
    {
        printf("Nombre de rochers dans le jeu "
               "(ne doit pas depasser %d) : ", nombreCasesDispo);
        scanf("%d", &nombreRochers);
        system("cls");
    }

    nombreCasesDispo -= nombreRochers;

    int chanceFonte = 0;

    while (chanceFonte < 1)
    {
        printf("Nombres de tours ou il y a une chance de fonte (positif) : ");
        scanf("%d", &chanceFonte);
        system("cls");
    }

    int chancePiege = 0;

    while (chancePiege < 1)
    {
        printf("Nombres de tours ou il y a une chance de tomber dans un piege (positif) : ");
        scanf("%d", &chancePiege);
        system("cls");
    }

    jeu = initJeux(4, taille, tailleEau, nombreGlacons, nombreMarteaux, nombreRessorts, nombreRochers, chanceFonte, chancePiege);

    return jeu;
}



//
T_jeu *initNiveau()
{
    T_jeu *jeu;
    int niveau = 0;

    while (niveau < 1 || niveau > 4)
    {
        printf("Choix du niveau :\n"
               "\n"
               "1 : Facile\n"
               "2 : Moyen\n"
               "3 : Difficile\n"
               "4 : Personnalise\n");
        scanf("%d", &niveau);
        system("cls");
    }

    switch (niveau)
    {
    case 1 :
        jeu = initJeux(1, 10, 1, 5, 1, 2, 5, 10, 20);
        break;
    case 2 :
        jeu = initJeux(2, 15, 2, 20, 2, 5, 10, 5, 10);
        break;
    case 3 :
        jeu = initJeux(3, 25, 3, 50, 5, 20, 50, 2, 5);
        break;
    default :
        jeu = initJeuxPersonalise();
    }

    return jeu;
}



//Affiche le jeu
void afficheJeu(T_jeu *jeu)
{
    int taille = jeu->banquise->tailleN;                                                         //Recupere la taille de la banquise
    int i, j;                                                                                    //Declare deux entiers pour les boucles for

    system("cls");                                                                               //Efface le terminal
    printf("Tour %d\n", jeu->nombreTour);                                                        //Affiche le nombre de tour

    for (i = 0; i < taille; i++)                                                                 //Boucle qui parcourt les lignes de la matrice
    {
        for (j = 0; j < taille; j++)                                                             //Boucle qui parcourt les collones de la matrice
        {
            int pos = jeu->banquise->matrice[i][j];                                              //Declare la position parcouru

            switch (pos)                                                                         //Affiche la case en couleur selon le type de la case
            {
            case JOUEUR :
                {
                T_joueur *joueur = joueurSelonPosition(jeu->joueurs, i, j, jeu->nombreJoueurs);   //Recupere le joueur a la position parcouru par la boucle

                changeCouleurConsole(joueur->couleur);                                             //Change la couleur selon celle du joueur
                break;
                }
            case ARRIVE :
                changeCouleurConsole(ROSE);                                                        //Change la couleur en rose pour l'arrive
                break;
            case EAU :
                changeCouleurConsole(BLEUFONCE);                                                   //Change la couleur en turquoise pour l'eau
                break;
            case GLACON :
                changeCouleurConsole(TURQUOISE);                                                   //Change la couleur en bleu-gris pour le glacon
                break;
            case GLACE :
                changeCouleurConsole(BLANC);                                                       //Change la couleur en blanc sinon
                break;
            case MARTEAU_TETE :
                changeCouleurConsole(KAKI);
                break;
            case RESSORT :
                changeCouleurConsole(MARRON);                                                      //Change la couleur en marron pour le ressort
                break;
            case ROCHER :
                changeCouleurConsole(GRIS);                                                        //Change la couleur en gris pout le rocher
                break;
            default :
                changeCouleurConsole(NOIR);                                                        //Change la couleur en noir pour le depart
            }

            printf("%d ", pos);                                                                    //Affiche la case

            changeCouleurConsole(DEFAULT);                                                         //Re-met la couleur en blanc
        }
        printf("\n");                                                                              //Saute une ligne
    }
}



//Retourne une lettre du clavier qui correspond a un deplacement
char saisieTouche(T_joueur *joueur, T_booleen bug)
{
    char clavier;

    if (bug)
    {
     clavier = getchar();
    }

    changeCouleurTexte(joueur->couleur);                                                     //Change la couleur selon la couleur choisi par le joueur
    printf("%s", joueur->nom);                                                               //Affiche le nom du joueur choisi
    changeCouleurTexte(BLANC);                                                               //Remet la couleur blanche
    printf(" deplacez vous : ");                                                             //Demande au joueur ou il veut se deplacer
    scanf("%c", &clavier);

    while (clavier != 'z'
           && clavier != 'q'
           && clavier != 's'
           && clavier != 'd'
           && clavier != 'p'
           && clavier != 'v'
           && clavier != 'm'
           && clavier != 'f'
           && clavier != 'Z'
           && clavier != 'Q'
           && clavier != 'S'
           && clavier != 'D'
           && clavier != 'P'
           && clavier != 'V'
           && clavier != 'M'
           && clavier != 'F')                                                               //Boucle qui fini quand l'utilisateur a rentree une bonne touche
    {
        clavier = getchar();
        printf("\r\nTouche incorrect, veuillez saisir une touche "
               "entre \"z, q, s, d, p, v, m, f\" : ");                                      //Re-demande le deplacement en rappellant les bonnes touches
        scanf("%c", &clavier);
    }

    return clavier;                                                                          //Retourne la bonne touche
}



//S'occupe du deplacement du glacon apres que celui-ci se soit fait pousser par un joueur
void joueurPousseGlacon(T_joueur *joueur, T_glacon *glacon, T_jeu *jeu)
{
    int Jdx = joueur->vecteur.dx, Jdy = joueur->vecteur.dy,                                                                                         //Enregistre le vecteur du joueur                                                                                            //Transfert le vecteur du joueur au glacon
        Gdx = glacon->vecteur.dx = Jdx, Gdy = glacon->vecteur.dy = Jdy,                                                                             //Initialise le vecteur du glacon selon celui du joueur
        verifDep,                                                                                                                                   //Variable pour verifier le deplacement
        stop = 0;                                                                                                                                   //Variable d'arret pour la boucle while

    while(stop == 0)                                                                                                                                //Tant qu'on decide de continuer
    {
        verifDep = verifieDeplacementGlacon(glacon, jeu->banquise, jeu->joueurs, jeu->nombreJoueurs);                                                       //Effectue le deplacement et stocke le resultat dans une variable
        Sleep(200);                                                                                                                                 //Attend 0,2s pour que le joueur voit le glacon se deplacer
        Gdx = glacon->vecteur.dx, Gdy = glacon->vecteur.dy;                                                                                         //Recupere les nouveaux vecteurs du glacon

        if(Gdx == 0 && Gdy == 0)                                                                                                                    //Verifie si le glacon bouge encore
        {
            stop = 1;                                                                                                                               //Arrete la boucle
        }

        switch(verifDep)                                                                                                                            //Regarde la valeur de retour apres le deplacement
        {
        case 1 :
        {
            T_glacon *nouveauGlacon = glaconSelonPosition(jeu->glacons, (glacon->position.x + Gdx), (glacon->position.y + Gdy), jeu->nombreGlacons); //Initialise un nouveau glacon qui correspond au glacon touche par le glacon en mouvement

            joueur->vecteur.dx = glacon->vecteur.dx, joueur->vecteur.dy = glacon->vecteur.dy;
            glacon->vecteur.dx = glacon->vecteur.dy = 0;                                                                                            //Arrete le glacon qui a touche le nouveau gl
            enleveCaseGlace(jeu->banquise, glacon->position.x, glacon->position.y, GLACON);                                                         //Met le glacon a sa nouvelle position
            joueurPousseGlacon(joueur, nouveauGlacon, jeu);                                                                                         //Rappelle la fonction pour faire deplacer le nouveau glacon
            break;
        }
        case 2 :
            ajouteCaseGlace(jeu->banquise, glacon->position.x, glacon->position.y);                                                                 //Transforme le glacon tombe dans l'eau en glace
            break;
        case 3 :
        {
            T_marteau *marteau = marteauSelonPosition(jeu->marteaux, (glacon->position.x + Gdx), (glacon->position.y + Gdy), jeu->nombreMarteaux);  //Initialise un nouveau marteau qui correspond au marteau que touche le glaçon
            T_booleen sensRotation = marteauSensRotation(marteau, glacon);

            enleveCaseGlace(jeu->banquise, glacon->position.x, glacon->position.y, GLACON);                                                         //Met le glacon a sa nouvelle position

            if (sensRotation != ECHEC)
            {
                bougeTeteMarteau(jeu, marteau, sensRotation);
            }
        }
        default :
            enleveCaseGlace(jeu->banquise, glacon->position.x, glacon->position.y, GLACON);                                                         //Met le glacon a sa nouvelle position
            afficheJeu(jeu);                                                                                                                        //Affiche le jeu
        }
    }
}



//Fonction qui fait fondre ou non un glaçon à chaque tour
void fonteGlacon(T_jeu *jeu)
{
    if (jeu->nombreGlacons != 0)
    {
        T_glacon *glacon = jeu->glacons[jeu->nombreGlacons - 1];

        if(verifFonteGlacon(glacon) == 1)
        {
            if (jeu->banquise->matrice[glacon->position.x][glacon->position.y] != GLACE)
            {
                ajouteCaseGlace(jeu->banquise, glacon->position.x, glacon->position.y);
            }
            jeu->nombreGlacons -= 1;
            free(glacon);
        }
    }
}



//
void bougeTeteMarteau(T_jeu *jeu, T_marteau *marteau, T_booleen sensHorraire)
{
    int nombreDeplacements = 0;

    marteau->mouvement = VRAI;

    while (marteau->mouvement == VRAI)
    {
        if (nombreDeplacements == 8)
        {
            marteau->mouvement = FAUX;
        }
        else
        {
            mouvementTete(jeu->banquise, marteau, sensHorraire);
            Sleep(500);
            afficheJeu(jeu);
        }

        nombreDeplacements++;
    }

    if (nombreDeplacements != 8)
    {
        T_joueur *joueur = jeu->joueurs[0];
        T_glacon *glacon = glaconSelonPosition(jeu->glacons,
                                               marteau->tete.position.x + marteau->tete.vecteur.dx,
                                               marteau->tete.position.y + marteau->tete.vecteur.dy,
                                               jeu->nombreGlacons);
        joueur->vecteur = marteau->tete.vecteur;

        joueurPousseGlacon(joueur, glacon, jeu);
    }
}




//Fonction qui s'occupe d'effectuer le tour d'un joueur dont l'identifiant est donne en parametre
int tourJoueur(T_jeu *jeu, int numJoueur, T_booleen bugToucheEntree)
{
    T_joueur *joueur = jeu->joueurs[numJoueur];                                              //Recupere le joueur dont l'identifiant est donne en parametre
    int **matrice = jeu->banquise->matrice;                                                  //Recupere la matrice represantant le jeu
    int caseValeur = ERREUR,                                                                 //Variable pour la valeur de la case ou le joueur est allee
        verifDep,                                                                            //Variable pour verifier le deplacement du joueur
        i;                                                                                   //Varibales pour la boucle suivante

    afficheJeu(jeu);                                                                         //Affiche la banquise dans le terminal

    if (joueur->etat == PIEGE)
    {
        changeCouleurTexte(joueur->couleur);
        printf("%s ", joueur->nom);
        changeCouleurTexte(BLANC);
        printf("vous passez votre tour");
        Sleep(2000);
        joueur->etat = ENCOURS;
    }
    else
    {
        char toucheSaise = saisieTouche(joueur, bugToucheEntree);

        switch (toucheSaise)
        {
        case 'p' :
        case 'P' :
            changeCouleurTexte(joueur->couleur);
            printf("%s ", joueur->nom);
            changeCouleurTexte(BLANC);
            printf("a decide de passer son tour");
            Sleep(2000);
            break;
        case 'v' :
        case 'V' :
            {
                T_booleen **tabTemp = tabChemin(jeu->banquise->tailleN);

                if (verifieChemin(jeu, tabTemp, joueur->position.x, joueur->position.y, VRAI))
                {
                    printf("\nIl y a un chemin possible");
                    Sleep(2000);
                    free(tabTemp);
                    tourJoueur(jeu, numJoueur, VRAI);
                }
                else
                {
                    printf("\nIl n'y a pas de chemin possible");
                    free(tabTemp);
                    return ARRIVE;
                }
                break;
            }
        case 'm' :
        case 'M' :
            afficheMenu(FAUX);
            tourJoueur(jeu, numJoueur, FAUX);
            break;
        case 'f' :
        case 'F' :
            {
                char clavier;

                while (clavier != 'o' && clavier != 'n')
                {
                    clavier = getchar();
                    printf("\nEtes vous sur de finir la partie, "
                           "si oui tapez 'o', sinon 'n' : ");
                    scanf("%c", &clavier);
                }

                if (clavier == 'o')
                {
                    return ABANDON;
                }
                else
                {
                    tourJoueur(jeu, numJoueur, VRAI);
                }
            }
        default :
            ajouteCaseGlace(jeu->banquise, joueur->position.x, joueur->position.y);                  //Met une glace sur la case que le joueur va quitter
            verifDep = deplacementJoueur(jeu->banquise, joueur, toucheSaise);                        //Effectue le deplacement du joueur sur la banquise
            caseValeur = matrice[joueur->position.x][joueur->position.y];                            //Regarde la valeur de la case ou le joueur est
            enleveCaseGlace(jeu->banquise, joueur->position.x, joueur->position.y, JOUEUR);          //Remplace la case glace ou le joueur est alle

            if (joueurEstPiege(joueur, jeu->probPiege) == PIEGE)
            {
                system("cls");
                afficheJeu(jeu);
                changeCouleurTexte(joueur->couleur);
                printf("%s ", joueur->nom);
                changeCouleurTexte(BLANC);
                printf("est tombe dans un piege, il ne jouera pas a son prochain tour");
                Sleep(2000);
            }

            if(verifDep == GLACON)                                                                   //Verifie si le joueur touche un glacon
            {
                for(i = 0; i < jeu->nombreGlacons; i++)                                               //Parcourt le tableaux de glacons
                {
                    if((joueur->position.x + joueur->vecteur.dx) == jeu->glacons[i]->position.x
                        && (joueur->position.y + joueur->vecteur.dy) == jeu->glacons[i]->position.y)  //Condition qui regarde quel glacon a touche le joueur en parametre
                    {
                        joueurPousseGlacon(jeu->joueurs[numJoueur], jeu->glacons[i], jeu);           //Effectue le deplacement du glacon
                        break;                                                                       //Sort de la boucle
                    }
                }
            }
        }
    }

    return caseValeur;                                                                       //Retourne la valeur de la case
}



//Ressort un entier qui determine si la partie est finie ou non
int victoire(T_jeu *jeu, int caseVal, int i)
{
    if (caseVal == ARRIVE)                                                         //Verifie si la case est celle d'arrive
    {
        jeu->joueurs[i]->etat = GAGNANT;                                           //Change l'etat de ce joueur pour le designer en tant que gagnant
        printf("\nLa partie est finie ! ");                                          //Affiche le joueur victorieux
        changeCouleurTexte(jeu->joueurs[i]->couleur);
        printf("%s", jeu->joueurs[i]->nom);
        changeCouleurTexte(BLANC);
        printf(" est victorieux !");
        jeu->joueurs[i]->score += 1000;                                            //Le gagnant recois 1000 point
        Sleep(3000);                                                               //Attend 3s avant de passer à l'instruction suivante
        return 1;                                                                  //Retourne l'entier 1 pour signaler une victoire
    }
    else if (caseVal == ABANDON)
    {
        printf("\nLa partie a ete interrompu par ");
        changeCouleurTexte(jeu->joueurs[i]->couleur);
        printf("%s", jeu->joueurs[i]->nom);
        changeCouleurTexte(BLANC);
        printf(" personne n'a gagne");
        Sleep(3000);                                                               //Attend 3s avant de passer à l'instruction suivante
        return 1;
    }
    else                                                                           //Si la case n'est pas celle d'arrive
    {
        return 0;                                                                  //Retourne l'entier 0 pour signaler que la partie continue
    }
}



//Affiche le scrore à la fin de la partie
void afficheScore(T_jeu *jeu)
{
    int i;                                                   //Variable pour la boucle suivante

    for(i = 0; i < jeu->nombreJoueurs; i++)                  //Boucle qui parcourt le tableau de joueurs
    {
        system("cls");                                       //Efface le terminal
        printf("->Joueur %d\n", (i + 1));                    //Affiche infos sur le joueur quand la partie est finie
        printf("    Nom : ");
        changeCouleurTexte(jeu->joueurs[i]->couleur);
        printf("%s\n", jeu->joueurs[i]->nom);
        changeCouleurTexte(BLANC);
        printf("    Mort : %d\n", jeu->joueurs[i]->nbMort);
        printf("    Score : %d\n", jeu->joueurs[i]->score);

        if (jeu->joueurs[i]->etat == GAGNANT)                //Permet de savoir si le joueur est gagnant ou perdant
        {
            printf("    Etat : GAGNANT\n");
        }
        else
        {
            printf("    Etat : PERDANT\n");
        }
        printf("\n");
        Sleep(3000);                                         //Attend 3 secondes
    }
}



//Fonction qui joue un niveau selectionne jusqu'à la victoire d'un joueur
void joueNiveau(T_jeu *jeu)
{
    int caseVal, finPartie = 0,                                //caseVal sert à connaitre la valeur de la case, et finPartie sert à mettre fin à la partie en cours
        i, j,                                                  //Varibales pour les boucles suivante
        taille = jeu->banquise->tailleN;

    T_booleen **tabTemp = tabChemin(taille);

    while (!verifieCheminJoueurs(jeu, tabTemp, FAUX))
    {
        for (i = 0; i < taille; i++)
        {
            for (j = 0; j < taille; j++)
            {
                tabTemp[i][j] = VRAI;
            }
        }
        reInitJeux(jeu);
    }

    free(tabTemp);

    jeu->nombreTour = 1;                                       //Initialise le nombre de tour a 1

    while(finPartie == 0)                                      //Boucle tant que la partie n'est pas finie, c'est a dire tant qu'un joueur n'a pas atteint la case d'arrive
    {
        for(i = 0; i < jeu->nombreJoueurs; i++)                 //Boucle for qui permet à chaque joueur de jouer pour un tour
        {
            caseVal = tourJoueur(jeu, i, VRAI);                //Tour du joueur i
            finPartie = victoire(jeu, caseVal, i);             //Donne un entier si la partie est gagnee, ou si elle continue

            if (caseVal == ARRIVE || caseVal == ABANDON)       //Permet de reellement stopper le jeu, pour ainsi eviter les joueurs suivant de jouer
            {
                break;                                         //Brise la boucle for
            }

            fonteBanquise(jeu->banquise, jeu->rechauffement);  //Applique le rechauffement climatique sur la banquise
            fonteGlacon(jeu);                                  //
        }
        jeu->nombreTour += 1;                                  //Incremente le nombre de tour
    }
    afficheScore(jeu);                                         //Affiche le score du jeu
    //Sleep(5000);                                               //Donne 5s au joueur pour lire les scores
    system("cls");                                             //Netoie la console
    printf("Merci d'avoir joue !\n");                          //Affiche remerciement
}



//Fonction qui renvoie un entier qui permet de rejouer une partie
int rejouer()
{
    char c = getchar();                                                            //Enregistre la valeur saisie par l'utilisateur

    printf("\nVoulez vous rejouer ? (Tapez \"o\" pour oui ou \"n\" pour non) : "); //Demande au joueur s'il veut relancer une partie

    c = getchar();

    while (c != 'n' && c != 'o')                                                   //Boucle tant que le joueur ne saisit pas les bons caractere
    {
        c = getchar();
        printf("\nChoix inconnue ! Veuillez reessayer : ");                        //Previens le joueur qu'il a saisie un mauvais caractere
        scanf("%c", &c);
    }

    if (c == 'o')                                                                  //Si le caractere est y
    {
        return 0;                                                                  //Retourne valeur de succes
    }
    else                                                                           //Si le caractere est n
    {
        return 1;                                                                  //Retourne valeur d'echec
    }
}



//
void joue()
{
    int stop;                                          //Varibale pour stoper le jeu

    afficheMenu(VRAI);                                 //Affiche le menu du jeu

    while(stop == 0)                                   //Boucle tant que le jeu n'est pas stope
    {
        stop = 0;                                      //Permet d'eviter un bug lorsqu'on relance une partie et qu'elle se finie

        system("cls");                                 //Nettoie la console

        T_jeu *jeu = initNiveau();

        joueNiveau(jeu);                             //Joue le niveau selectionne

        free(jeu);                                   //Libere l'espace prit par le niveau 1

        stop = rejouer();                              //Regarde si l'on doit stoper le jeu
    }
}
