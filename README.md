# A* Pathfinding

This module was developed to determine the shortest,
(i.e. the fastest) path from a to b on a two-dimensional playing field called maze.
A distinction is made between walkable and non-walkable paths.
For the representation of a maze a two nested vector is used.






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

#### why the A*-Algorithm is extremely fast:
In the following,
the path problem is solved as quickly as possible by calculating a score from the estimated distance
and the sum of paths already taken,
which is used to prioritize the order in which the neighbor nodes are investigated.
This also has the effect that A* always knows in which direction the end node is
and therefore does not first examine the neighbor away from it, but first all fast paths.



[![Astar_progress_animation](https://user-images.githubusercontent.com/73026669/157831494-b4712aac-9fbb-4c13-a3ce-7e361627360e.gif)](https://en.wikipedia.org/wiki/A*_search_algorithm)

![maze](https://user-images.githubusercontent.com/73026669/157827590-874d57e2-23e4-49e6-9162-1b4d2be29f89.gif)

