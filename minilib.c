#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BOOKS 100

struct Book {
    int id;
    char title[100];
    char author[100];
    float price;
};


struct Book library[MAX_BOOKS];
int count = 0;


void addBook();
void displayBooks();
void searchBook();
void deleteBook();

int main() {
    int choice;

    printf("\n=== Mini Library Management System ===\n");

    while (1) {
        printf("\n------ MENU ------\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book by ID\n");
        printf("4. Delete Book by ID\n");
        printf("5. Exit\n");
        printf("------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: printf("Exiting the program...\n"); exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}


void addBook() {
    if (count >= MAX_BOOKS) {
        printf("Library is full! Cannot add more books.\n");
        return;
    }

    struct Book b;
    printf("Enter Book ID: ");
    scanf("%d", &b.id);
    getchar();
    printf("Enter Book Title: ");
    fgets(b.title, sizeof(b.title), stdin);
    b.title[strcspn(b.title, "\n")] = 0;
    printf("Enter Author Name: ");
    fgets(b.author, sizeof(b.author), stdin);
    b.author[strcspn(b.author, "\n")] = 0;
    printf("Enter Price: ");
    scanf("%f", &b.price);

    library[count++] = b;
    printf("Book added successfully!\n");
}

void displayBooks() {
    if (count == 0) {
        printf("No books in the library.\n");
        return;
    }

    printf("\n--- Book List ---\n");
    for (int i = 0; i < count; i++) {
        printf("Book ID: %d\n", library[i].id);
        printf("Title: %s\n", library[i].title);
        printf("Author: %s\n", library[i].author);
        printf("Price: %.2f\n", library[i].price);
        printf("----------------------\n");
    }
}


void searchBook() {
    int id;
    printf("Enter Book ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (library[i].id == id) {
            printf("\nBook Found!\n");
            printf("Book ID: %d\n", library[i].id);
            printf("Title: %s\n", library[i].title);
            printf("Author: %s\n", library[i].author);
            printf("Price: %.2f\n", library[i].price);
            return;
        }
    }
    printf("Book not found!\n");
}


void deleteBook() {
    int id, found = 0;
    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (library[i].id == id) {
            for (int j = i; j < count - 1; j++) {
                library[j] = library[j + 1];
            }
            count--;
            found = 1;
            printf("Book deleted successfully!\n");
            break;
        }
    }

    if (!found)
        printf("Book not found!\n");
}
