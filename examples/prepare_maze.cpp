#include <iostream>
#include "AStar.hpp"
#include <vector>
using namespace std;
using pos_type = vector<int>;

vector<string> maze = {
        "###############################",
        "#a          #           #     #",
        "#  ####  #  #  #  #  ####  ####",
        "#        #  #  #     #        #",
        "#  ####  ####  #  #  #######  #",
        "#     #        #  #     #  #  #",
        "######################  #  ####",
        "#  #                 #        #",
        "#  #######  ####  ####  #  #  #",
        "#  #     #  #        #  #  #  #",
        "#  #  #  #  #######  #  #  #  #",
        "#  #  #        #        #  #  #",
        "#  #  #  #######  ####  #######",
        "#     #        #  #           #",
        "#  ####  #  #  #  #  #######  #",
        "#  #     #  #  #  #  #  #  #  #",
        "#  ##########  #  #  #  #  #  #",
        "#           #  #  #  #        #",
        "#  #######  ##########  #######",
        "#        #           #       b#",
        "###############################"
};

// prepare maze to be able to pass it into AStar()
vector<vector<int>> prepared_maze = prepare_maze(maze);


int main() {
    vector<int> start = findobj(maze, 'a');
    vector<int> end = findobj(maze, 'b');



    

    // returns AStarResult Class
    AStarResult result = AStar(prepare_maze(maze), start, end);

    // returns min movements made to get from start_node to end_node
    cout << "A* made " <<  result.movements << " moves to reach (" <<
    end[0] << ", " << end[1] << ")"
    << " from (" << start[0] << ", " << start[1] << ")\n";

    // prints out the whole maze with drawn path
    result.print_maze_solution_path();

    // .path_went variable contains the path went by the fastest node
    vector<pos_type> went_path = result.path_went;

}
