# Library-Management-System

# Library of Airobinay - Management System

    This program acts as an assistant to the librarian helping them make their day to day responsiblities easier.

## Features

    Addition of books with unique IDs

    Ability to locate books by Title, Author, or exact ID.

    Borrowing and returning of books with availability tracking.

    Calculation of overdue fees based on a 14-day borrowing period.

    Automatic saving and loading of the library database to and from a local .txt file.


## Compilation and Execution

    On Windows:
    g++ main.cpp -o library_app.exe
    .\library_app.exe

    On Linux:
    g++ main.cpp -o library_app
    ./library_app

## Testing & Showcase Data

   
    Where no existing library_data.txt file is found, the system will automatically generate a set of showcase books from ID 200 - 204 for immediate testing.

    You can test the system's search, borrow, and fine calculation features using the following default Book IDs:

    200

    201

    202

    203 (Hint: Try returning this one)

    204 (Hint: Try returning this one to test the overdue fines)

## AuthorS

    Tevin Mwambu Ngelu 