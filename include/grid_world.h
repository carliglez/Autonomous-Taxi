/**
 * @file grid_world.h
 * @author carliglez (https://github.com/carliglez)
 * @brief GridWorld class header file
 * @version 0.1
 * @date 2024-11-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include "world.h"

/**
 * @brief Derived class GridWorld that defines a grid environment where Vehicle objects can move
 * 
 */
class GridWorld: public World {
  using World::World; // inherits all the constructors from the World class

  // this method adjusts a Vehicle's position to keep it within the grid boundaries. If the Vehicle goes out of bounds in GridWorld
  // (by row or column), its position wraps around to the opposite side, creating a 'toroidal world' effect where the edges are connected.
  virtual void ReSize(Vehicle* vehicle){
    while(VehicleOut(vehicle) == true){
      if(vehicle->GetRow() >= world.GetUpperLimit())
        vehicle->SetRow(world.GetLowerLimit());
      else if(vehicle->GetRow() < world.GetLowerLimit()) 
        vehicle->SetRow(world.GetUpperLimit());
      else if (vehicle->GetColumn() >= world[0].GetUpperLimit())
        vehicle->SetColumn(world[vehicle->GetRow()].GetLowerLimit());
      else if(vehicle->GetColumn() < world[0].GetLowerLimit())
        vehicle->SetColumn(world[vehicle->GetRow()].GetUpperLimit());
    }
  }
};