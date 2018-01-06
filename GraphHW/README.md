# Graph homework : Finding Nemo

In the vast ocean, the sorrowful Nemo is lost! Knowing that the ocean is full of danger, including those dreadful sharks, his dad, Marlin, wants to find him as soon as possible. Can you help him?

Problem
-----------
In the form of a grid of length 41x41, defined in `.txt` files, are the oceans where Nemo is lost.
The following graph shows the ocean described in `o1.txt`.
```
#########################################
#M  #        # # # #       #        # # #
### # #### # # # # # ### ##### ## ### # #
#   # #    # #   #   #   # #    #   #   #
### ### ###### ######### # ###  # # ### #
#          #   #     #   #        # #   #
### ##### #### # ####### ### ###### ### #
# # # # #  #     #   #       #    #     #
# # # # # ## ### # # # # ###### ##### ###
#   # #        #   #   #   #      #     #
# #        # # # #   # # # # #      # # #
# # # ###### # # ### # ### # # #### ### #
# # #      # #     # #     # #  # #   # #
# # ###### ##### ######### # #  # # ### #
#   #      # #         #   #            #
########## # ##### ######### ## ####### #
#   #          #   # #     #      #     #
### # ### #### ##### ### ######## ##### #
#   #   #            #          # #     #
### #####  ##### ########### #### ##### #
#   #   #  #   #       #            # # #
### # ### ## ### ####### # ######## # # #
#     #    #           # #        # #   #
### ### ######## ########### ## # # ### #
#                  #         #  # # #   #
### ### ###### ##### ########## ### ### #
# # #      # # #N  #       # #  #     # #
# ##### # ## ###   # # # # # # ## ### ###
#       #    # ### # # # #          #   #
##### #### # # # # # # ######## # # #####
#       #  #     #         #    # #     #
# # #            # # #   #        # #   #
# # # # ## ########### # # ### ###### ###
# # # #    #   # # #   # # # #  #   #   #
# ### #### # ### # ##### ### ## # # # ###
#   # #          # # #     #      # #   #
# ### ### ###### # # # # #####  # ### ###
# #   #    #     #   # #        # #     #
### ### # ## # ### ###########  ### # # #
#     # #  # #                    # # # #
#########################################
```

The mark `#` indicates a impassable wall.

The mark `N` and `M` means Nemo and his dad Marlin respectively.

The empty cells are free to pass.

Description of the `struct`
-----------------------------
`struct Cell` defines the cells in the ocean.

`struct Ocean` defines the ocean, consisting of `Cell`s.

Each `Cell* c` has at most four neighbors, whose pointer can be obtained by calling either
*  `west(Cell* c)`
*  `south(Cell* c)`
*  `east(Cell* c)`
*  `north(Cell* c)`

`neighbors(Cell* c)` returns a `vector<Cell*>` list of valid neighbors, in the order west->south->east->north.

There are methods returning the nature of cells :
*  `isWall(Cell* c)` returns true if `c` is a wall
*  `isNemo(Cell* c)` returns true if `c` is Nemo
*  `isMarlin(Cell* c)` returns true if `c` is Marlin
*  `isShark(Cell* c)` returns true if `c` is a shark

For the following exercises, we will use the following methods to mark a `Cell`:

*  `void setMark(Cell* c)` to set `c` with value `0`.
*  `void setMark(Cell* c, int val)` to set `c` with value `val`.
*  `void unMark(Cell* c)` to unset the value of `c` (by default `-1`).
*  `bool isMarked(Cell* c)` returns true if `c` is marked (with value `>=0`)
*  `int getMark(Cell* c)` returns the mark of `c`.

Finally, to visualize the (marked) ocean, call `printMarked()`.

# Part 1

Exercise 1
------------
Complete the method `bool Ocean::dfsFrom(Cell* c)` which returns `true` if there exists a path from `c` to Nemo by passing only by the cells not yet marked, using a DFS approach.

Algorithm : 
1.  When Marlin arrives at a cell, he marks it with value `0`.
2.  When Marlin quits a cell because it leads to a dead end, marks it with value `deadEndColor`.
3.  The final path is marked with `pathColor`.

Code using recursive calls: 
*  Stopping conditions:
   1.  If we found Nemo, return `true`.
   2.  If we encounter a wall or a cell already visited, return `false`.
*  Recursion: We mark the current cell with `0`, and run a DFS on its neighbors.
   *  If one of its neighbors returns `true`, which means there is a path from that neighbor to Nemo, we should mark the current cell with `pathColor` and return `true`.
   *  Otherwise, it means none of its neighbors lead to Nemo, so we mark the cell with `deadEndColor` and return `false`.

Exercise 2
-----------
Complete the method `void Ocean::dfs()` which makes use of `bool Ocean::dfsFrom(Cell* c)`.

In `main`, run
```
Ocean o = readFile("o1.txt");
......
/* DFS */
o.dfs();
o.printMarked();
```
to see the result. The result should be the same as `o1_dfs.txt`.

