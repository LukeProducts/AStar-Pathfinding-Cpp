#include <iostream>
#include "AStar.hpp"
#include <vector>
using namespace std;
using pos_type = vector<int>;



int main() {
    // read in maze from the console
    vector<vector<int>> maze = readmaze();



    // returns AStarResult Class
    AStarResult result = AStar(maze, pos_type{1, 1}, pos_type{5, 5});

    // returns min movements made to get from start_node to end_node
    cout << "A* made " <<  result.movements << " moves to reach (" <<
    end[0] << ", " << end[1] << ")"
    << " from (" << start[0] << ", " << start[1] << ")\n";

    // prints out the whole maze with drawn path
    result.print_maze_solution_path();

    // .path_went variable contains the path went by the fastest node
    vector<pos_type> went_path = result.path_went;

}
