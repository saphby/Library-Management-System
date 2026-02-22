#include <iostream>
#include <cctype>
#include <vector>
#include <fstream>
#include <ctime>

class Book {
    private:
    std::string title;
    std::string author;
    int id;
    bool isAvailable;

    public:

    std::string borrowerName;
    time_t borrowDate;

    Book(std::string t, std::string a, int i){
        title = t;
        author = a;
        id = i;
        isAvailable = true;
        borrowerName = "None";
        borrowDate = 0;
    }
    std::string getTitle() {
        return title;
    }

    std::string getAuthor() {
        return author;
    }

    int getId() {
        return id;
    }

    bool getAvailability() {
        return isAvailable;
    }

    bool borrow() {
        if (isAvailable) {
            isAvailable = false;
            return true;
        } else {
            return false;
        };
    }
    
    bool giveBack() {
        if (!isAvailable) {
            isAvailable = true;
            return true;
        } else {
            return false;
        }
    }
};



bool continueBookAdd() {
    std::string userChoice;
    do {
        std::cout << "Add another Book (y/n)" << std::endl;
        std::cin >> userChoice;
        std::cin.ignore(1000, '\n'); 
        
        if (userChoice != "YES" && userChoice != "Yes" && userChoice != "yes" && userChoice != "Y" && userChoice != "y" &&
            userChoice != "NO" && userChoice != "No" && userChoice != "no" && userChoice != "N" && userChoice != "n" ) {
                std::cout << "Invalid input, Please try again" << std::endl;
            }
    } while(userChoice != "YES" && userChoice != "Yes" && userChoice != "yes" && userChoice != "Y" && userChoice != "y" &&
            userChoice != "NO" && userChoice != "No" && userChoice != "no" && userChoice != "N" && userChoice != "n" );

    return(userChoice == "YES" || userChoice == "Yes" || userChoice == "yes" || userChoice == "Y" || userChoice == "y");
}

void addBooks(std::vector<Book>&library) {    
    std::string userTitle;
    std::string userAuthor;
    int userId;

    do
    {
    std::cout << "Enter Book Title: " << std::endl;
    std::getline(std::cin, userTitle);

    std::cout << "Enter Book Author: " << std::endl;
    std::getline(std::cin, userAuthor);

    std::cout << "Enter Book ID: " << std::endl;
    std::cin >> userId;

    bool idExists = false;
    for (Book book : library) {
        if (book.getId() == userId) {
            idExists = true;
            break;
        }
    }

    if (idExists) {
        std::cout << "Book ID " << userId << " already exists" << std::endl;
    } else {
        Book bUser(userTitle, userAuthor, userId);
        library.push_back(bUser);
    }

    } while(continueBookAdd());

}


void findBookById(std::vector<Book>&library, int search) {
    int searchId;
    int foundId = -1;
    searchId = search;
    for (int i = 0; i < library.size(); i++) {
        if (library[i].getId() == searchId ) {
            foundId = i;
            break;        
        }        
}
    if (foundId > -1) {
        std::cout << "Book found: " << library[foundId].getTitle() << ", " << library[foundId].getAuthor() << ", " << library[foundId].getId() << std::endl;
        
        if (library[foundId].getAvailability()) {
            std::cout << "Status: Available " << std::endl;
        } else {
            std::cout << "Status: Borrowed by " << library[foundId].borrowerName << std::endl;
        }
        
    } else std::cout << "Not found" << std::endl;   
} 

void findBookByTitle(std::vector<Book>&library, std::string search) {
    std::string searchTitle;
    searchTitle = search;
    bool foundAny = false;
    for (int i = 0; i < library.size(); i++) {
        if (library[i].getTitle() == searchTitle) {
        std::cout << "Book found: " << library[i].getTitle() << ", " << library[i].getAuthor() << ", " << library[i].getId() << std::endl;
        foundAny = true;
        }    
    }

    if (foundAny == false) {
        std::cout << "Not found" << std::endl;
    } 
}

void findBookByAuthor(std::vector<Book>&library, std::string search) {
    std::string searchAuthor;
    searchAuthor = search;
    bool foundAny = false;
    for (int i = 0; i < library.size(); i++) {
        if (library[i].getAuthor() == searchAuthor) {
        std::cout << "Book found: " << library[i].getTitle() << ", " << library[i].getAuthor() << ", " << library[i].getId() << std::endl;
        foundAny = true;
        }    
    }

    if (foundAny == false) {
        std::cout << "Not found" << std::endl;
    }
}

void performBorrow(std::vector<Book>&library, int id) {
    int searchId;
    int foundId = -1;
    searchId = id;
    for (int i = 0; i < library.size(); i++) {
        if (library[i].getId() == searchId ) {
            foundId = i;
            break;        
        }        
}
    if (foundId > -1) {
        bool success = library[foundId].borrow();
        if (success) {
            std::cout << "Enter your name " << std::endl;
            std::getline(std::cin, library[foundId].borrowerName);
            library[foundId].borrowDate = time(0);
            std::cout << "You have successfully borrowed " << library[foundId].getTitle() << std::endl;
        } else  {
            std::cout << "Sorry, " << library[foundId].getTitle() << " " << "is already checked out." << std::endl;
        }
    } else std::cout << "Not found" << std::endl;  
    
}

