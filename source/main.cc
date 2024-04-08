#include "headers/course_catalog.hpp"

int main() {
    bool running = true;
    do {
        std::cout << "Welcome to CS topolgical sort\n";
        std::cout << "Please pick a school to browse\n";
        std::cout << "1. Fresno State CSCI\n";
        std::cout << "2. CSU Monterey\n"; 
        const int input = read(": ");
        std::string choice; 
        switch (input) {
            case 1:
                choice = "../Files/FSCSCI.txt";
                break;
            case 2:
                choice = "../Files/MCST.txt";
                break;
            case 3:
                choice = "../Files/SJSUCS.txt";
                break;
            case 4: 
                std::cout << "exiting the program..\n";
                running = false;
                break;
            default:
                break;
        }
        if(running) Catalog course_catalog(choice);
    } while(running);

    exit(EXIT_SUCCESS);
}