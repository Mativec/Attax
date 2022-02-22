#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#define TAILLE_PLATEAU 7
#define TAILLE_MAX_NOM 20
#define PROBA_INFECTION 0.75 //pour changer la probabilites d'infecter une piece voisine

typedef struct{
    char nom[TAILLE_MAX_NOM];
    char symbol; // 'x' ou 'o'
    int score; //nombre de pions sur le plateau pour un joueur 
} Joueur;

typedef struct{
    char plateau[TAILLE_PLATEAU+2][TAILLE_PLATEAU+2];
    Joueur * joueurs[2];
} Plateau;


// 1. Création d'un objet de chaque structure (une fonction par structure):

void init_joueur(Joueur * J1, Joueur * J2, int graph, int ordi){
    /*
    Fonction de type void qui va initialiser un objet de type Joueur, en ascci ou en MLV selon graph.
    Elle ne retourne rien mais modifie la valeur pointé par son parametre.
    Parametre:
    *J1: pointeur de type joueur
    *J: pointeur de type joueur
    graph: int compare le type d'affichage
    */
    if (graph == 0){
    printf("Rentrer le nom du joueur 1: ");
    scanf("%s" ,J1 -> nom);
    printf("\n");

        if(ordi == 1){
            J2 -> nom[0] = 'b';
            J2 -> nom[1] = 'o';
            J2 -> nom[2] = 't';
            printf("Vous affrontez l'ordinateur\n");
        }
        else{
            printf("Rentrer le nom du joueur 2: ");
            scanf("%s" ,J2 -> nom);
            printf("\n");
        }
    }
    else{
        MLV_draw_text( 50, 150,"Nom du joueur 1: (regardez le terminal)",\
        MLV_COLOR_BLACK,J1 -> nom);
        MLV_actualise_window();
        MLV_clear_window(MLV_COLOR_WHITE);
        printf("Nom du joueur 1: ");
        scanf("%s" ,J1 -> nom);
        printf("\n");
        if (ordi == 0){
            MLV_actualise_window();
            MLV_draw_text( 50, 150,"Nom du joueur 2: (regardez le terminal)",\
            MLV_COLOR_BLACK,J2 -> nom);
            MLV_actualise_window();
            printf("Nom du joueur 2: ");
            scanf("%s" ,J2 -> nom);
            printf("\n");
        } else {
            J2 -> nom[0] = 'b';
            J2 -> nom[1] = 'o';
            J2 -> nom[2] = 't';
        }
        MLV_clear_window(MLV_COLOR_WHITE);

    }
    J1->symbol = 'x';
    J1->score = 2;
    J2->symbol = 'o';
    J2->score = 2;
    
    // prendre en paremetre int graph + faire les conditions pour ascii ou graph + faire input box
}

void init_plateau(Plateau * p, Joueur *J1, Joueur *J2){
    /*
    Fonction de type void qui va initialiser un objet de type Plateau.
    Elle ne retourne rien mais modifie la valeur pointé par son parametre.
    '.'  = vide
    '*' = bord
    */
    p -> joueurs[0] = J1;
    p -> joueurs[1] = J2;
    for (int i = 0; i < TAILLE_PLATEAU + 2; i++){
        for (int j = 0; j < TAILLE_PLATEAU + 2; j++){
            if (i%(TAILLE_PLATEAU+1) == 0 || j%(TAILLE_PLATEAU+1) == 0){
                p -> plateau[i][j] = '*';
            } else {
                p -> plateau[i][j] = '.';
            }
        }
    }
    p -> plateau[1][1] = p -> joueurs[0] -> symbol;
    p -> plateau[TAILLE_PLATEAU][1] = p -> joueurs[1] -> symbol;
    p -> plateau[1][TAILLE_PLATEAU] = p -> joueurs[1] -> symbol;
    p -> plateau[TAILLE_PLATEAU][TAILLE_PLATEAU] = p -> joueurs[0] -> symbol;
}

// 2. Le tri des arguments:

void tri_arg(int nb_arg, char *arg[], int *graph, int *mdj){
    /*
    Fonction qui reçoit les arguments du main en parametre et modifie
    l'organisation du programme en conséquence.
    nb_arg = argc.
    arg[] = argv.
    mdj pointe vers le choix du mode de jeu.
    graph et mdj fonctionne comme des booléans (valent 0 ou 1)
    Parametre:
    nb_arg: int, compte le nombre d'argument
    char *arg[]: chaine de carectere
    *graph: pointeur de type int, pou rle choix graphque 
    *mdj: pointeur de type int
    */
   for (int i = 1;  i < nb_arg; i++){
        if (arg[i][0] == '-'){
            if (arg[i][1] == 'g'){
                *graph = 1;
            }
            if (arg[i][1] == 'o'){
                *mdj = 1;
            }
        }
   }
}

