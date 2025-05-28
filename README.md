# BFS and DFS + Mazes!

## What is this project about?

It is a program that takes a maze as input and outputs the path through the maze if there is an exit, or a message indicating that the maze has no solution otherwise.

## Finding a pathway

The program asks if the user wishes to find the exit using either DFS or BFS method. The latter always finding the shortest path between the initial and final position.

The DFS algorithm has a priority order defined by the programmer (me) that is:

> 1. UP
> 2. RIGHT
> 3. BOTTOM
> 4. LEFT

## Illustrative difference between BFS and DFS

The following giff illustrates pretty well the difference between BFS (left) and DFS (right) when comparing them being used as a flood filling algorithm.


![BFS](https://upload.wikimedia.org/wikipedia/commons/b/b6/Wfm_floodfill_animation_queue.gif)
![DFS](https://upload.wikimedia.org/wikipedia/commons/5/5e/Wfm_floodfill_animation_stack.gif)