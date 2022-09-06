#include "headers/program_functions.hpp"

void screen_wipe(){
	//Windows only lol!
	#if defined __WIN64__ || __WIN32__
	system("cls");
	#endif                                                                          
	
	//Linux only lol!
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
    std::cout << "3: Print all prereqs for class\n";
    std::cout << "4: Common prereqs\n";
    std::cout << "5: Print in DFS\n";
    std::cout << "6: Print in BFS\n";
    std::cout << "7: Exit program\n";
    std::cout << "Please enter a number: ";
}