// 3. Les mécaniques de jeu:

int infection(int x, int y, Joueur *patient0, Plateau *p){    
    /*
    Fonction qui simule la mécanique d'inferction prévu dans le jeu
    (un pion posé fais passer tous ceux autour de lui dans son camp).
    patient0 est un int (1 pour J1, 2 pour J2) correspondant au joueur qui a
    posé le pion.
    Parametre:
    x: int, represente une cordonnee
    y: int, represente une cordonnee
    *patient0: pointeur de type joueur
    *p: pointeur de type plateau
    */
    
    int indice;
    if (p -> joueurs[0] -> symbol == patient0 -> symbol){
        indice = 1;
    } else {
        indice = 0;
    }
    for (int i = y - 1; i <= y + 1; i++){
        for (int j = x - 1; j <= x + 1; j++){
            if (p -> plateau[i][j] != '.' && p -> plateau[i][j] != '*'){
                if (p -> plateau[i][j] != patient0 -> symbol){
                    p -> plateau[i][j] = patient0 -> symbol;
                    patient0 -> score++;
                    p -> joueurs[indice] -> score--;
                }
            }
        }
    }
    return 0;
}

int place_pion(int x, int y, Joueur *j, Plateau *p){
    /*
    Ajoute un pion au joueur numéro joueur sur le plateu de jeu
    Parametre:
    x: int, represente une cordonnee
    y: int, represente une cordonnee
    *j: pointeur de type joueur
    *p: pointeur de type plateau

    */
    if (p -> plateau[y][x] == '.'){
        p -> plateau[y][x] = j -> symbol;
        j -> score++;
        if (MLV_get_random_integer(0, 100) <= PROBA_INFECTION * 100){
            int infecte;
            infecte = infection(x, y, j, p);
        }
        return 1;
    }
    return 0;
}



// 4. Les différents types d'affichages:

void ascii(Plateau p){
    /*
    Fonction qui gère l'affichage du jeu en ascii.
    p désigne le plateau de jeu.

    '*' correspond au bords du plateau
    'x' correspond aux pions du J1
    'o' correspond aux pions du J2

    La fonction utilise saisie pour les interactions avec le joueur
    et affiche le résultat en fin de partie.
    Parametre: 
    p: reference a la structure plateau
    ex:
    ∗ ∗ ∗ ∗ ∗
    ∗ x . o ∗
    ∗ . . . ∗
    ∗ o . x ∗
    ∗ ∗ ∗ ∗ ∗
    */
    for (int i = 0; i < TAILLE_PLATEAU + 2; i++ ){
        for (int j = 0; j < TAILLE_PLATEAU + 2; j++){
            printf("%c ", p.plateau[j][i]);
        }
        printf("\n");
    }
}

void graphisme(Plateau p){
    /*
    Fonction qui gère l'affichage du jeu avec la librairie graphique MLV.
    Le nom du joueur en train de jouer sera affiché.
    'X' correspond aux pions du J1.
    'O' correspond aux pions du J2.

    Parametre:
    p: reference a plateau de jeu
    */
    MLV_clear_window(MLV_COLOR_WHITE);
    for(int i =1; i<TAILLE_PLATEAU +1; i++){
        for(int j=1; j<TAILLE_PLATEAU +1 ; j++){
            MLV_draw_rectangle(50*i,50*j, 50,50, MLV_COLOR_BLACK);
            if(p.plateau[j][i] == 'x'){
                MLV_draw_circle(50*j+25,50*i+25,23,MLV_COLOR_BLACK);
            }
            if(p.plateau[j][i] =='o'){
                MLV_draw_filled_circle(50*j+25,50*i+25,23, MLV_COLOR_BLACK);   
            }
        }
    }
    MLV_actualise_window();
}


// 5. Les différents modes de jeux (déroulement de la partie):

int controle_voisins(int x, int y, Plateau p){
    /*
    Contrôle la saisie par le joueur.
    x: int, represente une cordonnee
    y: represente une cordonnee
    p: reference a plateau
    */
    if (x < 1 || x > TAILLE_PLATEAU || y < 1 || y > TAILLE_PLATEAU){
        return 0;
    }
    for (int i = y - 1; i <= y + 1; i++){
        for (int j = x - 1; j <= x + 1; j++){
            if (p.plateau[i][j] != '.' && p.plateau[i][j] != '*'){
                return 1;
            }
        }
    }
    return 0;
}

