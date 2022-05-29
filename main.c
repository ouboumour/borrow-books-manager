
// C program to implement
// the above approach
#include <stdio.h>
#include <stdlib.h>
#include "data/json-c/json.h"
#include <string.h>
#define CMAX 30

unsigned int lastStudentAssignedId;
unsigned int lastBookAssignedId;

typedef struct SAdherent {
    int studentId;
    char studentName[CMAX];
    int borrowedBooksCounter;
    struct SAdherent* next;
} Student;

typedef struct SLivre {
    int bookId;
    char bookTitle[CMAX];
    char bookAuthor[CMAX];
    int borrowerId;
    struct SLivre* next;
} Book;

Student* studentList = NULL;
Book* bookList = NULL;

Student* StudentConstructor(
        int studentId,
        const char* studentName,
        int borrowedBooksCounter) {
    Student* student = (Student*) malloc(sizeof(Student));
    student->studentId = studentId;
    strcpy(student->studentName, studentName);
    student->borrowedBooksCounter = borrowedBooksCounter;
    return student;
}

Book* BookConstructor(int bookId, const char* bookTitle, const char* bookAuthor, int borrowerId) {
    Book* book = (Book*) malloc(sizeof(Book));
    book->bookId = bookId;
    strcpy(book->bookTitle, bookTitle);
    strcpy(book->bookAuthor, bookAuthor);
    book->borrowerId = borrowerId;
    return book;
}

int getBorrowedBooksSize(int studentId) {
    int counter = 0;
    Book* iterator = bookList;
    while (iterator) {
        if (iterator->borrowerId == studentId) {
            counter++;
        }
        iterator = iterator->next;
    }
    return counter;
}

void displayStudent(Student* student) {
    printf("\n\u2022 Id\t\t\t\t : %d\n", student->studentId);
    printf("\u2022 Nom\t\t\t\t : %s\n", student->studentName);
    printf("\u2022 Nombre d'emprunts  : %d\n", student->borrowedBooksCounter);
}

void displayBook(Book * book) {
    printf("\n\u2022 Id\t\t\t\t : %d\n", book->bookId);
    printf("\u2022 Title\t\t\t\t : %s\n", book->bookTitle);
    printf("\u2022 Autheur\t\t\t : %s\n", book->bookAuthor);
    printf("\u2022 Id de l'emprunteur : %d\n", book->borrowerId);
}

void displayStudentListAction() {
    Student* iterator = studentList;
    if (!studentList) {
        printf("La liste est vide\n");
    } else {
        while (iterator) {
            displayStudent(iterator);
            iterator = iterator->next;
        }
    }
}

void displayBookListAction() {
    Book* iterator = bookList;
    if (!bookList) {
        printf("La liste est vide\n");
    } else {
        while (iterator) {
            displayBook(iterator);
            iterator = iterator->next;
        }
    }
}

void addStudent(Student* student) {
    if (studentList == NULL || strcmp(studentList->studentName, student->studentName)>=0) {
        student->next = studentList;
        studentList = student;
    }else {
        Student* iterator;
        iterator = studentList;
        while (iterator->next != NULL
        && strcmp(iterator->next->studentName, student->studentName) < 0) {
            iterator = iterator->next;
        }
        student->next = iterator->next;
        iterator->next = student;
    }
}

void addBook(Book* book) {
    if (bookList == NULL || strcmp(bookList->bookTitle, book->bookTitle)>=0) {
        book->next = bookList;
        bookList = book;
    }else {
        Book * iterator;
        iterator = bookList;
        while (iterator->next != NULL
               && strcmp(iterator->next->bookTitle, book->bookTitle) < 0) {
            iterator = iterator->next;
        }
        book->next = iterator->next;
        iterator->next = book;
    }
}

void displayAllBorrowedBooks() {
    Book* iterator = bookList;
    while (iterator) {
        if (iterator->borrowerId) {
            displayBook(iterator);
        }
        iterator = iterator->next;
    }
}

void displayAllBorrowerStudents() {
    Student* iterator = studentList;
    while (iterator) {
        if (iterator->borrowedBooksCounter>0) {
            displayStudent(iterator);
        }
        iterator = iterator->next;
    }
}

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
    printf("(5) Retouner au menu principal\n");
    printf("***************** Fin Menu gestion des adhérents *****************\n\n");
}


