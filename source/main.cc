#include "headers/Graph.hpp"
#include "headers/program_functions.hpp"

using namespace std;

int main() {
    Graph current_graph("Graphs/fresnoState.dat");
    bool in_menu = true;
    while(in_menu) {
        int input = 0;
        std::string course, course1; 
        menu();
        cin >> input;
        while(true) {
            if(cin.fail()) {
                cin.clear();
                cin.ignore();
                screen_wipe();
                menu();
                cin >> input;
            }
            else {
                break;
            }
        }
        switch (input)
        {
        case 1:
            screen_wipe();
            cout << current_graph << endl;
            break;
        case 2:
            cin >> course; 
            screen_wipe();
            if(current_graph.hash_query(course)) {
                cout << current_graph[current_graph.hash_get(course)] << endl;
                cout << endl;
            } else {
                COURSE_NOT_FOUND;
            }
            break;
        case 3:
            cin >> course; 
            screen_wipe();
            if(current_graph.hash_query(course)) {
                cout << current_graph.print_all_prereqs(course) << endl;
                cout << endl;
            } else {
                COURSE_NOT_FOUND;
            }
            break;
        case 4:
            cin >> course >> course1; 
            screen_wipe();
            if(!current_graph.hash_query(course)) {
                COURSE_NOT_FOUND;
                break;
            }
            if(!current_graph.hash_query(course1)) {
                COURSE_NOT_FOUND;
                break;
            }
            cout << current_graph.print_common_prereqs(course,course1) << endl;
            cout << endl;
            break;
        case 5:
            cin >> course; 
            screen_wipe();
            cout << endl;
            current_graph.print_DFS(course);
            cout << endl;
            break;
        case 6:
            cin >> course; 
            screen_wipe();
            cout << endl;
            current_graph.print_BFS(course);
            cout << endl;
            break;
        case 7:
            in_menu = false;
            break;
        default:
            break;
        }
    }
    return 0;
}