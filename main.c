
// C program to implement
// the above approach
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CMAX 15
#define MAXINPUT 5

typedef struct SAdherent {
    int adh_Index;
    char adh_Nom[CMAX];
    int adh_NbEmprunts;
} Adherent;

typedef struct SLivre {
    int liv_Index;
    char liv_Titre[CMAX];
    char liv_Auteur[CMAX];
    int liv_Emprunteur;
} Livre;


void displayMenu() {
    printf("\n***************** Début Menu *****************\n");
    printf("(1) Gestion des adhérents\n");
    printf("\t\u2022 Ajouter, modifier ou supprimer un adhérent\n");
    printf("\t\u2022 Afficher la liste des adhérents par ordre alphabétique\n");

    printf("(2) Gestion des livres\n");
    printf("\t\u2022 Ajouter, modifier ou supprimer un livre\n");
    printf("\t\u2022 Afficher la liste des livres par ordre alphabétique (titre)\n");

    printf("(3) Gestion des emprunts\n");
    printf("\t\u2022 Emprunter un livre\t\t\u2022 Afficher la liste des livres empruntés\n");
    printf("\t\u2022 Rendre un livre\t\t\t\u2022 Afficher la liste des emprunteurs de livres\n");

    printf("(4) Quitter le programme\n");
    printf("***************** Fin menu *****************\n\n");
}


void displayStudentsMenu() {
    printf("\n***************** Début Menu gestion des adhérents *****************\n");
    printf("(1) Ajouter un adhérent\n");
    printf("(2) Modifier un adhérent\n");
    printf("(3) Supprimer un adhérent\n");
    printf("(4) Afficher la liste des adhérents par ordre alphabétique\n");
    printf("(5) Retouner au menu précédent\n");
    printf("***************** Fin Menu gestion des adhérents *****************\n\n");
}

void manageStudentsMenuActions(unsigned short subChoice, unsigned short* validSubChoice) {
    switch (subChoice) {
        case 1:
            // TODO: add Student
            break;
        case 2:
            // TODO: update Student
            break;
        case 3:
            // TODO: delete Student
            break;
        case 4:
            // TODO: read Student list by order
            break;
        case 5:
            // TODO: return back
            break;
        default:
            validSubChoice = 0;
            printf("Erreur: la valeur renseignée ne correspond à aucun des choix proposés!\n");
    }
}

void manageBooksMenuActions(unsigned short subChoice, unsigned short* validSubChoice) {
    switch (subChoice) {
        case 1:
            // TODO: add Book
            break;
        case 2:
            // TODO: update Book
            break;
        case 3:
            // TODO: delete Book
            break;
        case 4:
            // TODO: read Book list by order
            break;
        case 5:
            // TODO: return back
            break;
        default:
            *validSubChoice = 0;
            printf("Erreur: la valeur renseignée ne correspond à aucun des choix proposés!\n");
    }
}

void displayBooksMenu() {
    printf("\n***************** Début Menu gestion des livres *****************\n");
    printf("(1) Ajouter un livre\n");
    printf("(2) Modifier un livre\n");
    printf("(3) Supprimer un livre\n");
    printf("(4) Afficher la liste des livre par ordre alphabétique (titre)\n");
    printf("(5) Retouner au menu précédent\n");
    printf("***************** Fin Menu gestion des livres *****************\n\n");
}

void manageStudentsManagementMenuActions(unsigned short subChoice, unsigned short* validSubChoice) {
    switch (subChoice) {
        case 1:
            // TODO: Emprunter un livre
            break;
        case 2:
            // TODO: Afficher la liste des livres emprunté
            break;
        case 3:
            // TODO: Rendre un livre
            break;
        case 4:
            // TODO: Afficher la liste des emprunteurs de livres
            break;
        case 5:
            // TODO: return back
            break;
        default:
            validSubChoice = 0;
            printf("Erreur: la valeur renseignée ne correspond à aucun des choix proposés!\n");
    }
}

void displayStudentsManagementMenu() {
    printf("\n***************** Début Menu gestion des emprunts *****************\n");
    printf("(1) Emprunter un livre\n");
    printf("(2) Afficher la liste des livres empruntés\n");
    printf("(3) Rendre un livre\n");
    printf("(4) Afficher la liste des emprunteurs de livres\n");
    printf("(5) Retouner au menu précédent\n");
    printf("***************** Fin Menu gestion des emprunts *****************\n\n");
}

void main() {
    // TODO: define adherent table from file
    // TODO: define livre table from file


    // defining the menu and the available actions

    unsigned short validChoice;
    unsigned short validSubChoice;
    unsigned short choice;
    unsigned short subChoice;

    do {
        validChoice = 1;
        validSubChoice = 1;
        displayMenu();
        printf("Veuillez renseigner le nombre corerspondant à votre choix dessous :\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                do {
                    validSubChoice = 1;
                    displayStudentsMenu();
                    printf("Veuillez renseigner le nombre corerspondant à votre choix dessous :\n");
                    scanf("%d", &subChoice);
                    manageStudentsMenuActions(subChoice, &validSubChoice);
                } while (!validSubChoice);
                break;
            case 2:
                do {
                    validSubChoice = 1;
                    displayBooksMenu();
                    printf("Veuillez renseigner le nombre corerspondant à votre choix dessous :\n");
                    scanf("%d", &subChoice);
                    manageBooksMenuActions(subChoice, &validSubChoice);
                } while (!validSubChoice);
                break;
            case 3:
                do {
                    validSubChoice = 1;
                    displayStudentsManagementMenu();
                    printf("Veuillez renseigner le nombre corerspondant à votre choix dessous :\n");
                    scanf("%d", &subChoice);
                    manageStudentsManagementMenuActions(subChoice, &validSubChoice);
                } while (!validSubChoice);
                break;
            case 4:
                // exit the program
                exit(1);
            default:
                validChoice =0;
                printf("Erreur: la valeur renseignée ne correspond à aucun des choix proposés!\n");
        }
    } while (!validChoice);
}