void performReturn(std::vector<Book>&library, int id) {
    int searchId;
    int foundId = -1;
    searchId = id;
    

    for (int i = 0; i < library.size(); i++) {
        if (library[i].getId() == searchId ) {
            foundId = i;
            break;        
        }        
}
    if (foundId > -1) {
        bool success = library[foundId].giveBack();
        time_t now = time(0);
        time_t dueDate = library[foundId].borrowDate + 1.21e+6;
        double seconds = difftime(now, dueDate);
        double days = seconds / 86400;
        double fine = days * 50.0;

        if (success) {
            if (now > dueDate) {
                std::cout << "The book is " << days << " days overdue" << std::endl;
                std::cout << "Your fine is KES" << fine << ". " << std::endl;
            } 
            library[foundId].borrowerName = "None";
            library[foundId].borrowDate = 0;
            std::cout << "You have successfully returned " << library[foundId].getTitle() << std::endl;
        } else  {
            std::cout << "Sorry, " << library[foundId].getTitle() << " " << "is already returned." << std::endl;
        }
    } else {
        std::cout << "Not found" << std::endl;  
    }  
    
}

void saveLibrary(std::vector<Book>&library) {
    std::ofstream outFile("library_data.txt");
    if (outFile.is_open()) {
        for (Book book : library) {
            outFile << book.getTitle() << std::endl;
            outFile << book.getAuthor() << std::endl;
            outFile << book.getId() << std::endl;
            outFile << book.getAvailability() << std::endl;
            outFile << book.borrowerName << std::endl;
            outFile << book.borrowDate << std::endl;
        }
    outFile.close();
    std::cout << "Library saved successfully" << std::endl;
    } else {
        std::cout << "File could not be opened" << std::endl;
    }
}

void loadLibrary(std::vector<Book>&library) {
    std::ifstream inFile("library_data.txt");
    std::string tempTitle, tempAuthor, tempName;
    int tempId;
    bool tempAvailability;
    time_t tempDate;

    if (inFile.is_open()) {
        while(std::getline(inFile, tempTitle)) {
            std::getline(inFile, tempAuthor);
            inFile >> tempId;
            inFile >> tempAvailability;
           
            inFile.ignore();

            std::getline(inFile, tempName);
            inFile >> tempDate;

            inFile.ignore();

            Book tempBook(tempTitle, tempAuthor, tempId); 
            
            if (tempAvailability == false) {
                 tempBook.borrow();
                 tempBook.borrowerName = tempName;
                 tempBook.borrowDate = tempDate; 
            }

            library.push_back(tempBook);
        }

     inFile.close();
    }
    
}

int main () {
    std::vector<Book> library;
    loadLibrary(library);
    int choice = 0;
    std::string choiceAuthor;
    std::string choiceTitle;
    int choiceId = 0;
    int borrowId = 0;
    int returnId = 0;
    
    bool running = true;
    while(running) {
    std::cout << "Welcome to the Library of Airobinay " << std::endl;
    std::cout << "1. Add Book(s) " << std::endl;
    std::cout << "2. Search by Author " << std::endl;
    std::cout << "3. Search by Title " << std::endl;
    std::cout << "4. Search by Book ID " << std::endl;
    std::cout << "5. Borrow Book(s) " << std::endl;
    std::cout << "6. Return Book(s) " << std::endl;
    std::cout << "7. Exit " << std::endl;
    std::cout << "Select! " << std::endl;   
    std::cin >> choice;
    std::cin.ignore(1000, '\n'); 

    switch (choice)
    {
    case 1:
        addBooks(library);
        break;

    case 2:
        std::cout << "Please enter the name of the Author " << std::endl;
        std::getline(std::cin, choiceAuthor);
        findBookByAuthor(library, choiceAuthor);
        break;

    case 3:
        std::cout << "Please enter the Title " << std::endl;
        std::getline(std::cin, choiceTitle);
        findBookByTitle(library, choiceTitle);
        break;

    case 4:
        std::cout << "Please enter the ID " << std::endl;
        std::cin >> choiceId;
        findBookById(library, choiceId);
        break;

    case 5:
        std::cout << "Please enter the ID " << std::endl;
        std::cin >> borrowId;
        std::cin.ignore(1000, '\n'); 
        performBorrow(library, borrowId);
        break;

    case 6:
        std::cout << "Please enter the ID " << std::endl;
        std::cin >> returnId;
        performReturn(library, returnId);
        break;

    case 7:
        saveLibrary(library);
        std::cout << "Exitting.. " << std::endl;
        return 0;
    
    default:
        std::cout << "Invalid Choice, Try again please" << std::endl;
        break;
    }

}
    return 0;
 }
   
