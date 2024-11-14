/**
 * @file taxi8.h
 * @author carliglez (https://github.com/carliglez)
 * @brief Taxi8 class header file
 * @version 0.1
 * @date 2024-11-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include "vehicle.h"

/**
 * @brief Derived class Taxi8
 * 
 */
class Taxi8: public Vehicle {
  public:
  Taxi8(int i, int j, int direction_, int row_destination,
        int col_destination, int Wx, int Wy, HeuristicFunction* hf): 
        Vehicle(i, j, direction_, row_destination, col_destination, Wx, Wy, hf) {}

  virtual void Turn45(char colour);

  virtual void Turn45(bool colour);

  // implements the A* algorithm
  virtual void Move(World_t& coord);

  virtual void PrintDirection(void);
};