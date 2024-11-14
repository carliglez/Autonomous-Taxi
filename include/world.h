/**
 * @file world.h
 * @author carliglez (https://github.com/carliglez)
 * @brief World class header file
 * @version 0.1
 * @date 2024-11-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <fstream>
#include <iostream>
#include <random>
#include "stdio.h"
#include <sstream>
#include <unistd.h>

#include "vehicle.h"
#include "vector.h"
#include "cell.h"

typedef Vector<Vector<Cell>> World_t;

/**
 * @brief Base class World
 * 
 */
class World {
  protected:
    int row;
    int column;
    int size;
    World_t world;
  public:
    World();  // default constructor
    World(int, int);  // constructor by size
    explicit World(int, int, int, int);
    explicit World(int, int, int, int, int);
    virtual ~World(); // destructor

  inline int GetRow() {
    return row; // returns the total number of rows
  }

  inline int GetColumn() {
    return column;  // returns the total number of columns
  }

  inline int GetSize() {
    return size;  // returns the size of the array
  }

  inline Cell GetCell(int i, int j) {
    try {
      return world[i][j];   
    }
    catch(std::exception& e) {
      throw e;
    }   
  }

  inline World_t& GetWorld(void) { return world; } // returns the world by reference

  char GetWorldState(int, int); // returns the “state” of a cell (black or white)
  bool GetWorldValue(int, int); // returns the boolean state of a cell
  int GetWorldX(int, int);
  int GetWorldY(int, int);

  void SetRow(int);
  void SetColumn(int);
  void SetSize(int);
  void SetWorldState(char, int, int); // set the status of a cell
  void SetWorldValue(bool, int, int); // set the boolean value of a cell
  void ToggleWorldValue(int, int);
  void SetWorld(World_t&);

  virtual void ReSize(Vehicle*) = 0;

  void PrintWorld(void);  // prints the matrix alone
  void PrintHorizontalWall(void); // prints a horizontal wall
  void PrintGrid (Vehicle*);
  void PrintSolucion(Vehicle* vehicle);

  bool VehicleOut(Vehicle*);
  void TryPosition(Vehicle*);
};