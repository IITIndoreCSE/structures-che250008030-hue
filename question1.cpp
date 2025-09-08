#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// Define Book struct
struct Book {
    char title[100];
    char author[100];
    int year;
    int pages;
    char isbn[20];
};

void print_book(int index, const char* title, const char* author, int year, int pages, const char* isbn) {
    cout << "Book[" << index << "]: "
         << "title=" << title << ", "
         << "author=" << author << ", "
         << "year=" << year << ", "
         << "pages=" << pages << ", "
         << "isbn=" << isbn << "\n";
}

int main() {
    const char* filename = "books123.txt";

    // Try to open file
    ifstream input(filename);

    // Check if file opened successfully
    if (!input) {
        cerr << "Error opening file: " << filename << endl;
        cerr << "Make sure the file '" << filename << "' exists in the current directory where you run this program." << endl;
        return 1;
    } else {
        cout << "File '" << filename << "' opened successfully.\n";
    }

    int num_books;
    input >> num_books;
    input.ignore(); // skip newline after number

    Book books[100];

    for (int i = 0; i < num_books; i++) {
        input.getline(books[i].title, 100);
        input.getline(books[i].author, 100);
        input >> books[i].year >> books[i].pages;
        input.ignore(); // skip newline after reading numbers
        input.getline(books[i].isbn, 20);
    }

    for (int i = 0; i < num_books; i++) {
        print_book(i, books[i].title, books[i].author, books[i].year, books[i].pages, books[i].isbn);
    }

    return 0;
}