Student* getStudentById(int studentId) {
    Student* iterator = studentList;
    while (iterator) {
        if (iterator->studentId == studentId) {
            return iterator;
        }
        iterator = iterator->next;
    }
    return NULL;
}

Book* getBookById(int bookId) {
    Book* iterator = bookList;
    while (iterator) {
        if (iterator->bookId == bookId) {
            return iterator;
        }
        iterator = iterator->next;
    }
    return NULL;
}

void deleteStudent(int studentId) {
    if (studentList == NULL) return;

    // case student found at the head
    if (studentList->studentId == studentId) {
        studentList = studentList->next;
        return;
    }

    // otherwise
    Student* iterator = studentList;
    while (iterator) {
        if (iterator->next->studentId == studentId) {
            free(iterator->next);
            iterator->next = iterator->next->next;
            return;
        }
        iterator = iterator->next;
    }
}

void deleteBook(int bookId) {
    if (bookList == NULL) return;

    // case student found at the head
    if (bookList->bookId == bookId) {
        bookList = bookList->next;
        return;
    }

    // otherwise
    Book* iterator = bookList;
    while (iterator) {
        if (iterator->next->bookId == bookId) {
            free(iterator->next);
            iterator->next = iterator->next->next;
            return;
        }
        iterator = iterator->next;
    }
}

void manageStudentsMenuActions(unsigned int subChoice, int* returnBackToMainMenu) {
    char studentName[CMAX];
    int studentId;
    switch (subChoice) {
        case 1:
            // add Student
            printf("Veuillez renseigner le nom de l'etudiant :\n");
            scanf("%s", studentName);
            addStudent(StudentConstructor(lastStudentAssignedId+1,studentName, 0));
            lastStudentAssignedId++;
            break;
        case 2:
            // update Student
            printf("Veuillez renseigner l'ID de l'etudiant :\n");
            scanf("%d", &studentId);

            Student * student = getStudentById(studentId);
            printf("\nVeuillez renseigner le nouveau nom de l'etudiant :\n");
            scanf("%s", studentName);

            deleteStudent(student->studentId);
            addStudent(StudentConstructor(
                student->studentId,
                studentName,
                student->borrowedBooksCounter)
            );
            break;
        case 3:
            // delete Student
            printf("Veuillez renseigner l'ID de l'etudiant :\n");
            scanf("%d", &studentId);
            deleteStudent(studentId);
            break;
        case 4:
            // read Student list by order
            displayStudentListAction();
            break;
        case 5:
            // return back
            *returnBackToMainMenu = 1;
            break;
        default:
            printf("Erreur: la valeur renseignée ne correspond à aucun des choix proposés!\n");
    }
}

