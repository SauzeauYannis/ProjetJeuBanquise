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
           "Appuyer sur entree pour continuer");        //Affiche le Menu

    char entree;                                        //Stocke un caractere
    entree = getchar();                                 //Attend que la touche entree soit pressee

    system("cls");                                      //Nettoie l'ecran

    printf("Regles du jeux\n"
           "\n"
           "A venir\n"
           "\n"
           "Appuyer sur entree pour continuer");        //Affiche les regles du jeu

    entree = getchar();                                 //Attend que la touche entree soit pressee

    system("cls");                                      //Nettoie l'ecran

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

    entree = getchar();                                 //Attend que la touche entree soit pressee

    system("cls");                                      //Nettoie l'ecran
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
    case NOIR :
        SetConsoleTextAttribute(console, 0);
        break;
    case MARRON :
        SetConsoleTextAttribute(console, 4);
        break;
    default :
        SetConsoleTextAttribute(console, 15);
    }
}



//Retourne un pointeur de type jeu en fonction du niveau et de la taille de la banquise
T_jeu *initJeux(int niveau, int tailleN, int tailleEau, int nombreGlacons, int nombreRochers, int nombreRessorts, int chanceFonte, int chancePiege)
{
    T_jeu *jeu = (T_jeu *)malloc(sizeof(T_jeu));                               //Aloue de l'espace memoire a un pointeur de type jeu

    int nombreJoueurs = demandeNombreJoueurs();                                //Recupere le nombre de joueurs saisi par l'utilisateur

    jeu->banquise = initBanquise(tailleN, tailleEau);                          //Initialise la banquise dans le jeu
    jeu->joueurs = initTabJoueurs(jeu->banquise, nombreJoueurs);               //Initialise le tableau de joueurs
    jeu->glacons = initTabGlacons(jeu->banquise, nombreGlacons, chanceFonte);  //Initialise le tableau de glacons
    jeu->rochers = initTabRochers(jeu->banquise, nombreRochers);               //Initialise le tableau de rochers
    jeu->ressorts = initTabRessorts(jeu->banquise, nombreRessorts);            //Initialise le tableau de ressorts
    jeu->nombreJoueurs = nombreJoueurs;                                        //Initialise le nombre de joueurs
    jeu->nombreGlacons = nombreGlacons;                                        //Initialise le nombre de glacons
    jeu->nombreRochers = nombreRochers;                                        //Initialise le nombre de rochers
    jeu->nombreRessorts = nombreRessorts;                                      //Initialise le nombre de ressorts
    jeu->nombreTour = 0;                                                       //Initialise le nombre de tour
    jeu->rechauffement = chanceFonte;                                          //Initialise la probabilite de chance de fonte
    jeu->probPiege = chancePiege;                                              //Initialise la probabilite de chance d'etre piege
    jeu->IdJeu = niveau;                                                       //Initialise le niveau

    return jeu;                                                                //Retourne le pointeur de type jeu
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
        printf("| ");                                                                            //Esthetique
        for (j = 0; j < taille; j++)                                                             //Boucle qui parcourt les collones de la matrice
        {
            int pos = jeu->banquise->matrice[i][j];                                              //Declare la position parcouru

            switch (pos)                                                                         //Affiche la case en couleur selon le type de la case
            {
            case JOUEUR :
                {
                T_joueur *joueur = joueurSelonPosition(jeu->joueurs, i, j, jeu->nombreJoueurs);  //Recupere le joueur a la position parcouru par la boucle

                changeCouleurTexte(joueur->couleur);                                             //Change la couleur selon celle du joueur
                break;
                }
            case DEPART :
                changeCouleurTexte(NOIR);                                                        //Change la couleur en noir pour le depart
                break;
            case ARRIVE :
                changeCouleurTexte(ROSE);                                                        //Change la couleur en rose pour l'arrive
                break;
            case GLACON :
                changeCouleurTexte(BLEUFONCE);                                                   //Change la couleur en bleu-gris pour le glacon
                break;
            case EAU :
                changeCouleurTexte(TURQUOISE);                                                   //Change la couleur en turquoise pour l'eau
                break;
            case ROCHER :
                changeCouleurTexte(GRIS);                                                        //Change la couleur en gris pout le rocher
                break;
            case RESSORT :
                changeCouleurTexte(MARRON);                                                      //Change la couleur en marron pour le ressort
                break;
            default :
                changeCouleurTexte(BLANC);                                                       //Change la couleur en blanc sinon
            }

            printf("%d ", pos);                                                                  //Affiche la case

            changeCouleurTexte(BLANC);                                                           //Re-met la couleur en blanc
        }
        printf("|\n");                                                                           //Esthetique
    }
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

            glacon->vecteur.dx = glacon->vecteur.dy = 0;                                                                                            //Arrete le glacon qui a touche le nouveau glacon
            enleveCaseGlace(jeu->banquise, glacon->position.x, glacon->position.y, GLACON);                                                         //Met le glacon a sa nouvelle position
            joueurPousseGlacon(joueur, nouveauGlacon, jeu);                                                                                         //Rappelle la fonction pour faire deplacer le nouveau glacon
            break;
        }
        case 2 :
            ajouteCaseGlace(jeu->banquise, glacon->position.x, glacon->position.y);                                                                 //Transforme le glacon tombe dans l'eau en glace
            break;
        default :
            enleveCaseGlace(jeu->banquise, glacon->position.x, glacon->position.y, GLACON);                                                         //Met le glacon a sa nouvelle position
            afficheJeu(jeu);                                                                                                                        //Affiche le jeu
        }
    }
}



