#include <math.h>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>


/*
 * A* Pathfinding
 *
 * This module was developed to determine the shortest,
 * (i.e. the fastest) path from a to b on a two-dimensional playing field called maze.
 * A distinction is made between walkable and non-walkable paths.
 * For the representation of a maze a two nested vector is used.
 *
 * why the A*-Algorithm is extremely fast:
 * In the following,
 * the path problem is solved as quickly as possible by calculating a score from the estimated distance
 * and the sum of paths already taken,
 * which is used to prioritize the order in which the neighbor nodes are investigated.
 *This also has the effect that A* always knows in which direction the end node is
 * and therefore does not first examine the neighbor away from it, but first all fast paths.




Copyright (c) 2022, LukeProducts
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */




// maze output formatting:
#define STARTSYMBOL 's' // the start Node
#define GOALSYMBOL 'g' // the end Node
#define BRANCH '+' // the Branches between start and end Node
#define BARRIER '#' // Barrier marks non-walkable path
#define PENETRABLE ' ' // marks walkable terrain

// maze input handling (astar()):
#define WALKABLE 0 // walkable terrain is interpreted like
#define NOT_WALKABLE 1 // non-walkable terrain is interpreted like



using namespace std;

using pos_type = vector<int>; // could be array<>, but we are saving ourselves the include statement of <array>

struct Node {
    vector<pos_type> path{}; // saves the path to its origin
    pos_type position{};
    int g = 0, h = 0, f = 0;
    Node(pos_type p): position(p) { // has no parent node
        path.push_back(position); // actual move
    }
    Node(Node c, pos_type p): position{p}{
        for (pos_type pos : c.path)
            path.push_back(pos); // the went way back to the start node
        path.push_back(position); // the actual move action
    }
    bool operator==(Node &other) {
        return position == other.position;
    }

    bool operator<(Node &other) {
        return f < other.f;
    }

    bool operator>(Node &other) {
        return f > other.f;

    }
    /*operator < and > are needed to measure whether
     * an Nodes f-score is good or bad
     * */
};
ostream& operator<<(ostream& os, const Node &out) {
    return os << "Node at (" << out.position[0] << ", " << out.position[1] << "), [" << out.f << " = " << out.g << " + " << out.h << "]";
    /*setting up output routine for Node
     * */
}

class AStarResult {
    vector<vector<int>> defaultmaze{};
public:
    vector<pos_type> path_went{};
    int movements{};
    AStarResult(vector<pos_type> m, vector<vector<int>> old): path_went{m}, defaultmaze{old} {
        movements = path_went.size()-1;
    }

    void print_maze_solution_path() {
        map<int, char> legend{{0, PENETRABLE}, {1, BARRIER}};
        for (int i = 0; i < defaultmaze.size(); i++) {
            for (int j = 0; j < defaultmaze[0].size(); j++) {
                if (std::find(path_went.begin(), path_went.end(), vector<int>{i, j}) != path_went.end()) { // objekt enthalten
                    if (vector<int>{i, j} == path_went[0]) {
                        cout << STARTSYMBOL;
                    }
                    else if (vector<int>{i, j} == path_went[path_went.size()-1]) {
                        cout << GOALSYMBOL;
                    }
                    else {
                        cout << BRANCH;
                    }
                }
                else {
                    cout << legend[defaultmaze[i][j]];
                }
            }
            cout << '\n';
        }
    }
};

