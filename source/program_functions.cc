#include "headers/program_functions.hpp"

void screen_wipe(){
	#if defined __WIN64__ || __WIN32__
	system("cls");
	#endif                                                                          
	
	#if defined __linux__
	if(system("clear")){}
	#endif

	#if defined __MACH__1 || __APPLE__1
	system("clear");
	#endif     
}

void menu() {
    std::cout << "1: Print out the graph\n";
    std::cout << "2: Search for a class\n";
    std::cout << "3: Print all prereqs topologically for a class\n";
    std::cout << "4: Common prereqs between classes\n";
    std::cout << "5: Print a class in DFS\n";
    std::cout << "6: Print a class in BFS\n";
    std::cout << "7: Exit program\n";
    std::cout << "Please enter a number: ";
}