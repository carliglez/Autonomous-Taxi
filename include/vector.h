/**
 * @file vector.h
 * @author carliglez (https://github.com/carliglez)
 * @brief Vector class header file
 * @version 0.1
 * @date 2024-11-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <vector>
#include <cassert>
#include <iostream>
#include <iomanip>

#include "cell.h"

/**
 * @brief Class template Vector
 * 
 * @tparam T 
 */
template<class T>
class Vector {
  private:
    int index_zero = 0;
    std::vector<T> vector;

  public:
    Vector() {
      //index_zero = 0;
      //vector.resize(2);
    }

    Vector(int min, int max) {
      assert (min < max);
      index_zero = min;
      int sz = max - min;
      vector.resize(sz);
    }

    Vector(const Vector<T>& r_vec) {
      index_zero = r_vec.GetLowerLimit();
      vector = r_vec.vector;
    }

    ~Vector() {}

    T& operator[](int index) {
      if((index >= GetLowerLimit()) &&(index < GetUpperLimit()))
        return vector[index - index_zero];
      else 
        throw std::exception();
    }


    T& operator[](int index) const {
      try {
        assert(index >= GetLowerLimit());
        assert(index <= GetUpperLimit());
        return vector[index - index_zero];
      }
      catch(...) {
        throw std::exception();
      }
    }

    void resize(int sz) { vector.resize(sz); }

    inline std::vector<T>& GetVector() { return vector; }
    
    inline int GetUpperLimit() const { return index_zero + vector.size(); }

    inline int GetLowerLimit() const { return index_zero; }

    inline void SetLowerLimit(int min) { index_zero = min; }

    inline void SetUpperLimit(int max) { index_zero = max; }

    inline int GetSize() const { return GetUpperLimit() - GetLowerLimit(); }

    void push_back(T& x) { vector.push_back(x); }

    bool Empty (void) { return (GetSize() == 0); }

    int Erase(unsigned int iter) { return vector.erase(iter); }

    unsigned int Begin (void) { return vector.begin(); }
};