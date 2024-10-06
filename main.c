#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define taille 3  // Définir la taille du plateau (3x3)

char plateau[taille][taille];  // Déclaration du plateau de jeu (3x3)

void afficherGrille() { 
    for (int i = 0; i < taille; i++) { 

        for (int j = 0; j < taille; j++) {  
            printf(" [%c] ", plateau[i][j]);
            if (j < taille - 1) printf("|");  
        }
        printf("\n");
        if (i < taille - 1) {
            printf("  ---+-----+-\n");  
        }
    }
    printf("\n");  
}

void initialiserPlateau() {
    for (int i = 0; i < taille; i++) {  
        for (int j = 0; j < taille; j++) {  
            plateau[i][j] = ' '; 
        }
    }
}

int TourJoueur() {
    int ligne, col;

    while (1) {  
        afficherGrille();  
        printf("A votre tour ! Choisissez une ligne (1-3) : ");
        scanf("%d", &ligne);
        printf("Puis choisissez une colonne (1-3) : ");
        scanf("%d", &col);

        
        ligne--;  
        col--;    

       
        if (ligne >= 0 && ligne < taille && col >= 0 && col < taille && plateau[ligne][col] == ' ') {
            plateau[ligne][col] = 'X'; 
            return 1;  
        } else {
            printf("Case déjà occupée ou invalide. Essayez à nouveau.\n");
        }
    }
}

int TourOrdinateur() {
    int ligne, col;  

    do {
        ligne = rand() % taille;  // Choisir une ligne aléatoire
        col = rand() % taille;    // Choisir une colonne aléatoire 
    } while (plateau[ligne][col] != ' ');  // Tant que la case est déjà occupée, recommencer

    printf("L'ordinateur joue en %d, %d.\n", ligne + 1, col + 1);
    plateau[ligne][col] = 'O';  
    return 1;  
}

int verifGagnant(char symbole) {
    for (int i = 0; i < taille; i++) {
        if (plateau[i][0] == symbole && plateau[i][1] == symbole && plateau[i][2] == symbole) {
            return 1;
        }
    }
    for (int i = 0; i < taille; i++) {
        if (plateau[0][i] == symbole && plateau[1][i] == symbole && plateau[2][i] == symbole) {
            return 1;
        }
    }
    if (plateau[0][0] == symbole && plateau[1][1] == symbole && plateau[2][2] == symbole) {
        return 1;
    }
    if (plateau[0][2] == symbole && plateau[1][1] == symbole && plateau[2][0] == symbole) {
        return 1;
    }
    return 0;
}


int verifEgalite() {
    for (int i = 0; i < taille; i++) {  
        for (int j = 0; j < taille; j++) {  
            if (plateau[i][j] == ' ') {  
                return 0;  
            }
        }
    }
    return 1;  
}

int main() {
    srand(time(NULL));  
    int tour = 0;  
    int jeuTermine = 0;  

    initialiserPlateau();  

    while (jeuTermine == 0) {  
        if (TourJoueur()) {
            tour++;  
            if (verifGagnant('X')) {
                afficherGrille();  
                printf("Félicitations! Vous avez gagné!\n");  
                jeuTermine = 1;  
            } else if (verifEgalite()) {
                afficherGrille();
                printf("Égalité! Le plateau est plein.\n");
                jeuTermine = 1;  
            }
        }

        if (jeuTermine==0 && TourOrdinateur()) {
            tour++;  
            if (verifGagnant('O')) {
                afficherGrille(); 
                printf("L'ordinateur a gagné! Désolé...\n");  
                jeuTermine = 1;  
            } else if (verifEgalite()) {
                afficherGrille();
                printf("Égalité! Le plateau est plein.\n");
                jeuTermine = 1;  
            }
        }
    }

    return 0;  
}
