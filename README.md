# A* Pathfinding

This module was developed to determine the shortest,
(i.e. the fastest) path from a to b on a two-dimensional playing field called maze.
A distinction is made between walkable and non-walkable paths.
For the representation of a maze a two nested vector is used.



<img src="https://user-images.githubusercontent.com/73026669/157827590-874d57e2-23e4-49e6-9162-1b4d2be29f89.gif" align="left" width="700x"/>







### How does the A* - Algorithm works?

It is started with the help of a specified labirynth and 
a start and end node, of which only the position is known at the beginning of the runtime. 
Now all possible paths around this node are examined, 
and these then again just like the start node until a node arrives at the position of the end node. 
Then the fastest possible way from start to end is explored, i.e. the best node to go, and then output.


<br><br>


#### why the A*-Algorithm is extremely fast:
<img src="https://upload.wikimedia.org/wikipedia/commons/8/85/Weighted_A_star_with_eps_5.gif" align="left" width="200px"/>

The path problem is solved as quickly as possible by calculating a score from the estimated distance
and the sum of paths already taken,
which is used to prioritize the order in which the neighbor nodes are investigated.
This also has the effect that A* always knows in which direction the end node is
and therefore does not first examine the neighbor away from it, but first all fast paths.

The formula used for this is:

**f(n) = g(n) + h(n)**

<br>

**n**

> is the Node Object itself


<img src="https://media.geeksforgeeks.org/wp-content/uploads/a_-search-algorithm-5.png" align="right" width="200px" />

**g(n)**
> Is the estimate of how far n is from the end node
> 
> **(current_cell.x – goal.x)^2 + (current_cell.y – goal.y)^2** 



**h(n)**
> Is the number of travelled path units from the 
> start node to the current position of n


**f(n)**
> the sum of both **g(n)** and **h(n)**

> is a score value with which we select and 
> examine from different nodes the one with the best score, 
> with the greatest probability of being the fastest path, which makes the code much faster, 
> because otherwise the graph would not look like above, but like this:
> 

 
<img src="https://miro.medium.com/max/420/1*2jRCHqAbTCY7W7oG5ntMOQ.gif" align="left" width="200px" />

much slower search, <br>
because the algorith has no clue, <br>
in which direction to go first, <br>
so it goes in each direction with <br>
the same priority

<br><br><br><br>

## Example:
```
############################### -----------------------------------> ###############################
#a  #   # #         #   #     # -----------------------------------> #s++#   # #++++++++#   #     #
### # ### # ####### # ### ##### -----------------------------------> ###+# ### #+#######+# ### #####
# #       # #     #     # #   # -----------------------------------> # #+++++++#+#     #+++  # #   #
# ##### # # ##### ### ### ### # -----------------------------------> # ##### #+#+##### ###+### ### #
#   # # #     #         # #   # -----------------------------------> #   # # #+++  #    +++  # #   #
### # # ### ####### ##### # ### -----------------------------------> ### # # ### #######+##### # ###
#   #   # #     #           # # -----------------------------------> #   #   # #     #  +++++++  # #
# ### ### ### # ### ##### ### # -----------------------------------> # ### ### ### # ### #####+### #
#       #   # # #   #         # -----------------------------------> #       #   # # #   #    +++  #
### ####### ### ########### # # -----------------------------------> ### ####### ### ###########+# #
#   #       # #   # # #     # # -----------------------------------> #   #       # #   # # #  +++# #
### # ### # # # ### # # # ### # -----------------------------------> ### # ### # # # ### # # #+### #
#       # # # #       # # # # # -----------------------------------> #       # # # #       # #+# # #
# # ##### # # ##### # ### # ### -----------------------------------> # # ##### # # ##### # ###+# ###
# #     # # #   #   # #   #   # -----------------------------------> # #     # # #   #   # #  +#   #
### ######### ### ####### # ### -----------------------------------> ### ######### ### #######+# ###
#   #   # #   #   #   # #     # -----------------------------------> #   #   # #   #   #   # #+++++#
# ### # # # ##### ### # ##### # -----------------------------------> # ### # # # ##### ### # #####+#
#     #         #           #b# -----------------------------------> #     #         #           #g#
############################### -----------------------------------> ###############################


```




## included Features

<img src="https://user-images.githubusercontent.com/73026669/157855414-6f6f2fd1-7da4-4eba-8cf6-b1b66ccb12d9.jpg" align="left" />
<h3> AStarResult - Class </h3>
The main AStar() function returns a AStarResult class-object which provides the hole path went, 
the total amount of moves, 
done as well as a method to print out the hole maze




<br><br><br><br><br><br><br><br><br><br>
possible output:

```
A* made 64 moves to reach (19, 29) from (1, 1)
###############################
#s+++++++   # +++       #     #
#  #### +#  # +#+ #  ####  ####
#       +#  # +#++++ #        #
#  #### +#### +#  #+ #######  #
#     # +++++++#  #++++ #  #  #
######################+ #  ####
#  #                 #+       #
#  #######  ####  ####+ #  #  #
#  #     #  #        #+ #  #  #
#  #  #  #  #######  #+ #  #  #
#  #  #        #      + #  #  #
#  #  #  #######  ####++#######
#     #        #  #    ++++++ #
#  ####  #  #  #  #  #######+ #
#  #     #  #  #  #  #  #  #+ #
#  ##########  #  #  #  #  #+ #
#           #  #  #  # ++++++ #
#  #######  ########## +#######
#        #           # ++++++g#
###############################
``` 

<br><br>
-----------------------------------------------------------------------------------

<img src="https://user-images.githubusercontent.com/73026669/157859667-9cb5c26d-812c-4666-a14a-ffa3284d3189.jpg" align="left" />
<h3> prepare maze - function </h3>

The prepare function converts a maze consisting out of <br>
__barriers__ (f.ex. '#') and __walkable terrain__ (f.ex. ' ') <br>
is converted to a maze out of zeroes and ones, <br>
the ones represent the not walkable terrain and the zeroes the walkable terrain by default. <br><br>
All this settings could be adjusted in the __#define__ statements at the beginning of this package.<br><br>

```
########## -----> 1111111111
#        # -----> 1000000001
# ##### ## -----> 1011111011
# ##    ## -----> 1011000011
# ##  #### -----> 1011001111
# ###    # -----> 1011100001
#  #  ## # -----> 1001001101
###  ##  # -----> 1110011001
##  ##  ## -----> 1100110011
########## -----> 1111111111
```
