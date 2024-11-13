# Determination of the Optimal Trajectory for an Autonomous Taxi

## Summary

This project addresses the problem of finding an optimal path for a taxi, which can move in 4 or 8 directions, from a starting point to a destination. The solution is achieved through the use of a search algorithm, which works with two distinct heuristic functions to compare and find the best solution for each case. The implemented algorithm is A*, using both the Manhattan and Euclidean distance heuristics. After evaluating different scenarios, it was determined that using the Manhattan distance heuristic with a taxi capable of 8 movements provides the best results for solving the problem.

## Introduction

The problem consists of a rectangular environment where an autonomous taxi can move in at least four directions per move. The environment contains obstacles that the taxi cannot pass through. The objective is to find the optimal path from a starting cell to a destination cell while avoiding obstacles and minimizing the number of moves.

## Problem Formulation

In the context of Artificial Intelligence, to solve search problems in the state space, we need to define the following four essential elements:

- **Initial State**: The starting configuration of the environment, including the taxi's position and the locations of obstacles.
- **Final State**: The solution, represented by the full path taken by the taxi, including the obstacles that make up the environment. In case the taxi can't reach the destination, the path and the taxi's final position are considered part of the final state.
- **Operators**: The possible movements of the taxi. With 4 directions (north, south, east, west), there are 4 operators. With 8 directions (including diagonals), there are 8 operators.
- **States**: All possible configurations of the environment, formed by applying movements starting from the initial state. For example, if the taxi is in a given environment and moves north, the new state will be the environment with the taxi's position updated to the north.

## Simulation Environment

The program provides a text-based interface, offering a fast way to input data and display results. This approach compensates for the slight loss in visual comfort and the manual input of obstacles. The interface is clear, intuitive, and provides error messages to handle any situation.

## Search Algorithm

The A* algorithm is implemented as the search method. A* is a heuristic search algorithm that uses a best-first search strategy to avoid expanding costly paths. It labels nodes with an evaluation function to determine the optimal path.

The two heuristics used are:

- **Manhattan Distance**: Suitable when obstacles are present, as it calculates the shortest path in a grid where diagonal moves are not allowed.
- **Euclidean Distance**: Represents the straight-line distance between two points and is ideal when there are no obstacles.

The A* algorithm expands nodes from an open list (nodes that haven't been explored) and places explored nodes in a closed list. Nodes are expanded based on their evaluation (f = g + h), where:

- `g` is the cost to reach the current node,
- `h` is the heuristic estimate of the distance to the goal.

## Experimental Evaluation

The evaluation results indicate the following key findings:

1. Execution time is lower with the Manhattan distance heuristic, regardless of the taxi's movement capabilities or the environment size.
2. When there are no obstacles (0% obstacles), both heuristics find an optimal path with the same length. However, the Manhattan heuristic expands fewer nodes, especially with an 8-direction vehicle.
3. The number of expanded nodes is significantly lower with the 8-direction vehicle, leading to faster execution compared to the 4-direction vehicle.
4. The 8-direction vehicle performs better in environments with obstacles, finding a path in more cases than the 4-direction vehicle when the obstacle density is 50%.
5. The number of expanded nodes increases exponentially with environment size for the 4-direction vehicle, while the 8-direction vehicle expands nodes at approximately double the rate.
6. Overall, the optimal path length is similar for both heuristics. However, the Manhattan distance heuristic expands fewer nodes, which results in a shorter execution time.

The combination of an 8-direction taxi and the Manhattan distance heuristic yields the best solution in terms of pathfinding efficiency, regardless of the environment size. Additionally, the algorithm tends to prioritize diagonal moves when possible, especially when the starting position is in the top-left corner and the destination is in the bottom-right corner.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
