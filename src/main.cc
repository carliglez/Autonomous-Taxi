/**
 * @file main.cc
 * @author carliglez (https://github.com/carliglez)
 * @brief Main program file
 * @version 0.1
 * @date 2024-11-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../include/simulation.h"
#include "../include/vector.h"
#include "../include/taxi4.h"
#include "../include/taxi8.h"

/**
 * @brief Auxiliary function for printing program information
 * 
 */
void printInfo() {
  std::cout << "\n- Welcome, this program is in charge of generating a simulation." << std::endl;;
  std::cout << " You will be in charge of selecting the random, manual or file-based resource generation mode." << std::endl;
  std::cout << " In this way, an environment will be generated where an autonomous taxi (🚖) must be able to reach the destination location (🚩) " << std::endl;
  std::cout << " in the most efficient way possible according to a heuristic function.\n\n";
}

/**
 * @brief Main function
 * 
 * @return int
 */
int main(void /* int argc, char* argv[]*/) {
  int row_min, row_max, col_min, col_max, iterations, direction, vehicle_row;
  int vehicle_col, opt, vehicle_chosen, destination_row, destination_col, obstacle_chosen = -1;

  std::cout << "**** Enter 0 to print the program information first ****\n";
  std::cout << "**** Enter 1 to start execution immediately         ****\n";
  std::cout << "Enter 0 or 1: ";
  std::cin >> opt;
  while ((opt != 0) && (opt != 1)) {
    std::cout << "ERROR: please, enter 0 or 1: ";
    std::cin >> opt;
  }

  if (opt == 0) {
    printInfo();  // calling the auxiliary function
  }

  std::cout << "Enter the desired WIDTH: ";
  std::cin >> row_max;
  while (row_max < 0) {
    std::cout << "ERROR: value less than 0" << std::endl << "Enter the desired WIDTH: ";
    std::cin >> row_max;
  }

  row_min = 0;
  std::cout << "Enter the desired HEIGHT: ";
  std::cin >> col_max;
  while (col_max < 0) {
    std::cout << "ERROR: value less than 0" << std::endl << "Enter the desired HEIGHT: ";
    std::cin >> col_max;
  }

  col_min = 0;
  std::cout << "- Obstacle generation:\n";
  std::cout << "0. Automatically generate obstacles?\n";
  std::cout << "1. Enter them manually?\n";
  std::cout << "2. Read a file with the corresponding obstacles?\n";
  std::cout << "Enter the desired option: ";
  std::cin >> obstacle_chosen;
  while ((obstacle_chosen != 0) && (obstacle_chosen != 1) && (obstacle_chosen != 2)) {
    std::cout << "ERROR: value not equal to 0, 1, or 2" << std::endl << "Enter the desired value: ";
    std::cin >> obstacle_chosen;
  }

  World* world = new GridWorld(row_min, row_max, col_min, col_max, obstacle_chosen);
  Vehicle* vehicle;

  std::cout << "\nIs the taxi 4-way or 8-way? Please, enter 4 or 8: ";
  std::cin >> vehicle_chosen;
  while ((vehicle_chosen != 4) && (vehicle_chosen != 8)) {
    std::cout << "ERROR: value not equal to 4 or 8 " << std::endl << "Enter the desired value: ";
    std::cin >> vehicle_chosen;
  }

  // X coordinate of the taxi
  std::cout << "Enter the X coordinate of the taxi: ";
  std::cin >> vehicle_col;
  while ((vehicle_col < 0) || (vehicle_col > col_max * 2 - 1)) {
    std::cout << "ERROR: the X coordinate is not within the initialized world" << std::endl;
    std::cout << "Enter an existing coordinate between " << 0 << " and " << col_max * 2 - 1 << ": ";
    std::cin >> vehicle_col;
  }
  vehicle_col += col_min;

  // Y coordinate of the taxi
  std::cout << "Enter the Y coordinate of the taxi: ";
  std::cin >> vehicle_row;
  while ((vehicle_row < 0) || (vehicle_row > row_max * 2 - 1)) {
    std::cout << "ERROR: the Y coordinate is not within the initialized world" << std::endl;
    std::cout << "Enter an existing coordinate between " << 0 << " and " << row_max * 2 - 1 << ": ";
    std::cin >> vehicle_row;
  }
  vehicle_row += row_min;

  // X coordinate of the destination
  std::cout << "Enter de X coordinate of the destination: ";
  std::cin >> destination_col;
  while ((destination_col < 0) || (destination_col > col_max * 2 - 1)) {
    std::cout << "ERROR: the X coordinate is not within the initialized world" << std::endl;
    std::cout << "Enter an existing coordinate between " << 0 << " and " << col_max * 2 - 1 << ": ";
    std::cin >> destination_col;
  }
  destination_col += col_min;

  // Y coordinate of the destination
  std::cout << "Enter de Y coordinate of the destination: ";
  std::cin >> destination_row;
  while ((destination_row < 0) || (destination_row > row_max * 2 - 1)){
    std::cout << "ERROR: the Y coordinate is not within the initialized world" << std::endl;
    std::cout << "Enter an existing coordinate between " << 0 << " and " << row_max * 2 - 1 << ": ";
    std::cin >> destination_row;
  }
  destination_row += row_min;

  // Heuristic Function
  HeuristicFunction* hf;
  char opcion;
  std::cout << "Enter the desired Heuristic Function ([E]uclidean | [M]anhattan): ";
  std::cin  >> opcion;
  while ((opcion != 'E') && (opcion != 'M')) {
    std::cout << "ERROR: value not equal to 'E' (Euclidean) or 'M' (Manhattan)" << std::endl << "Enter the desired value: ";
  }
  if (opcion == 'M')
    hf = new ManhattanHeuristic;
  else if (opcion == 'E')
    hf = new EuclideanHeuristic;
  else
    std::cout << "ERROR: value not equal to E or M" << std::endl;

  if (vehicle_chosen == 4)
    vehicle = new Taxi4(vehicle_row, vehicle_col, direction, destination_row, destination_row, row_max, col_max, hf);
  else if (vehicle_chosen == 8)
    vehicle = new Taxi8(vehicle_row, vehicle_col, direction, destination_row, destination_row, row_max, col_max, hf);
  else
    std::cout << "ERROR: value not equal to 4 or 8" << std::endl;

  // Simulation
  Simulation simulation(world, vehicle, iterations);
  simulation.Loop();

  return 0;
}