Exercise 3
----------
Complete the method `void Ocean::bfs()` which implements a BFS approach to mark the cells (with `pathColor`). You will need to include a proper data structure.

In `main`, run
```
Ocean o = readFile("o1.txt");
......
/* BFS */
o.bfs();
o.printMarked();
```
to see the result. The result should be the same as `o1_bfs.txt`.

Exercise 4
----------
Complete the method `void Ocean::bfsWithDistance()` which, in addition to the BFS, computes the distance to Nemo.
Hint : modify just a little `void Ocean::bfs()` by marking the cells with the distances instead of `pathColor`.

In `main`, run
```
/* BFS WITH DISTANCE */
o.bfsWithDistance();
cout<<"Distance to Nemo : "<<o.getMark(o.nemo)<<endl;
```
to see the result. The result should be `Distance to Nemo : 104`.

Exercise 5
---------
Complete the method `void Ocean::bfsWithShortestPath()` which computes the shortest path to Nemo. As mentioned in the lecture, the method is to remember the direction from which the cell is reached.

More precisely, mark the cells with the direction from which it is reached, making use of
```
const int WEST = 1, SOUTH = 2, EAST = 3, NORTH = 4;
```

At the end of this method, you will need to call `void Ocean::backTrack()` which backtracks the path. I.e. this time starting from Nemo, going all the way back to Marlin by following the marks, and set these cells with value `pathColor`.

Complete the method `void Ocean::backTrack()`.

In `main`, run
```
Ocean o = readFile("o1.txt");
......
/* BFS WITH SHORTEST PATH */
o.bfsWithShortestPath();
o.printMarked();
```
to see the result. The result should be the same as `o1_bfs_shortest.txt`.

# Part 2
Fearful sharks appear! Run!!

In oceans described in `o2.txt` and `o3.txt`, there are SHARKS, indicated with symbol `S`.

The following graph shows the ocean described in `o2.txt`. Notice a shark at the bottom of the ocean.
```
#########################################
#M  #        # # # #       #        # # #
### # #### # # # # # ### ##### ## ### # #
#   # #    # #   #   #   # #    #   #   #
### ### ###### ######### # ###  # # ### #
#          #   #     #   #        # #   #
### ##### #### # ####### ### ###### ### #
# # # # #  #     #   #       #    #     #
# # # # # ## ### # # # # ###### ##### ###
#   # #        #   #   #   #      #     #
# #        # # # #   # # # # #      # # #
# # # ###### # # ### # ### # # #### ### #
# # #      # #     # #     # #  # #   # #
# # ###### ##### ######### # #  # # ### #
#   #      # #         #   #            #
########## # ##### ######### ## ####### #
#   #          #   # #     #      #     #
### # ### #### ##### ### ######## ##### #
#   #   #            #          # #     #
### #####  ##### ########### #### ##### #
#   #   #  #   #       #            # # #
### # ### ## ### ####### # ######## # # #
#     #    #           # #        # #   #
### ### ######## ########### ## # # ### #
#                  #         #  # # #   #
### ### ###### ##### ########## ### ### #
# # #      # # #N  #       # #  #     # #
# ##### # ## ###   # # # # # # ## ### ###
#       #    # ### # # # #          #   #
##### #### # # # # # # ######## # # #####
#       #  #     #         #    # #     #
# # #            # # #   #        # #   #
# # # # ## #######S### # # ### ###### ###
# # # #    #   # # #   # # # #  #   #   #
# ### #### # ### # ##### ### ## # # # ###
#   # #          # # #     #      # #   #
# ### ### ###### # # # # #####  # ### ###
# #   #    #     #   # #        # #     #
### ### # ## # ### ###########  ### # # #
#     # #  # #                    # # # #
#########################################
```

This time, to secure the life, instead of searching for a shortest path, Marlin decides to look for a path that **passes by the minimum number of sharks**.

To achieve this, we can still use BFS, but with a modified data structure. We will use `deque` (*double-ended queue*). A `deque` is a queue where we can add and access elements from both ends. 

The idea is simple, when we add new cells to this queue, we look at the nature of the cell :
*  If it is a normal cell, add it **to the front** of the queue
*  If it is a shark, add it **to the end** of the queue
*  Pop the first cell of the queue for the next visit

In this way, we can guarantee that the shark cells are visited all the way to the end.

Exercise 6
-----------
Complete the method `void Ocean::avoidSharks()`.

Hint : add just a couple of lines in `void Ocean::bfsWithShortestPath()` and you're done! 

In `main`, run
```
Ocean o = readFile("o2.txt");
......
o.avoidSharks();
o.printMarked();
```
and
```
Ocean o = readFile("o3.txt");
......
o.avoidSharks();
o.printMarked();
```
to see the results. The results should be the same as `o2_avoid.txt` and `o3_avoid.txt`.

# Answers
Answers can be found in `GraphHW_answer.cpp`.
