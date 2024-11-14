/**
 * @file cell.h
 * @author carliglez (https://github.com/carliglez)
 * @brief Cell class header file
 * @version 0.1
 * @date 2024-11-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <utility>

typedef std::pair <int,int> Posicion_t;
typedef std::pair<double, std::pair<int, int> > pPair;

/**
 * @brief Cell class definition
 * 
 */
class Cell {
    private:
    bool is_closed_;  // is it in closed_list?
    bool is_frontier_;  // is it in open_list?
    bool value = false; // free (false) or occupied (true)
    char state = ' '; // X   --> means that the taxi has previously passed through the cell
                      // " " --> means that it is free
                      // O   --> means that there is an obstacle
    int x;  // X coordinate
    int y;  // Y coordinate
    Posicion_t position;

    // parent's coordinates
    int parent_x_;
    int parent_y_;

    double f_;  // estimated cost from start node to target node (g(n) + h(n))
    double h_;  // estimated cost from this node to the target node
    double g_;  // cost from the initial node to this node

    public:
    Cell(int row = 0, int col = 0) {
      x = row;
      y = col;
      position = std::make_pair(row,col);
    }

    ~Cell() {};

    bool GetValue() const { return value; }

    char GetState() const { return state; }

    int GetX() const { return x; }

    int GetY() const { return y; }

    void SetValue(bool new_value) { value = new_value; }

    void SetState(char new_state) { state = new_state; }

    void SetX(int x_) {
      x = x_;
      position.first = x_;
    }

    void SetY(int y_) {
      y = y_;
      position.second = y_;
    }

    void SetPos(int x_, int y_) {
      y = y_;
      x = x_;
      position = std::make_pair(x_,y_);
    }

    bool IsBlocked(void) { return value; }

    // getters and setters of heuristic functions
    void SetF(double f) { f_ = f; }
    
    double GetF(void) const { return f_; }

    void SetG(double g) { g_ = g; }
    
    double GetG(void) const { return g_; }
        
    void SetH(double h) { h_ = h; }

    double GetH(void) const { return h_; }

    int GetPadreX(void) const { return parent_x_; }

    int GetPadreY(void) const { return parent_y_; }

    void SetPadreX(int p) { parent_x_ = p; }

    void SetPadreY(int p) { parent_y_ = p; }
};