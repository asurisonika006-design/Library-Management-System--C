#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100

struct Book {
    char title[50];
    char author[50];
    char isbn[20];
    int issued; // 0 = available, 1 = issued
};

struct Book library[MAX_BOOKS];
int bookCount = 0;

// Function prototypes
void addBook();
void viewBooks();
void searchBook();
void issueBook();
void returnBook();
void removeBook();

int main() {
    int choice;

    while(1) {
        printf("\n===== Library Management System =====\n");
        printf("1. Add Book\n");
        printf("2. View Books\n");
        printf("3. Search Book\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("6. Remove Book\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch(choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
            case 6: removeBook(); break;
            case 7: printf("Exiting system...\n"); return 0;
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

// Add a new book
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Library is full!\n");
        return;
    }
    printf("Enter book title: ");
    fgets(library[bookCount].title, 50, stdin);
    library[bookCount].title[strcspn(library[bookCount].title, "\n")] = 0;

    printf("Enter author name: ");
    fgets(library[bookCount].author, 50, stdin);
    library[bookCount].author[strcspn(library[bookCount].author, "\n")] = 0;

    printf("Enter ISBN: ");
    fgets(library[bookCount].isbn, 20, stdin);
    library[bookCount].isbn[strcspn(library[bookCount].isbn, "\n")] = 0;

    library[bookCount].issued = 0;
    bookCount++;
    printf("Book added successfully!\n");
}

// View all books
void viewBooks() {
    if (bookCount == 0) {
        printf("No books in the library.\n");
        return;
    }
    printf("\n--- List of Books ---\n");
    for (int i = 0; i < bookCount; i++) {
        printf("Title: %s, Author: %s, ISBN: %s, Status: %s\n",
               library[i].title, library[i].author, library[i].isbn,
               library[i].issued ? "Issued" : "Available");
    }
}

// Search for a book by ISBN
void searchBook() {
    char isbn[20];
    printf("Enter ISBN to search: ");
    fgets(isbn, 20, stdin);
    isbn[strcspn(isbn, "\n")] = 0;

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(library[i].isbn, isbn) == 0) {
            printf("Book Found: %s by %s, Status: %s\n",
                   library[i].title, library[i].author,
                   library[i].issued ? "Issued" : "Available");
            return;
        }
    }
    printf("Book not found.\n");
}

// Issue a book
void issueBook() {
    char isbn[20];
    printf("Enter ISBN to issue: ");
    fgets(isbn, 20, stdin);
    isbn[strcspn(isbn, "\n")] = 0;

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(library[i].isbn, isbn) == 0) {
            if (library[i].issued) {
                printf("Book is already issued!\n");
            } else {
                library[i].issued = 1;
                printf("Book issued successfully!\n");
            }
            return;
        }
    }
    printf("Book not found.\n");
}

// Return a book
void returnBook() {
    char isbn[20];
    printf("Enter ISBN to return: ");
    fgets(isbn, 20, stdin);
    isbn[strcspn(isbn, "\n")] = 0;

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(library[i].isbn, isbn) == 0) {
            if (!library[i].issued) {
                printf("This book was not issued.\n");
            } else {
                library[i].issued = 0;
                printf("Book returned successfully!\n");
            }
            return;
        }
    }
    printf("Book not found.\n");
}

// Remove a book
void removeBook() {
    char isbn[20];
    printf("Enter ISBN to remove: ");
    fgets(isbn, 20, stdin);
    isbn[strcspn(isbn, "\n")] = 0;

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(library[i].isbn, isbn) == 0) {
            for (int j = i; j < bookCount - 1; j++) {
                library[j] = library[j + 1];
            }
            bookCount--;
            printf("Book removed successfully!\n");
            return;
        }
    }
    printf("Book not found.\n");
}
