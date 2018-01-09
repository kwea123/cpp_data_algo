# Solving N queen problem more efficiently

In the lecture, we used an array and backtracking method to solve N queen problem for N=8. If you increase N (to around 13,14), you will notice that the program runs very slow. Actually, this is because we systematically test the N rows, and check again and again, for every preceeding rows, if the current queen conflicts with any queen already on the board.

In this homework, we propose a way, using bit manipulations, to decrease the number of places that we need to check.

Look at the following graph for N=8: 

We can eliminate the places by checking three ways :
1.  There is already a queen on the same row.
2.  There is already a queen on the diagonal pointing to the right.
3.  There is already a queen on the diagonal pointing to the left.
4.  Finally, the red cells are possible valid places that we can put the next queen.

Open `AdvancedHW.cpp` and go to method `int countSolutionsRec(int a, int b, int c)`. In the following paragraphs, we will guide you to complete this method.

Since N is small, we can use **binary representations** to represent the valid places.

For example, in the above scenario, we pose `a=11100101` in binary to represent the valid cells after process *1.*

Similarly, we pose `b=01101000` and `c=00001001` to represent the cells prohibited by processes *2.* and *3.*

First of all, it is easy to see the termination condition : when we've filled in the whole board! In this case the program should return 1.

This line, `if (a == 0) return 1;` is already done for you.

Next, we declare a variable `int f;` to store the total number of solutions. This is also done for you.

Exercise 1
-----------------
Now, suppose `a` is not 0, so we have some places to check next.

Given `a, b, c`, what are the rows we need to check next? Declare a variable `int e = ...` and assign it to be that value in binary, using binary operators on `a` and `b` and `c`.

Hint : for the above example, the remaining rows are `e=10000100` (see the red places in *4.*).

Hint : you will need `&`, the bitwise AND operator, and `~`, the bitwise NON operator (flipping 1 and 0).

Now, having the valid places `e`, we need place a queen on one of them, and continue to check the next row. We can check, for example, the **rightmost** valid place first.

The iterations are done in a `while` loop, to check for all configurations until no more is possible, which means `e==0`.

Now, we need to fill in the content in the `while(e!=0)` loop :

Exercise 2
-------------
Declare a variable `int d`, and assign it to be ![2^r](https://latex.codecogs.com/gif.latex?2^r), where *r* is the rightmost non-zero digit of `e`, using binary operators.

Hint : for the above example, `d=00000100`.

Hint : cf. lecture "Advanced/BIT"

Exercise 3
------------
Next, we need to fill in the next row, by calling `countSolutionsRec` recursively.

What's the new `a`, `b`, and `c` right now?

Hint : for the above example, new `a=11100001` since we've filled in the six column by a queen; new `b=1101100`, since the prohibited places are now shifted one place to the left (because it's diagonal); new `c=00000110` similarly.

Hint : you need to use `<<` and `>>`, which allows to shift a number one bit to the left and to the right respectively.

Finally, we need to subtract `d` from `e` to consider the next valid place in the current row. (cf. lecture "Advanced/BIT")

Exercise 4
-----------
The method `countSolutionsRec` is now done. We pass to `int countSolutions2(int n)` which actually computes the total number of solutions for `n` queens by calling `countSolutionsRec(a, b, c)`.

The choice of `b=c=0` is obvious, since initially no place is prohibited (diagonally or even vertically).

As there is no queen initially on the board, `a` should contains all *1*'s, indicating that every place is OK to put a queen.

Fill in `a` now.

Hint : for `N=8`, initially `a=11111111` (eight *1*'s) 

Exercise 5
-----------
Once you're done, in `main()`, run the following :
```
cout<<"Number of solutions for "<<N<<" queens : "<<countSolutions2(N)<<endl;
```

By default, `N=8`, so you should see :
```
Number of solutions for 8 queens : 92
```

Change `N` in *line 5* to `15`, and run the program again. You should see :
```
Number of solutions for 15 queens : 2279184
```

**Attention : if you run N=15 using the naive solution taught in the lecture, your program might not finish in a reasonable time.**

# Answers
Answers can be found in `AdvancedHW.cpp`.
