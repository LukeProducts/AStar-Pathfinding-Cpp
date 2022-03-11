#include <iostream>
#include "AStar.hpp"
#include <vector>
using namespace std;
using pos_type = vector<int>;



int main() {
    // read in maze from the console, but not directly convert it into a numeric maze
    vector<vector<int>> maze = readunpreparedmaze();

    /* because it's not already been converted into a numeric maze,
     * you can get the position by finding chars here and don't need to know (and hardcode)
     * the start and end position before
     * */
    pos_type start_pos = findobj(maze, 'a');
    pos_type end_pos = findobj(maze, 'b');

    // returns AStarResult Class
    AStarResult result = AStar(prepare_maze(maze), start_pos, end_pos);

    // returns min movements made to get from start_node to end_node
    cout << "A* made " <<  result.movements << " moves to reach (" <<
    end[0] << ", " << end[1] << ")"
    << " from (" << start[0] << ", " << start[1] << ")\n";

    // prints out the whole maze with drawn path
    result.print_maze_solution_path();

    // .path_went variable contains the path went by the fastest node
    vector<pos_type> went_path = result.path_went;

}
