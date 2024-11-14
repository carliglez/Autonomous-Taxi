/**
 * @file heuristic_function.h
 * @author carliglez (https://github.com/carliglez)
 * @brief HeuristicFunction class header file
 * @version 0.1
 * @date 2024-11-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <cmath>
#include "cell.h"

/**
 * @brief Abstract class HeuristicFunction
 * 
 */
class HeuristicFunction {
  public:
  virtual int operator()(int x_act, int y_act, int x_fin, int y_fin) = 0;
  virtual ~HeuristicFunction() = default; // Virtual destructor
};

/**
 * @brief ManhattanHeuristic class
 * 
 */
class ManhattanHeuristic: public HeuristicFunction{
  public:
  int operator()(int x_act, int y_act, int x_fin, int y_fin){
    return fabs((x_fin-x_act) + (y_fin-y_act));
  }
};

/**
 * @brief EuclideanHeuristic class
 * 
 */
class EuclideanHeuristic: public HeuristicFunction{
  public:
  int operator()(int x_act, int y_act, int x_fin, int y_fin){
    return static_cast<int>(std::round(sqrt(pow((x_fin - x_act), 2) + pow((y_fin - y_act), 2)))); // round to the nearest integer instead of truncating
  }
};