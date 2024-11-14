/**
 * @file taxi8.cc
 * @author carliglez (https://github.com/carliglez)
 * @brief Taxi8 class source file
 * @version 0.1
 * @date 2024-11-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../include/taxi8.h"

void Taxi8::Turn45(char colour) {
  if(colour == ' ') { // if the box is white
    if((direction <= 8) && (direction > 1)) // left turn
      direction--;
    else if(direction == 1)
      direction = 8;
    else std::cout << "ERROR, direction = " << direction << std::endl;
  }
  else if(colour == 'X') {  // if the box is black
    if((direction >= 1) && (direction < 8)) // right turn
      direction++;
    else if (direction == 8)
      direction = 1;
    else std::cout << "ERROR, direction = " << direction << std::endl;
  }
}

void Taxi8::Turn45(bool colour) {
  if(colour == false) {  // if the box is white
    if((direction <= 8) && (direction > 1)) // left turn
      direction--;
    else if(direction == 1)
      direction = 8;
    else std::cout << "ERROR, direction = " << direction << std::endl;
  }
  else {
    if((direction >= 1) && (direction < 8)) // right turn
      direction++;
    else if (direction == 8)
      direction = 1;
    else std::cout << "ERROR, direction = " << direction << std::endl;
  }
}

void Taxi8::PrintDirection(void) { // prints arrows to represent the directions to be taken
  int direction = GetDirection();
  switch(direction) {
    case 1: std::cout << "\u2191";  // unicode character 'UPWARDS ARROW'
    break;

    case 2: std::cout << "\u2197";  // unicode character 'NORTH EAST ARROW
    break;

    case 3: std::cout << "\u2192";  // unicode character 'RIGHTWARDS ARROW'
    break;

    case 4: std::cout << "\u2198";  // unicode character 'SOUTH EAST ARROW'
    break;

    case 5: std::cout << "\u2193";  // unicode character 'DOWNWARDS ARROW'
    break;

    case 6: std::cout << "\u2199";  // unicode character 'SOUTH WEST ARROW'
    break;

    case 7: std::cout << "\u2190";  // unicode character 'LEFTWARDS ARROW'
    break;

    case 8: std::cout << "\u2196";  // unicode character 'NORTH WEST ARROW'
    break;
  }
}

void Taxi8::Move(World_t& Grid) {
  //Vector<Vector<Cell>> Grid = coord.GetWorld(); 
  // if the source is out of range
  if (isValid(origin.first, origin.second) == false) {
    std::cout << "Source is invalid\n";
    return;
  }

  // if the destination is out of range
  if (isValid(destination.first, destination.second) == false) {
    std::cout << "Destination is invalid\n";
    return;
  }

  // either the source or the destination is blocked
  /*if (isUnBlocked(Grid, origin.first, origin.second) == false
    || isUnBlocked(Grid, destination.first, destination.second) == false) {
    std::cout << "Source or the destination is blocked\n";
    return;
  }*/

  // if the destination cell is the same as source cell
  if (isDestination(origin.first, origin.second, destination) == true) {
    printf("We are already at the destination\n");//
    return;
  }

  // create a closed list and initialise it to false which means that no cell has
  // been included yet This closed list is implemented as a boolean 2D array
  bool closedList[WorldSizeX][WorldSizeY];
  memset(closedList, false, sizeof(closedList));

  // declare a 2D array of structure to hold the details of that cell
  Cell cellDetails[WorldSizeX][WorldSizeY];

  int i, j;
  for (i = 0; i < WorldSizeX; i++) {
    for (j = 0; j < WorldSizeY; j++) {
      cellDetails[i][j].SetF(FLT_MAX);
      cellDetails[i][j].SetG(FLT_MAX);
      cellDetails[i][j].SetH(FLT_MAX);
      cellDetails[i][j].SetPadreX(-1);
      cellDetails[i][j].SetPadreY(-1);
    }
  }

  // initialising the parameters of the starting node
  i = origin.first, j = origin.second;
  cellDetails[i][j].SetF(0.0);
  cellDetails[i][j].SetG(0.0);
  cellDetails[i][j].SetH(0.0);
  cellDetails[i][j].SetPadreX(i);
  cellDetails[i][j].SetPadreY(j);
  std::set<pPair> openList;

  // put the starting cell on the open list and set its 'f' as 0
  openList.insert(std::make_pair(0.0, std::make_pair(i, j)));

  // we set this boolean value as false as initially the destination is not reached.
  bool foundDest = false;

  while (!openList.empty()) {
    pPair p = *openList.begin();

    // remove this vertex from the open list
    openList.erase(openList.begin());

    // add this vertex to the closed list
    i = p.second.first;
    j = p.second.second;
    closedList[i][j] = true;

    double gNew, hNew, fNew;

    //----------- 1st Successor (North) ------------

    // only process this cell if this is a valid one
    if (isValid(i - 1, j) == true) {
      // if the destination cell is the same as the current successor
      if (isDestination(i - 1, j, destination) == true) {
        // set the Parent of the destination cell
        cellDetails[i - 1][j].SetPadreX(i);
        cellDetails[i - 1][j].SetPadreY(j);
        printf("The destination cell is found\n");
        foundDest = true;
        //tracePath(cellDetails, destination);

        std::cout << "\nThe path is ";
        int row = destination.first;
        int col = destination.second;
    
        std::stack<Posicion_t> path;
    
        while (!(cellDetails[row][col].GetPadreX() == row
              && cellDetails[row][col].GetPadreY() == col)) {
          path.push(std::make_pair(row, col));
          int temp_row = cellDetails[row][col].GetPadreX();
          int temp_col = cellDetails[row][col].GetPadreY();
          row = temp_row;
          col = temp_col;
        }
    
        path.push(std::make_pair(row, col));
        Solution_ = path;
        while (!path.empty()) {
        std::pair<int, int> p = path.top();
        path.pop();
        //printf("-> (%d,%d) ", p.first, p.second);
        std::cout << "-> (" << p.first << "," << p.second << ") ";
        }
        std::cout << std::endl;
        
        return;
      }
      // of the successor is already on the closed list or if it is blocked,
      // then ignore it. Else do the following:
      else if (closedList[i - 1][j] == false
              && isUnBlocked(Grid, i - 1, j) == true) {
        gNew = cellDetails[i][j].GetG() + 1.0;
        hNew = calculateHValue(i - 1, j, destination);
        fNew = gNew + hNew;
        // if it isn’t on the open list, add it to the open list. Make the current square
        // the parent of this square. Record the f, g, and h costs of the square cell
        //                OR
        // if it is on the open list already, check to see if this path to that square is
        // better, using 'f' cost as the measure.
        if (cellDetails[i - 1][j].GetF() == FLT_MAX
            || cellDetails[i - 1][j].GetF() > fNew) {
            openList.insert(std::make_pair(fNew, std::make_pair(i - 1, j)));
            AddExpansion();
            // update the details of this cell
            cellDetails[i - 1][j].SetF(fNew);
            cellDetails[i - 1][j].SetG(gNew);
            cellDetails[i - 1][j].SetH(hNew);
            cellDetails[i - 1][j].SetPadreX(i);
            cellDetails[i - 1][j].SetPadreY(j);
        }
      }
    }

    //----------- 2nd Successor (South) ------------

    // only process this cell if this is a valid one
    if (isValid(i + 1, j) == true) {
      // if the destination cell is the same as the current successor
      if (isDestination(i + 1, j, destination) == true) {
        // set the Parent of the destination cell
        cellDetails[i + 1][j].SetPadreX(i);
        cellDetails[i + 1][j].SetPadreY(j);
        printf("The destination cell is found\n");
        //foundDest = true;
        //tracePath(cellDetails, destination);

        int row = destination.first;
        int col = destination.second;
        std::stack<Posicion_t> path;
        while (!(cellDetails[row][col].GetPadreX() == row
                && cellDetails[row][col].GetPadreY() == col)) {
          path.push(std::make_pair(row, col));
          int temp_row = cellDetails[row][col].GetPadreX();
          int temp_col = cellDetails[row][col].GetPadreY();
          row = temp_row;
          col = temp_col;
        }

        path.push(std::make_pair(row, col));
        Solution_ = path;
        while (!path.empty()) {
        std::pair<int, int> p = path.top();
        path.pop();
        //printf("-> (%d,%d) ", p.first, p.second);
        std::cout << "-> (" << p.first << "," << p.second << ") ";
        }
        std::cout << std::endl;
        
        return;
      }
      // if the successor is already on the closed list or if it is blocked,
      // then ignore it. Else do the following:
      else if (closedList[i + 1][j] == false
              && isUnBlocked(Grid, i + 1, j) == true) {
        gNew = cellDetails[i][j].GetG() + 1.0;
        hNew = calculateHValue(i + 1, j, destination);
        fNew = gNew + hNew;
        // if it isn’t on the open list, add it to the open list. Make the current square
        // the parent of this square. Record the f, g, and h costs of the square cell
        //                OR
        // if it is on the open list already, check to see if this path to that square is
        // better, using 'f' cost as the measure.
        if (cellDetails[i + 1][j].GetF() == FLT_MAX
            || cellDetails[i + 1][j].GetF() > fNew) {
          openList.insert(std::make_pair(fNew, std::make_pair(i + 1, j)));
          AddExpansion();
          // update the details of this cell
          cellDetails[i + 1][j].SetF(fNew);
          cellDetails[i + 1][j].SetG(gNew);
          cellDetails[i + 1][j].SetH(hNew);
          cellDetails[i + 1][j].SetPadreX(i);
          cellDetails[i + 1][j].SetPadreY(j);
        }
      }
    }

    //----------- 3rd Successor (East) ------------

    // only process this cell if this is a valid one
    if (isValid(i, j + 1) == true) {
      // if the destination cell is the same as the current successor
      if (isDestination(i, j + 1, destination) == true) {
        // set the Parent of the destination cell
        cellDetails[i][j + 1].SetPadreX(i);
        cellDetails[i][j + 1].SetPadreY(j);
        printf("The destination cell is found\n");
        foundDest = true;
        //tracePath(cellDetails, destination);

        std::cout << "\nThe path is ";
        int row = destination.first;
        int col = destination.second;
    
        std::stack<Posicion_t> path;
    
        while (!(cellDetails[row][col].GetPadreX() == row
              && cellDetails[row][col].GetPadreY() == col)) {
          path.push(std::make_pair(row, col));
          int temp_row = cellDetails[row][col].GetPadreX();
          int temp_col = cellDetails[row][col].GetPadreY();
          row = temp_row;
          col = temp_col;
        }
    
        path.push(std::make_pair(row, col));
        Solution_ = path;
        while (!path.empty()) {
        std::pair<int, int> p = path.top();
        path.pop();
        //printf("-> (%d,%d) ", p.first, p.second);
        std::cout << "-> (" << p.first << "," << p.second << ") ";
        }
        std::cout << std::endl;
        
        return;
      }

      // if the successor is already on the closed list or if it is blocked,
      // then ignore it. Else do the following:
      else if (closedList[i][j + 1] == false
              && isUnBlocked(Grid, i, j + 1) == true) {
        gNew = cellDetails[i][j].GetG()+ 1.0;
        hNew = calculateHValue(i, j + 1, destination);
        fNew = gNew + hNew;
        // if it isn’t on the open list, add it to the open list. Make the current square
        // the parent of this square. Record the f, g, and h costs of the square cell
        //                OR
        // if it is on the open list already, check to see if this path to that square is
        // better, using 'f' cost as the measure.
        if (cellDetails[i][j + 1].GetF() == FLT_MAX
            || cellDetails[i][j + 1].GetF() > fNew) {
          openList.insert(std::make_pair(fNew, std::make_pair(i, j + 1)));
          AddExpansion();
          // update the details of this cell
          cellDetails[i][j + 1].SetF(fNew);
          cellDetails[i][j + 1].SetG(gNew);
          cellDetails[i][j + 1].SetH(hNew);
          cellDetails[i][j + 1].SetPadreX(i);
          cellDetails[i][j + 1].SetPadreY(j);
        }
      }
    }

    //----------- 4th Successor (West) ------------

    // only process this cell if this is a valid one
    if (isValid(i, j - 1) == true) {
      // if the destination cell is the same as the current successor
      if (isDestination(i, j - 1, destination) == true) {
        cellDetails[i][j - 1].SetPadreX(i);
        cellDetails[i][j - 1].SetPadreY(j);
        printf("The destination cell is found\n");
        foundDest = true;
        //tracePath(cellDetails, destination);

        std::cout << "\nThe path is ";
        int row = destination.first;
        int col = destination.second;
    
        std::stack<Posicion_t> path;
    
        while (!(cellDetails[row][col].GetPadreX() == row
              && cellDetails[row][col].GetPadreY() == col)) {
          path.push(std::make_pair(row, col));
          int temp_row = cellDetails[row][col].GetPadreX();
          int temp_col = cellDetails[row][col].GetPadreY();
          row = temp_row;
          col = temp_col;
        }
    
        path.push(std::make_pair(row, col));
        Solution_ = path;
        while (!path.empty()) {
        std::pair<int, int> p = path.top();
        path.pop();
        //printf("-> (%d,%d) ", p.first, p.second);
        std::cout << "-> (" << p.first << "," << p.second << ") ";
        }
        std::cout << std::endl;
        
        return;
      }

      else if (closedList[i][j - 1] == false
              && isUnBlocked(Grid, i, j - 1) == true) {
        gNew = cellDetails[i][j].GetG()+ 1.0;
        hNew = calculateHValue( i, j - 1, destination);
        fNew = gNew + hNew;

        if (cellDetails[i][j - 1].GetF() == FLT_MAX
            || cellDetails[i][j - 1].GetF() > fNew) {
          openList.insert(std::make_pair(fNew, std::make_pair(i, j - 1)));
          AddExpansion();
          // update the details of this cell
          cellDetails[i][j - 1].SetF(fNew);
          cellDetails[i][j - 1].SetG(gNew);
          cellDetails[i][j - 1].SetH(hNew);
          cellDetails[i][j - 1].SetPadreX(i);
          cellDetails[i][j - 1].SetPadreY(j);
        }
      }
    }

    //----------- 5th Successor (North - West) ------------

    // only process this cell if this is a valid one
    if (isValid(i - 1, j - 1) == true) {
      // if the destination cell is the same as the current successor
      if (isDestination(i - 1, j - 1, destination) == true) {
        // set the Parent of the destination cell
        cellDetails[i - 1][j - 1].SetPadreX(i);
        cellDetails[i - 1][j - 1].SetPadreY(j);
        printf("The destination cell is found\n");
        foundDest = true;
        //tracePath(cellDetails, destination);

        std::cout << "\nThe path is ";
        int row = destination.first;
        int col = destination.second;
    
        std::stack<Posicion_t> path;
    
        while (!(cellDetails[row][col].GetPadreX() == row
              && cellDetails[row][col].GetPadreY() == col)) {
          path.push(std::make_pair(row, col));
          int temp_row = cellDetails[row][col].GetPadreX();
          int temp_col = cellDetails[row][col].GetPadreY();
          row = temp_row;
          col = temp_col;
        }
    
        path.push(std::make_pair(row, col));
        Solution_ = path;
        while (!path.empty()) {
        std::pair<int, int> p = path.top();
        path.pop();
        //printf("-> (%d,%d) ", p.first, p.second);
        std::cout << "-> (" << p.first << "," << p.second << ") ";
        }
        std::cout << std::endl;
        
        return;
      }

      else if (closedList[i - 1][j - 1] == false
              && isUnBlocked(Grid, i - 1, j - 1) == true) {
        gNew = cellDetails[i][j].GetG()+ 1.0;
        hNew = calculateHValue( i - 1, j - 1, destination);
        fNew = gNew + hNew;

        if (cellDetails[i - 1][j - 1].GetF() == FLT_MAX
            || cellDetails[i - 1][j - 1].GetF() > fNew) {
          openList.insert(std::make_pair(fNew, std::make_pair(i - 1, j - 1)));
          AddExpansion();
          // update the details of this cell
          cellDetails[i - 1][j - 1].SetF(fNew);
          cellDetails[i - 1][j - 1].SetG(gNew);
          cellDetails[i - 1][j - 1].SetH(hNew);
          cellDetails[i - 1][j - 1].SetPadreX(i);
          cellDetails[i - 1][j - 1].SetPadreY(j);
        }
      }
    }

    //----------- 6th Successor (South - East) ------------

    // only process this cell if this is a valid one
    if (isValid(i + 1, j + 1) == true) {
      // if the destination cell is the same as the current successor
      if (isDestination(i + 1, j + 1, destination) == true) {
        // set the Parent of the destination cell
        cellDetails[i + 1][j + 1].SetPadreX(i);
        cellDetails[i + 1][j + 1].SetPadreY(j);
        printf("The destination cell is found\n");
        foundDest = true;
        //tracePath(cellDetails, destination);

        std::cout << "\nThe path is ";
        int row = destination.first;
        int col = destination.second;
    
        std::stack<Posicion_t> path;
    
        while (!(cellDetails[row][col].GetPadreX() == row
              && cellDetails[row][col].GetPadreY() == col)) {
          path.push(std::make_pair(row, col));
          int temp_row = cellDetails[row][col].GetPadreX();
          int temp_col = cellDetails[row][col].GetPadreY();
          row = temp_row;
          col = temp_col;
        }
    
        path.push(std::make_pair(row, col));
        Solution_ = path;
        while (!path.empty()) {
        std::pair<int, int> p = path.top();
        path.pop();
        //printf("-> (%d,%d) ", p.first, p.second);
        std::cout << "-> (" << p.first << "," << p.second << ") ";
        }
        std::cout << std::endl;
        
        return;
      }

      else if (closedList[i + 1][j + 1] == false
              && isUnBlocked(Grid, i + 1, j + 1) == true) {
        gNew = cellDetails[i][j].GetG()+ 1.0;
        hNew = calculateHValue( i + 1, j + 1, destination);
        fNew = gNew + hNew;

        if (cellDetails[i + 1][j + 1].GetF() == FLT_MAX
            || cellDetails[i + 1][j + 1].GetF() > fNew) {
          openList.insert(std::make_pair(fNew, std::make_pair(i + 1, j + 1)));
          AddExpansion();
          // update the details of this cell
          cellDetails[i + 1][j + 1].SetF(fNew);
          cellDetails[i + 1][j + 1].SetG(gNew);
          cellDetails[i + 1][j + 1].SetH(hNew);
          cellDetails[i + 1][j + 1].SetPadreX(i);
          cellDetails[i + 1][j + 1].SetPadreY(j);
        }
      }
    }

    //----------- 7th Successor (South - West) ------------

    // only process this cell if this is a valid one
    if (isValid(i + 1, j - 1) == true) {
      // if the destination cell is the same as the current successor
      if (isDestination(i + 1, j - 1, destination) == true) {
        // set the Parent of the destination cell
        cellDetails[i + 1][j - 1].SetPadreX(i);
        cellDetails[i + 1][j - 1].SetPadreY(j);
        printf("The destination cell is found\n");
        foundDest = true;
        //tracePath(cellDetails, destination);

        std::cout << "\nThe path is ";
        int row = destination.first;
        int col = destination.second;
    
        std::stack<Posicion_t> path;
    
        while (!(cellDetails[row][col].GetPadreX() == row
              && cellDetails[row][col].GetPadreY() == col)) {
          path.push(std::make_pair(row, col));
          int temp_row = cellDetails[row][col].GetPadreX();
          int temp_col = cellDetails[row][col].GetPadreY();
          row = temp_row;
          col = temp_col;
        }
    
        path.push(std::make_pair(row, col));
        Solution_ = path;
        while (!path.empty()) {
        std::pair<int, int> p = path.top();
        path.pop();
        //printf("-> (%d,%d) ", p.first, p.second);
        std::cout << "-> (" << p.first << "," << p.second << ") ";
        }
        std::cout << std::endl;
        
        return;
      }

      else if (closedList[i + 1][j - 1] == false
              && isUnBlocked(Grid, i + 1, j - 1) == true) {
        gNew = cellDetails[i][j].GetG()+ 1.0;
        hNew = calculateHValue( i + 1, j - 1, destination);
        fNew = gNew + hNew;

        if (cellDetails[i + 1][j - 1].GetF() == FLT_MAX
            || cellDetails[i + 1][j - 1].GetF() > fNew) {
          openList.insert(std::make_pair(fNew, std::make_pair(i + 1, j - 1)));
          AddExpansion();
          // update the details of this cell
          cellDetails[i + 1][j - 1].SetF(fNew);
          cellDetails[i + 1][j - 1].SetG(gNew);
          cellDetails[i + 1][j - 1].SetH(hNew);
          cellDetails[i + 1][j - 1].SetPadreX(i);
          cellDetails[i + 1][j - 1].SetPadreY(j);
        }
      }
    }

    //----------- 8th Successor (North East) ------------

    // only process this cell if this is a valid one
    if (isValid(i - 1, j + 1) == true) {
      // if the destination cell is the same as the current successor
      if (isDestination(i - 1, j + 1, destination) == true) {
        // set the Parent of the destination cell
        cellDetails[i - 1][j + 1].SetPadreX(i);
        cellDetails[i - 1][j + 1].SetPadreY(j);
        printf("The destination cell is found\n");
        foundDest = true;
        //tracePath(cellDetails, destination);

        std::cout << "\nThe path is ";
        int row = destination.first;
        int col = destination.second;
    
        std::stack<Posicion_t> path;
    
        while (!(cellDetails[row][col].GetPadreX() == row
              && cellDetails[row][col].GetPadreY() == col)) {
          path.push(std::make_pair(row, col));
          int temp_row = cellDetails[row][col].GetPadreX();
          int temp_col = cellDetails[row][col].GetPadreY();
          row = temp_row;
          col = temp_col;
        }
    
        path.push(std::make_pair(row, col));
        Solution_ = path;
        while (!path.empty()) {
        std::pair<int, int> p = path.top();
        path.pop();
        //printf("-> (%d,%d) ", p.first, p.second);
        std::cout << "-> (" << p.first << "," << p.second << ") ";
        }
        std::cout << std::endl;
        
        return;
      }

      else if (closedList[i - 1][j + 1] == false
              && isUnBlocked(Grid, i - 1, j + 1) == true) {
        gNew = cellDetails[i][j].GetG()+ 1.0;
        hNew = calculateHValue( i - 1, j + 1, destination);
        fNew = gNew + hNew;

        if (cellDetails[i - 1][j + 1].GetF() == FLT_MAX
            || cellDetails[i - 1][j + 1].GetF() > fNew) {
          openList.insert(std::make_pair(fNew, std::make_pair(i - 1, j + 1)));
          AddExpansion();
          // update the details of this cell
          cellDetails[i - 1][j + 1].SetF(fNew);
          cellDetails[i - 1][j + 1].SetG(gNew);
          cellDetails[i - 1][j + 1].SetH(hNew);
          cellDetails[i - 1][j + 1].SetPadreX(i);
          cellDetails[i - 1][j + 1].SetPadreY(j);
        }
      }
    }
  } // while

  if (foundDest == false)
    std::cout << "Could not find the path" << std::endl;
}