Node pop(vector<Node> &heap) {
    /*
     * astar() - intern function to find the node with the snallest f score, which means,
     * it is located potentially nearest to the end Node
     * */
    Node smallest = *min_element(heap.begin(), heap.end()); // get the Node with best chances to reach end note first
    heap.erase(min_element(heap.begin(), heap.end())); // pop this Node out
    return smallest;
}
AStarResult AStar(vector<vector<int>> maze, pos_type start, pos_type end, bool allow_diagonal_moves = false) {

    /*
     * the actual A* algorithm
     *
     *
      vector<vector<int>> maze:

      2-dimensional integer list between 0 and 1, where (if WALKABLE = 0) 0 meaning an possible way
      and 1 (if NOT_WALKABLE = 1) symbolizes an barrier

      maze formatting sample:

      vector<vector<int>> maze{{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                               {1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1},
                               {1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1},
                               {1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
                               {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

      this structure can be created with the functions prepare_maze()
      by an vector of strings, meaning the cols as one object or
      an vector of an vector containing chars




     * */


    // create start and end node
    Node start_node{start}; // has no parent
    start_node.g = start_node.h = start_node.f = 0;
    Node end_node{end}; // has not parent
    end_node.g = end_node.h = end_node.f = 0;

    // init open and closed list
    vector<Node> open_list{};
    vector<Node> closed_list{};

    // push start_node into open list in order to start inspecting its neighbours and spawning child Nodes
    open_list.push_back(start_node);

    /*
     * stop condition is equal to the area of the maze,
     * to be able to figure out whether it is possible to find the solution path or not
     * */
    int outer_iterations = 0;
    int max_iterations = maze[0].size() * maze.size() / 2;

    // which squares to search
    vector<pos_type> adjected_squares{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    if (allow_diagonal_moves) { // if diagonal moves are allowed, we need to look further around the current parent node
        adjected_squares = vector<pos_type>{{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    }

    // loop until end found

    while (!open_list.empty()) {

        outer_iterations++;

        if (outer_iterations > max_iterations) {
            return AStarResult(vector<pos_type>{{}}, maze);
        }

        // get the current Node
        Node current_node = pop(open_list);
        closed_list.push_back(current_node);



        if (current_node.position[0] == end_node.position[0] && current_node.position[1] == end_node.position[1]) { // found the goal
            return AStarResult(current_node.path, maze);
        }

        //generate children

        vector<Node> children{};

        for (pos_type new_position : adjected_squares) { // iterating through every square to cover all possible movement possibilities

            //get nodes new position
            pos_type node_position{current_node.position[0] + new_position[0], current_node.position[1] + new_position[1]};

            // check if in range of maze
            if (node_position[0] > (maze.size()-1) || node_position[0] < 0 || node_position[1] > (maze[maze.size()-1].size()-1) || node_position[1] < 0) {
                continue; // out of range
            }

            // if we're operating within walkable terrain
            if (maze[node_position[0]][node_position[1]] != WALKABLE)
                continue; // barrier at this position

            // create new node to inspect
            Node new_node{current_node, node_position};

            // add our new child to the childrens vector to be examined in the following
            children.push_back(new_node);
        }
        // loop through children
        for (Node child : children) {
            // if child is on the closed list
            vector<Node> bad{};
            for (Node closed_child : closed_list) {
                if (child == closed_child)
                    bad.push_back(closed_child);
            }
            if (!bad.empty())
                continue; // no need to inspect this Node, as we know it's at the wrong path

            // create f, g and h scores
            child.g = current_node.g + 1;
            child.h = ((pow(child.position[0] - end_node.position[0], 2)) +
                       (pow(child.position[1] - end_node.position[1], 2)));
            child.f = child.g + child.h;

            // if child is already in the open list, then
            vector<Node> already{};
            for (Node open_node : open_list) {
                if (child.position == open_node.position && child.g > open_node.g)
                    already.push_back(open_node);
            }
            if (!already.empty())
                continue; // continue with the next child

            open_list.push_back(child);
        }
    }
    cerr << "Could not find path to destination\n"; // A* searched up every possible path and did not find an valid solution
    return AStarResult(vector<pos_type>{{}}, maze);
}



/*
 * I've declared some helpful functions you might need here:
 * */




/*
 prepare_maze converts

    ##########
    #        #
    # ##### ##
    # ##    ##
    # ##  ####
    # ###    #
    #  #  ## #
    ###  ##  #
    ##  ##  ##
    ##########

 to
    1111111111
    1000000001
    1011111011
    1011000011
    1011001111
    1011100001
    1001001101
    1110011001
    1100110011
    1111111111

    in which 1 is NOT_WALKABLE and 0 is WALKABLE

    the converted maze can be passed into the astar() function



 * */

vector<vector<int>> prepare_maze(vector<vector<char>> curr_maze, char barrier = BARRIER) {
    vector<vector<int>> res{};
    for (int i = 0; i < curr_maze.size(); i++) {
        vector<int> tmp{};
        for (int j = 0; j < curr_maze[0].size(); j++) {
            if (curr_maze[i][j] == barrier)
                tmp.push_back(NOT_WALKABLE);
            else
                tmp.push_back(WALKABLE);
        }
        res.push_back(tmp);
    }
    return res;

    /*
     * returns both something like this:
     *
    1111111111
    1000000001
    1011111011
    1011000011
    1011001111
    1011100001
    1001001101
    1110011001
    1100110011
    1111111111

     * */
}
vector<vector<int>> prepare_maze(vector<string> curr_maze, char barrier = BARRIER) { // Overload for vector<string>
    vector<vector<int>> res{};
    for (int i = 0; i < curr_maze.size(); i++) {
        vector<int> tmp{};
        for (int j = 0; j < curr_maze[0].length(); j++) {
            if (curr_maze[i][j] == barrier)
                tmp.push_back(NOT_WALKABLE);
            else
                tmp.push_back(WALKABLE);
        }
        res.push_back(tmp);
    }
    return res;
}


/*
 * findobj:
 * finds an character out of the default maze,
 * where maze needs to be in vector<vector<char>> or vector<string> format, like this:

    ##########
    #        #
    # ##### ##
    # ##    ##
    # ##  ####
    # ###    #
    #  #  ## #
    ###  ##  #
    ##  ##  ##
    ##########

 * the whole maze can by read from the console via readunpreparedmaze(), which returns this type of maze
 * read-in-functions are defined underneath
 *
 * returns pos_type (alias vector<int>),
 * containing the position which is well suited for astar's start as well as end position param
 * */

pos_type findobj(vector<string> maze, char query) {
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[0].length(); j++) {
            if (maze[i][j] == query)
                return pos_type{i, j};
        }
    }
    return pos_type{-1, -1}; // position (-1, -1), if not found the query

    /*
     * returns an pos_type (x, y) position of query as well as its overload below
     * */
}


pos_type findobj(vector<vector<char>> maze, char query) { // Overload for vector<vector<char>>
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[0].size(); j++) {
            if (maze[i][j] == query)
                return pos_type{i, j};
        }
    }
    return pos_type{-1, -1}; // position (-1, -1), if not found the query


}



