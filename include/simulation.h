/**
 * @file simulation.h
 * @author carliglez (https://github.com/carliglez)
 * @brief Simulation class header file
 * @version 0.1
 * @date 2024-11-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <ctime>
#include "grid_world.h"

/**
 * @brief Simulation class definition
 * 
 */
class Simulation {
  private:
    int max_iter;
    int curr_iter;
    Vehicle* vehicle;
    World *grid;

  public:
    Simulation();
    Simulation(int);
    Simulation(World*, Vehicle*, int);
    ~Simulation();

    int GetMaxIter(void); // returns the maximum number of iterations
    int GetCurrIter(void);  // returns the current number of iterations

    void SetMaxIter(int);
    void SetCurrIter(int);

    void Loop(void);
    void PrintData(void);
};