void saisie(Plateau *p, Joueur *j, int graph){
    /*
    Fonction qui gère l'interaction avec le joueur selon mode graphique
    ou ascii.
    La fonction renvoie les indices saisis pour une utilisation sur le plateau
    de jeu.
    Parametre:
    *p: pointeur de type Plateau
    *j: pointeur de type Joueur
    grah: int compare l'afifchage
    */
    int x;
    int y;

    if (graph == 0){ //ascii
        do{
            printf("%s (%c), veuillez saisir les coordonnées ",\
             j->nom, j->symbol);
            printf("où jouer(entre 1 et %d) : ", TAILLE_PLATEAU);
            scanf("%d", &x);
            printf(" ");
            scanf("%d", &y);
            printf("\n");
        } while (!controle_voisins(x, y, *p) || !place_pion(x, y, j, p));
    } else{ //MLV
        
        do{
            MLV_draw_text( 10,10,"Au tour de %s de jouer",MLV_COLOR_BLACK,\
            j->nom);
            MLV_wait_mouse(&y, &x);
            x = x /50 ;
            y = y /50 ;
        } while(!controle_voisins(x, y, *p) || !place_pion(x, y, j, p));
    }
}

void pve(Plateau *p, Joueur *ordi){

    /*
    Fonction qui simule le deroulement d'un tour contre l'ordinateur, jouant de maniere aleatoire.
    Parametres:
    *p: pointeur de type plateau
    *ordi: pointeur de type plateau
    */
    int x;
    int y;
    printf("Au tour de l'ordinateur de jouer...\n\n");
    do {
        x = MLV_get_random_integer(1, TAILLE_PLATEAU);
        y = MLV_get_random_integer(1, TAILLE_PLATEAU);
    }
    while (!controle_voisins(x, y, *p) || !place_pion(x, y, ordi, p));
}

int gameover(Joueur J1, Joueur J2, int graph){
    /*
    FOnction qui détermenine le gagnant d'une partie en comparant les scores,
    affiche les scores en ascii ou en MLV selon la valeur de graph.
    Parametre:
    J1: fait références à la structure joueur
    J2: fait références à la structure joueur
    graph: int pour comparer les types d'affichages

    */
    if (J1.score + J2.score == TAILLE_PLATEAU * TAILLE_PLATEAU){
        if (J2.score < J1.score){
            if (graph ==0){
            printf("Bravo %s, vous avez gagne %d a %d.\n", J1.nom, J1.score,\
            J2.score);
            }
            else{
                MLV_draw_text(125,30,"Bravo %s, vous avez gagné !", \
                MLV_COLOR_BLACK, J1.nom);
                MLV_actualise_window();
                MLV_wait_mouse(NULL,NULL);
            }
            return 1;
        }

        if (J2.score > J1.score){
            if (graph ==0){
            printf("Bravo %s, vous avez gagne %d a %d.\n", J2.nom, J2.score,\
            J1.score);
            }
            else{
                MLV_draw_text(125,30,"Bravo %s, vous avez gagné !", \
                MLV_COLOR_BLACK, J2.nom);
                MLV_actualise_window();
                MLV_wait_mouse(NULL,NULL);
            }
            return 1;
        }

        if (J1.score == J2.score){
            if (graph == 0){
            printf("Match nul, %d partout.\n",J1.score);
            }
            else{
                MLV_draw_text(125,30,"Match nul",MLV_COLOR_BLACK);
                MLV_actualise_window();
                MLV_wait_mouse(NULL,NULL);
                }
            return 1;  
        }
    }
    return 0;
}

// 6. Gestion générale du programme:

int main(int argc, char *argv[]){
    int graph = 0; //affichage, 0 = ascii, 1 = MLV
    int adv = 0; //adversaire, 0 = humain, 1 = ordi
    tri_arg(argc, argv, &graph, &adv);
    if (graph == 1){
        MLV_create_window("Attax", "Attax",500,500);
        MLV_clear_window(MLV_COLOR_WHITE);
        MLV_actualise_window();
    }
    Joueur J1;
    Joueur J2;
    Plateau p;
    init_joueur(&J1, &J2, graph, adv);
    init_plateau(&p, &J1, &J2);

    if (graph == 0){
        ascii(p);
    } else {
        graphisme(p);
    }
    int joueur = 1;
    while(!gameover(J1, J2, graph)){
        if (joueur == 1){
            saisie(&p, &J1, graph);
        } else {
            if (adv == 0){
                saisie(&p, &J2, graph);
            } else {
                pve(&p, &J2);
            }
        }
        if (graph == 0){
            ascii(p);
        }
        else{
            graphisme(p);
        }
        if (graph == 0) {
            printf("Score actuel : %s(%c) %d - %s(%c) %d\n",\
            J1.nom, J1.symbol, J1.score, J2.nom, J2.symbol, J2.score);
        } else {
            MLV_draw_text(250, 450, "Score actuel : %s(%c) %d - %s(%c) %d",\
            MLV_COLOR_BLACK,\
            J1.nom, J1.symbol, J1.score, J2.nom, J2.symbol, J2.score);
            MLV_update_window();
        }
        joueur = 3 - joueur;
    }
    if (graph == 1){
        MLV_free_window();
    }
    return 0;
}