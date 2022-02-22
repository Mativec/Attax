#define TAILLE_PLATEAU 7
#define TAILLE_MAX_NOM 20

typedef struct{
    char nom[TAILLE_MAX_NOM];
    char symbol; // 'x' ou 'o'
    int score; //nb pions sur le plateau
} Joueur;

typedef struct{
    char plateau[TAILLE_PLATEAU+2][TAILLE_PLATEAU+2];
    Joueur ∗ joueurs[2];
} Plateau;


/*
La fonction.
Ses arguments.
Sa valeur de retour.
Ses eventuels effetes de bords avec eventuellement un exemple
*/

// 1. Création d'un objet de chaque structure (une fonction par structure):

void init_joueur(Joueur * j){
    /*
    Fonction qui va initialiser un objet de type Joueur.
    Elle prend en parametre un pointeur vers un objet de type Joueur.
    Elle ne retourne rien mais modifie la valeur pointé par son parametre.
    */
    break();
}

void init_plateau(Plateau * p){
    /*
    Fonction qui va initialiser un objet de type Plateau.
    Elle prend en parametre un pointeur vers un objet de type Plateau.
    Elle ne retourne rien mais modifie la valeur pointé par son parametre.
    */
    break();
}


// 2. Le tri des arguments:

void tri_arg(int nb_arg, char arg[], int *graph, int *mdj){
    /*
    Fonction qui reçoit les arguments du main en parametre et modifie
    l'organisation du programme en conséquence.
    nb_arg = argc.
    arg[] = argv.
    graph pointe vers le choix du style graphique.
    mdj pointe vers le choix du mode de jeu.
    graph et mdj fonctionne comme des booléans (valent 0 ou 1)
    */
   break();
}

// 3. Les mécaniques de jeu:

void place_pion(int joueur, Plateau *p){
    /*
    Ajoute un pion au joueur numéro joueur dans p
    p pointe sur le plateau de jeu
    joueur est un int (1 pour J1, 2 pour J2)
    Elle modifiera donc p.plateau pour les remplir les cases correspondante
    mais aussi incrémentera p.joueur[joueur]
    */
   break();
}

void enleve_pion(int joueur, Plateau *p){

    /*
    Retire un pion au joueur numéro joueur dans p.
    p pointe sur le plateau de jeu.
    joueur est un int (1 pour J1, 2 pour J2).
    Elle modifiera donc p.plateau pour les remplir les cases correspondante
    mais aussi décrémentera p.joueur[joueur].
    */
   break();
}

void infection(int patient0, Plateau *p){    
    /*
    Fonction qui simule la mécanique d'inferction prévu dans le jeu
    (un pion posé fais passer tous ceux autour de lui dans son camp).
    patient0 est un int (1 pour J1, 2 pour J2) correspondant au joueur qui a
    posé le pion.
    p pointe sur le plateau de jeu.
    Elle modifiera donc p.plateau pour effectuer le changement de camp des
    pions alentours mais aussi modifiera les valeurs dans p.joueur.
    */
   break();
}

// 4. Les différents types d'affichages:

void ascii(Plateau p){
    /*
    Fonction qui gère l'affichage du jeu en ascii.
    p désigne le plateau de jeu.

    '*' correspond au bords du plateau
    'x' correspond aux pions du J1
    'o' correspond aux pions du J2

    La fonction utilise saisie pour les intéractions avec le joueur
    et affiche le résultat en fin de partie.

    ex:
    ∗ ∗ ∗ ∗ ∗
    ∗ x . o ∗
    ∗ . . . ∗
    ∗ o . x ∗
    ∗ ∗ ∗ ∗ ∗
    */
   break();
}

void graphisme(Plateau p){
    /*
    Fonction qui gère l'affichage du jeu avec la librairie graphique MLV.
    p désigne le plateau de jeu.

    Le nom du joueur en train de jouer sera affiché.
    'X' correspond aux pions du J1.
    'O' correspond aux pions du J2.

    La fonction utilise saisie pour les interactions avec le joueur
    et affiche le résultat en fin de partie.
    */
   break();
}

// 5. Les différents modes de jeux (déroulement de la partie):

int disponible(Plateau p){
    /*
    Fonction qui scan le plateau de jeu et renvoie un tableau d'entier
    contenant les indices cases jouables.
    p désigne le plateau de jeu
    La fonction renvoie un tableau à 2 dimensions avec uniquement les cases
    jouables.
    p n'est pas modifié suite à l'execution de cette fonction.
    */
   break();
}

int saisie(Plateau p, int graph){
    /*
    Fonction qui gère l'interaction avec le joueur selon mode graphique
    ou ascii.
    p designe le plateau de jeu.
    graph designe le style graphique choisi (graphique ou ascii).
    La fonction renvoie les indices saisis pour une utilisation sur le plateau
    de jeu.
    Elle ne modifie pas le plateau de jeu.
    */
    break()
}

void pvp(int joueur, Plateau *p){
    /*
    Fonction qui simule le deroulement d'un tour entre 2 joueurs.
    joueur désigne le numéro du joueur en train de jouer
    p pointe sur le plateau de jeu.
    La fonction fera appelle à saisie et à celles de la partie 3.
    */
    saisie(&p, J1, 1);
    ascii(p);
}

void pve(int ordi, Plateau *p){
    /*
    Fonction qui simule le deroulement d'un tour contre l'ordinateur.
    ordi désigne le numéro du joueur ou de l'ordinateur dont c'est le tour.
    p pointe sur le plateau de jeu.
    La fonction fera appelle à saisie et à celles de la partie 3.
    */
   break();
}


// 6. Gestion générale du programme:

int main(int argc, char *argv[]){
    return 0;
}