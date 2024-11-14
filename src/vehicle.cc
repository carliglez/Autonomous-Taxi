/**
 * @file vehicle.cc
 * @author carliglez (https://github.com/carliglez)
 * @brief Vehicle class source file
 * @version 0.1
 * @date 2024-11-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../include/vehicle.h"
#include "../include/world.h"

// constructors
Vehicle::Vehicle() {
  row_pos = 0;
  column_pos = 0;
  direction = 1;
  destination_row = 4;
  destination_col = 7;
}

Vehicle::Vehicle(int i, int j, int direction_, int row_destination,
                 int col_destination, int Wx, int Wy, HeuristicFunction* hf) {
  heuristic_function = hf;
  origin = std::make_pair(i,j);
  destination = std::make_pair(row_destination,col_destination);
  
  WorldSizeX = Wx;
  WorldSizeY = Wy;

  row_pos = i;
  column_pos = j;
  direction = direction_;
  destination_row = row_destination;
  destination_col = col_destination;
}

// destructor
Vehicle::~Vehicle() {
}

// getters and setters
int Vehicle::GetRow(void) { return row_pos; }

int Vehicle::GetColumn(void) { return column_pos; }

int Vehicle::GetDestinationRow(void) { return destination_row; }

int Vehicle::GetDestinationColumn(void) { return destination_col; }

int Vehicle::GetDirection(void) { return direction; }

int Vehicle::GetExpansion(void) { return expansion; }

void Vehicle::AddExpansion(void) { expansion += 1; }

void Vehicle::SetRow(int row) { row_pos = row; }

void Vehicle::SetColumn(int column) { column_pos = column; }

void Vehicle::SetDirection(int next_direction) { direction = next_direction; }

void Vehicle::Update(World_t& coord) {
  try {
    //Turn45(coord.GetWorldValue(GetRow(), GetColumn()));
    //coord.ToggleWorldValue(GetRow(), GetColumn());
    //coord.SetWorldState('X', GetRow(), GetColumn());

    // These functions are now implemented in the Update() invoker method (simulation.cpp/loop)
    // Actually the algorithm runs all at once and does not change the states of the world's positions at X.
    // The solution I see is to then use the constructed path to paint it
    Move(coord); 
  } catch (std::exception& e) {
    throw e;
  }
}

bool Vehicle::isValid(int row, int col) { return (row >= 0) && (row < WorldSizeX) && (col >= 0) && (col < WorldSizeY); }

bool Vehicle::isUnBlocked(World_t& Grid, int row, int col) { return !Grid[row][col].GetValue(); }

bool Vehicle::isDestination(int row, int col, Posicion_t dest) {
  if (row == dest.first && col == dest.second)
    return (true);
  else
    return (false);
}

double Vehicle::calculateHValue(int row, int col, Posicion_t dest) { return GetHeuristicFunction()->operator()(row,col, dest.first, dest.second); }

HeuristicFunction* Vehicle::GetHeuristicFunction(void) { return heuristic_function; }