/*
 * In the following, the functions are defined that can read in an game field
 * and immediately transfer it to the correct format if desired
 *
 *
 * readmaze() reads in the whole maze and converts it directly into the 2 Dim integer-vector, which astar() needs
 *
 * readunpreparedmaze() reads in the whole maze and returns an vector with each row as string,
 * which is usable for cell-by-cell object search findobj(),
 * but must be manually converted using prepare_maze() to use it in astar()
 *
    INPUT SAMPLE:

    10 10        // first 10 = m = rows, second 10 = n = columns
    ##########
    #        #
    # ##### ##
    # ##    ##
    # ##  ####
    # ###    #
    #  #  ## #
    ###  ##  #
    ##  ##  ##
    ##########

     * */



vector<vector<int>> readmaze() {
    int m, n;
    cin >> m; cin >> n;
    vector<string> stringmaze{};

    for (int i = 0; i < m+1; i++) {
        string tmp{};
        getline(cin, tmp);
        if (!tmp.empty())
            stringmaze.push_back(tmp);
    }
    return prepare_maze(stringmaze);
    /*
     * return something like:
    1111111111
    1000000001
    1011111011
    1011000011
    1011001111
    1011100001
    1001001101
    1110011001
    1100110011
    1111111111

     * */
}

vector<string> readunpreparedmaze() {
    int m, n;
    cin >> m; cin >> n;
    vector<string> stringmaze{};

    for (int i = 0; i < m; i++) {
        string tmp{};
        getline(cin, tmp);

        if (tmp.empty()) {
            i--; // user entered empty string
            continue;
        }
        stringmaze.push_back(tmp); // user entered valid sequence of symbols
    }
    return stringmaze;
    /*
     * returns something like:

    ##########
    #        #
    # ##### ##
    # ##    ##
    # ##  ####
    # ###    #
    #  #  ## #
    ###  ##  #
    ##  ##  ##
    ##########


     * */
}

/*
* Here is a sample on how to proceed:

int main{
         vector<string> myunprocessedmaze{   {"##########"},
                                             {"#        #"},
                                             {"# ##### ##"},
                                             {"# ##    ##"},
                                             {"# ##  ####"},
                                             {"# ###    #"},
                                             {"# a#  ## #"},
                                             {"###  ##  #"},
                                             {"##  ##b ##"},
                                             {"##########"}};

         // we could have also have read in this maze from the console with vector<string> readunpreparedmaze();

         vector<int> start_pos = findobj(myunprocessedmaze, 'a'); // findobj finds a for us

         vector<int> end_pos = findobj(myunprocessedmaze, 'b'); //findobj finds b for us

         AStarResult res = AStar(prepare_maze(myunprocessedmaze), start_pos, end_pos); // calculates our results

         res.print_maze_solution_path(); // prints our maze with the went path

         cout << "We went " << res.movements << " blocks\n";

 }

 the console output is

    ##########
    #+++++++ #
    #+#####+##
    #+## +++##
    #+## +####
    #+###++++#
    #+s#  ##+#
    ###  ##++#
    ##  ##g+##
    ##########

*/