void manageBooksMenuActions(unsigned int subChoice, unsigned int* returnBackToMainMenu) {
    char bookTitle[CMAX];
    char bookAuthor[CMAX];
    int bookId;
    switch (subChoice) {
        case 1:
            // add Book
            printf("Veuillez renseigner le titre du livre :\n");
            scanf("%s", bookTitle);
            printf("Veuillez renseigner l'auteur du livre :\n");
            scanf("%s", bookAuthor);
            addBook(BookConstructor(
                    lastBookAssignedId+1,
                    bookTitle,
                    bookAuthor,
                    0)
            );
            lastBookAssignedId++;
            break;
        case 2:
            // update Book
            printf("Veuillez renseigner l'ID du livre :\n");
            scanf("%d", &bookId);

            Book * book = getBookById(bookId);
            printf("\nVeuillez renseigner le nouveau titre du livre :\n");
            scanf("%s", bookTitle);

            printf("\nVeuillez renseigner le nouveau autheur :\n");
            scanf("%s", bookTitle);

            deleteBook(bookId);
            addBook(BookConstructor(
                    book->bookId,
                    bookTitle,
                    bookAuthor,
                    book->borrowerId)
            );
            break;
        case 3:
            // delete Book
            printf("Veuillez renseigner l'ID du livre :\n");
            scanf("%d", &bookId);
            deleteBook(bookId);
            break;
        case 4:
            // read Book list by order
            displayBookListAction();
            break;
        case 5:
            // return back
            *returnBackToMainMenu = 1;
            break;
        default:
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

void manageStudentsManagementMenuActions(unsigned int subChoice, unsigned int* returnBackToMainMenu) {
    int bookId;
    int studentId;
    switch (subChoice) {
        case 1:
            // Emprunter un livre
            printf("Veuillez renseigner l'ID du livre :\n");
            scanf("%d", &bookId);
            printf("Veuillez renseigner l'ID de l'etudiant :\n");
            scanf("%d", &studentId);

            Book* book = getBookById(bookId);
            Student* student = getStudentById(studentId);
            // TODO: check if book exist
            // TODO: check if student exist
            // TODO: check if book available

            book->borrowerId = studentId;
            student->borrowedBooksCounter++;
            break;
        case 2:
            // Afficher la liste des livres emprunté
            displayAllBorrowedBooks();
            break;
        case 3:
            // Rendre un livre
            printf("Veuillez renseigner l'ID du livre :\n");
            scanf("%d", &bookId);
            printf("Veuillez renseigner l'ID de l'etudiant :\n");
            scanf("%d", &studentId);

            book = getBookById(bookId);
            student = getStudentById(studentId);
            // TODO: check if book exist
            // TODO: check if student exist
            // TODO: check if book available

            book->borrowerId = 0;
            student->borrowedBooksCounter--;
            break;
        case 4:
            // Afficher la liste des emprunteurs de livres
            displayAllBorrowerStudents();
            break;
        case 5:
            // return back
            *returnBackToMainMenu = 1;
            break;
        default:
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
void loadStudentData() {
    json_object *root = json_object_from_file("data/students.json");
    int n = json_object_array_length(root);
    for (int i=0;i<n; i++)
    {
        struct json_object* currentJsonObject= json_object_array_get_idx(root, i);
        json_object* studentId = json_object_object_get(currentJsonObject, "studentId");
        json_object* studentName = json_object_object_get(currentJsonObject, "studentName");

        int id= json_object_get_int64(studentId);
        Student* student = StudentConstructor(
                id,
                json_object_get_string(studentName),
                getBorrowedBooksSize(id)
        );

        addStudent(student);
    }
    // free json taken memory
    json_object_put(root);
}

void loadBookData() {
    json_object *root = json_object_from_file("data/books.json");
    int n = json_object_array_length(root);
    for (int i=0;i<n; i++)
    {
        struct json_object* currentJsonObject= json_object_array_get_idx(root, i);
        json_object* bookId = json_object_object_get(currentJsonObject, "bookId");
        json_object* bookTitle = json_object_object_get(currentJsonObject, "bookTitle");
        json_object* bookAuthor = json_object_object_get(currentJsonObject, "bookAuthor");
        json_object* borrowerId = json_object_object_get(currentJsonObject, "borrowerId");


        Book* book = BookConstructor(
                json_object_get_int64(bookId),
                json_object_get_string(bookTitle),
                json_object_get_string(bookAuthor),
                json_object_get_int64(borrowerId)
        );

        addBook(book);
    }
    // free memory occupied by json root
    json_object_put(root);
}

void loadIdsManagers() {
    json_object *root = json_object_from_file("data/ids_manager.json");

    json_object* lastStudentAssignedIdJson = json_object_object_get(root, "lastStudentAssignedId");
    json_object* lastBookAssignedIdJson = json_object_object_get(root, "lastBookAssignedId");

    lastStudentAssignedId = json_object_get_int64(lastStudentAssignedIdJson);
    lastBookAssignedId = json_object_get_int64(lastBookAssignedIdJson);

    // free memory occupied by json root
    json_object_put(root);
}

void updateStudentFile() {
    json_object *root = json_object_new_array();
    Student* iterator = studentList;

    while (iterator) {

        json_object *child = json_object_new_object();
        json_object_object_add(child, "studentId", json_object_new_int64(iterator->studentId));
        json_object_object_add(child, "studentName", json_object_new_string(iterator->studentName));

        json_object_array_add(root, child);
        iterator = iterator->next;
    }

    json_object_to_file_ext("students.json", root, JSON_C_TO_STRING_PRETTY);
    // free memory occupied by json root
    json_object_put(root);
}

void updateBookFile() {
    json_object *root = json_object_new_array();
    Book* iterator = bookList;

    while (iterator) {

        json_object *child = json_object_new_object();
        json_object_object_add(child, "bookId", json_object_new_int64(iterator->bookId));
        json_object_object_add(child, "bookTitle", json_object_new_string(iterator->bookTitle));
        json_object_object_add(child, "bookAuthor", json_object_new_string(iterator->bookAuthor));
        json_object_object_add(child, "borrowerId", json_object_new_int64(iterator->borrowerId));

        json_object_array_add(root, child);
        iterator = iterator->next;
    }

    json_object_to_file_ext("books.json", root, JSON_C_TO_STRING_PRETTY);
    // free memory occupied by json root
    json_object_put(root);
}

void updateIdsManagerFile() {
    json_object *root = json_object_new_object();
    json_object_object_add(root, "lastStudentAssignedId", json_object_new_int64(lastStudentAssignedId));
    json_object_object_add(root, "lastBookAssignedId", json_object_new_int64(lastBookAssignedId));

    json_object_to_file_ext("ids_manager.json", root, JSON_C_TO_STRING_PRETTY);
    // free memory occupied by json root
    json_object_put(root);
}

void main() {
    // load data from files
    loadBookData();
    loadStudentData();
    loadIdsManagers();

    unsigned int validChoice;
    unsigned int choice;
    unsigned int subChoice;
    unsigned int returnBackToMainMenu;
    unsigned int returnBackToSubMenu;

    do {
        validChoice = 1;
        returnBackToMainMenu = 0;
        displayMenu();

        printf("Veuillez renseigner le nombre corerspondant à votre choix dessous :\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                do {
                    returnBackToSubMenu = 0;
                    displayStudentsMenu();
                    printf("Veuillez renseigner le nombre corerspondant à votre choix dessous :\n");
                    scanf("%d", &subChoice);
                    manageStudentsMenuActions(subChoice, &returnBackToMainMenu);
                    validChoice = subChoice>=1 && subChoice<=5;
                    if (validChoice && subChoice!=5) {
                        do {
                            printf("\n(1) Retourner au menu precedent \n");
                            scanf("%d", &returnBackToSubMenu);
                            if (returnBackToSubMenu != 1) {
                                printf("Erreur: la valeur renseignée ne correspond à aucun des choix proposés!\n");
                            }
                        } while (returnBackToSubMenu != 1);
                    }

                } while (!validChoice || returnBackToSubMenu == 1);
                break;
            case 2:
                do {
                    returnBackToSubMenu = 0;
                    displayBooksMenu();
                    printf("Veuillez renseigner le nombre corerspondant à votre choix dessous :\n");
                    scanf("%d", &subChoice);
                    manageBooksMenuActions(subChoice, &returnBackToMainMenu);
                    short validChoice = subChoice>=1 && subChoice<=5;
                    if (validChoice && subChoice!=5) {
                        do {
                            printf("\n(1) Retourner au menu precedent \n");
                            scanf("%d", &returnBackToSubMenu);
                            if (returnBackToSubMenu != 1) {
                                printf("Erreur: la valeur renseignée ne correspond à aucun des choix proposés!\n");
                            }
                        } while (returnBackToSubMenu != 1);
                    }

                } while (!validChoice || returnBackToSubMenu == 1);
                break;
            case 3:
                do {
                    returnBackToSubMenu = 0;
                    displayStudentsManagementMenu();
                    printf("Veuillez renseigner le nombre corerspondant à votre choix dessous :\n");
                    scanf("%d", &subChoice);
                    manageStudentsManagementMenuActions(subChoice, &returnBackToMainMenu);
                    short validChoice = subChoice>=1 && subChoice<=5;
                    if (validChoice && subChoice!=5) {
                        do {
                            printf("\n(1) Retourner au menu precedent \n");
                            scanf("%d", &returnBackToSubMenu);
                            if (returnBackToSubMenu != 1) {
                                printf("Erreur: la valeur renseignée ne correspond à aucun des choix proposés!\n");
                            }
                        } while (returnBackToSubMenu != 1);
                    }

                } while (!validChoice || returnBackToSubMenu == 1);
                break;

            case 4:
                // update files
                updateStudentFile();
                updateBookFile();
                updateIdsManagerFile();
                // exit the program
                exit(1);
            default:
                validChoice =0;
                printf("Erreur: la valeur renseignée ne correspond à aucun des choix proposés!\n");
        }
    } while (!validChoice || returnBackToMainMenu);
}