//Fonction qui fait fondre ou non un gla�on � chaque tour
void fonteGlacon(T_jeu *jeu)
{
    if (jeu->nombreGlacons != 0)
    {
        T_glacon *glacon = jeu->glacons[jeu->nombreGlacons - 1];

        if(verifFonteGlacon(glacon) == 1)
        {
            ajouteCaseGlace(jeu->banquise, glacon->position.x, glacon->position.y);
            jeu->nombreGlacons -= 1;
            free(glacon);
        }
    }
}



//Fonction qui s'occupe d'effectuer le tour d'un joueur dont l'identifiant est donne en parametre
int tourJoueur(T_jeu *jeu, int numJoueur)
{
    T_joueur *joueur = jeu->joueurs[numJoueur];                                              //Recupere le joueur dont l'identifiant est donne en parametre
    int **matrice = jeu->banquise->matrice,                                                  //Recupere la matrice represantant le jeu
        caseValeur,                                                                          //Variable pour la valeur de la case ou le joueur est allee
        verifDep,                                                                            //Variable pour verifier le deplacement du joueur
        j;                                                                                   //

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
        ajouteCaseGlace(jeu->banquise, joueur->position.x, joueur->position.y);                  //Met une glace sur la case que le joueur va quitter
        verifDep = deplacementJoueur(jeu->banquise, joueur);                                     //Effectue le deplacement du joueur sur la banquise
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
    }

    if(verifDep == GLACON)                                                                   //Verifie si le joueur touche un glacon
    {
        for(j = 0; j < jeu->nombreGlacons; j++)                                               //Parcourt le tableaux de glacons
        {
            if((joueur->position.x + joueur->vecteur.dx) == jeu->glacons[j]->position.x
               && (joueur->position.y + joueur->vecteur.dy) == jeu->glacons[j]->position.y)  //Condition qui regarde quel glacon a touche le joueur en parametre
            {
                joueurPousseGlacon(jeu->joueurs[numJoueur], jeu->glacons[j], jeu);           //Effectue le deplacement du glacon
                break;                                                                       //Sort de la boucle
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
        printf("La partie est finie ! ");                                          //Affiche le joueur victorieux
        changeCouleurTexte(jeu->joueurs[i]->couleur);
        printf("%s", jeu->joueurs[i]->nom);
        changeCouleurTexte(BLANC);
        printf(" est victorieux !");
        jeu->joueurs[i]->score += 1000;                                            //Le gagnant recois 1000 point
        Sleep(3000);                                                               //Attend 3s avant de passer � l'instruction suivante
        return 1;                                                                  //Retourne l'entier 1 pour signaler une victoire
    }
    else                                                                           //Si la case n'est pas celle d'arrive
    {
        return 0;                                                                  //Retourne l'entier 0 pour signaler que la partie continue
    }
}



//Affiche le scrore � la fin de la partie
void afficheScore(T_jeu *jeu)
{
    int i;                                                   //Variable pour la boucle suivante

    for(i = 0; i < jeu->nombreJoueurs; i++)                  //Boucle qui parcourt le tableau de joueurs
    {
        Sleep(2000);                                         //Attend 2 secondes
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
    }
}



//Fonction qui joue un niveau selectionne jusqu'� la victoire d'un joueur
void joueNiveau(T_jeu *jeu)
{
    int caseVal, finPartie = 0,                                //caseVal sert � connaitre la valeur de la case, et finPartie sert � mettre fin � la partie en cours
        i;                                                     //Variable pour la boucle suivante

    jeu->nombreTour = 1;                                       //Initialise le nombre de tour a 1

    while(finPartie == 0)                                      //Boucle tant que la partie n'est pas finie, c'est a dire tant qu'un joueur n'a pas atteint la case d'arrive
    {
        for(i = 0; i < jeu->nombreJoueurs; i++)                 //Boucle for qui permet � chaque joueur de jouer pour un tour
        {
            caseVal = tourJoueur(jeu, i);                      //Tour du joueur i
            finPartie = victoire(jeu, caseVal, i);             //Donne un entier si la partie est gagnee, ou si elle continue

            if (caseVal == ARRIVE)                             //Permet de reellement stopper le jeu, pour ainsi eviter les joueurs suivant de jouer
            {
                break;                                         //Brise la boucle for
            }

            fonteBanquise(jeu->banquise, jeu->rechauffement);  //Applique le rechauffement climatique sur la banquise
            fonteGlacon(jeu);                                  //
        }
        jeu->nombreTour += 1;                                  //Incremente le nombre de tour
    }
    afficheScore(jeu);                                         //Affiche le score du jeu
    Sleep(5000);                                               //Donne 5s au joueur pour lire les scores
    system("cls");                                             //Netoie la console
    printf("Merci d'avoir joue !\n");                          //Affiche remerciement
}




//Fonction qui renvoie un entier qui permet de rejouer une partie
int rejouer()
{
    char c;                                                                        //Enregistre la valeur saisie par l'utilisateur

    printf("\nVoulez vous rejouer ? (Tapez \"y\" pour oui ou \"n\" pour non) : "); //Demande au joueur s'il veut relancer une partie

    c = getchar();
    c = getchar();

    while (c != 'n' && c != 'y')                                                   //Boucle tant que le joueur ne saisit pas les bons caractere
    {
        printf("\nChoix inconnue ! Veuillez reessayer : ");                        //Previens le joueur qu'il a saisie un mauvais caractere
        c = getchar();
    }

    if (c == 'y')                                                                  //Si le caractere est y
    {
        return 0;                                                                  //Retourne valeur de succes
    }
    else                                                                           //Si le caractere est n
    {
        return 1;                                                                  //Retourne valeur d'echec
    }
}
