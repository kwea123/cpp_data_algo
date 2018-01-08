# Contructing new labyrinths

Remember in the homework : *Finding Nemo*, we studied the problem of finding a shortest path in a labyrinth.

For example of the following one (Ocean `o1.txt`):
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

If you look closer, you might notice that there's an interesting property of this labyrinth : **All the empty cells are connected by one unique path!**

In today's homework, we propose to generate new labyrinths with such property, by using *disjoint sets*.

The idea is the following : we construct disjoint sets where the elements are the cells in the labyrinth. Initially, each cell is a separated set containing only itself, and there are walls separating all of them. Then we consider every pairs (c1, c2) of adjacent cells (vertically and horizontally) in a random order (can you compute how many pairs are there in function of the size of the labyrinth?). For each pair (c1, c2), we compare the roots of them, if they are equal, then we do nothing; otherwise, merge them and destruct the wall between c1 and c2.

In `DisjointHW.cpp`, we've already included a disjoint set structure taught in the lecture, with struct `Cell`.

We propose to implement the above algorithm progressively.

Exercise 1
-------------------
We need to construct all pairs of cells that are adjacent, and store in the variable `vector<pair<Cell*, Cell*> > pairs`.

Fill in `void constructPairs()`. This method should construct all **different** pairs of cells, store in `vector<pair<Cell*, Cell*> > pairs`.

You can access the cell in position (i, j) by calling `cells[i][j]`, it will return a pointer to that cell.

Exercise 2
------------------
Now we have all pairs of cells, we need to randomly shuffle them in order to generate a different labyrinth each time. We can use *Knuth shuffle* (taught in lecture "Sort") to achieve this.

Fill in `void Knuth()` which will shuffle the pairs in `pairs`.

Hint : cf. lecture "Sort".

Exercise 3
------------------
Now, we can merge the pairs in `pairs` using the disjoint set structure. To store the pairs between which the wall has been destructed, we have a variable `set<pair<pair<int, int>,pair<int, int> > > noWall` that stores the coordinates of these cells. More precisely, if `pp` belongs to `noWall`, then there is no wall between `cells[pp.first.first][pp.first.second]` and `cells[pp.second.first][pp.second.second]`.

Fill in `void constructNoWalls()` which will fill in `noWall` with the coordinates of the pairs of cells (c1, c2) in `pairs` between which the wall has been destructed. 

Finally, in `main()`, run
```
srand(time(NULL));

init();

constructPairs();
Knuth();
constructNoWalls();

printLabyrinth();
```

By default, `N=5` so a labyrinth of size 5 is generated. To print the walls correctly, we expand the size to `2N+1`, but the topology remains the same (you don't need to worry about printing).

You should see a 11x11 labyrinth printed :
```
###########
S   #   # #
# ### ### #
#     #   #
# ### # # #
# #     # #
### # #####
#   # #   #
# ### ### #
# #       E
###########
```
Where `S` means "start" and `E` means "goal".

Your generated labyrinth will very likely be different from this one as it is totally random, but you need to make sure that every two cells are connected by *one unique path*.

You can change `N` in *line 47* to test different labyrinth sizes.

Extra
-------------
uncomment this line in `main()`:
```
//	cout<<noWall.size()<<endl;
```
This line prints out the number of walls that were destructed during the construction of the labyrinth.

If you execute your program again, you will notice that this number remains the same no matter how the labyrinth looks like. In other words, the number of walls is a function of `N`, regardless of the labyrinth is constructed (i.e. regardless of the order of pairs, how we implement union-find, etc.).

Can you find this function?

Finally, prove the property that we keep mentioning : **Every two cells are connected by one unique path**.

Answers
------------
Answers can be found in `DisjointHW_answer.cpp`.
