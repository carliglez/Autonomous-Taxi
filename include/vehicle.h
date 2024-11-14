/**
 * @file vehicle.h
 * @author carliglez (https://github.com/carliglez)
 * @brief Vehicle class header file
 * @version 0.1
 * @date 2024-11-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <iostream>
#include "stdio.h"
#include <vector>
#include <stack>
#include <bits/stdc++.h>

#include "vector.h"
#include "heuristic_function.h"

typedef Vector<Vector<Cell>> World_t;

/**
 * @brief Base class Vehicle
 * 
 */
class Vehicle {
  public: // previously private
    HeuristicFunction* heuristic_function;

    int row_pos;
    int column_pos;
    int direction;
    int destination_row;
    int destination_col;
    int expansion;

    int WorldSizeX, WorldSizeY;
    std::stack<Posicion_t> Solution_; // Posicion_t type defined in cell.h

    Posicion_t origin, destination;

    virtual void Turn45(bool) = 0;
    virtual void Turn45(char) = 0;

    // apply algorithm A* to reach the destination
    virtual void Move(World_t& MainGrid) = 0; 

  public:
    Vehicle();
    Vehicle(int, int, int, int, int, int, int,  HeuristicFunction*);
    ~Vehicle();

    int GetRow(void); // returns the row in which the taxi is located
    int GetColumn(void);  // returns the column in which the taxi is located
    int GetDirection(void); // returns the direction it has
    int GetDestinationRow(void);  // returns the row in which the destination is located
    int GetDestinationColumn(void); // returns the column in which the destination is located
    int GetExpansion(void);

    int GetWorldX(void) { return WorldSizeX; }
    int GetWorldY(void) { return WorldSizeY; }

    Posicion_t GetOrigin (void) { return origin; }
    Posicion_t GetDestination(void) { return destination; }

    HeuristicFunction* GetHeuristicFunction(void);

    // methods needed for A*
    bool isValid(int row, int col);
    bool isUnBlocked(World_t& Grid, int row, int col);
    bool isDestination(int row, int col, Posicion_t dest);
    //void tracePath(Cell& cellDetails[WorldSizeX][WorldSizeY], Posicion_t dest); // fix

    double calculateHValue(int row, int col, Posicion_t dest);

    void SetRow(int);
    void SetColumn(int);
    void SetDirection(int);
    void AddExpansion(void);

    virtual void Update(World_t& Grid); // makes the turn and the movement according to the box

    virtual void PrintDirection(void) = 0;
};