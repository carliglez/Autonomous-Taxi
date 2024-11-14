/**
 * @file world.cc
 * @author carliglez (https://github.com/carliglez)
 * @brief World class source file
 * @version 0.1
 * @date 2024-11-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../include/world.h"

// constructors
World::World(){
  row = 10;
  column = 10;
  size = 100;
  world = Vector<Vector<Cell>> (-10,10);
  for(int i = 0; i < 10; i++) {
    world[i].resize(10);
  }
}
std::vector<int> a;
World::World(int row_size, int column_size) {
  row = row_size;
  column = column_size;
  size = row * column;
  world.resize(row_size);
    for(int i = 0; i < column_size; i++) {
    world[i].resize(column_size);
  }
}

World::World(int row_min, int row_max, int col_min, int col_max) {
  row = row_max - row_min;
  column = col_max - col_min;
  size = row * column;
  world.resize(row);
  world.SetLowerLimit(row_min);
  for(int i = world.GetLowerLimit(); i < world.GetUpperLimit(); i++) {
    world[i].resize(column);
    
    world[i].SetLowerLimit(col_min);
  }
}

World::World(int row_min, int row_max, int col_min, int col_max, int obstacle_type) {  // initializes a world with random obstacles
  row = row_max - row_min;
  column = col_max - col_min;
  size = row * column;
  world.resize(row);
  world.SetLowerLimit(row_min);
  //world.SetUpperLimit(col)
  int x, y;
  for(int i = world.GetLowerLimit(); i < world.GetUpperLimit(); i++) {
    world[i].resize(column);
    //std::cout<<world.GetLowerLimit() <<std::endl;

    for (int iter = 0; iter < world.GetUpperLimit(); iter++) {
      //std::cout<<world[i].GetLowerLimit() <<std::endl;
      world[i][iter].SetPos(i, iter);
    }

    world[i].SetLowerLimit(col_min);
  }

  int obstacle_percentage;
  int obstacle_quantity;

  switch(obstacle_type) {
    case 0:   
      std::cout << "Enter the percentage of obstacles (value between 0 and 100): " << std:: endl;
      std::cin >> obstacle_percentage;
      while ((obstacle_percentage < 0) || (obstacle_percentage > 100)) {
        std::cout << "ERROR: value outside the range between 0 and 100" << std::endl;
        std::cout << "Enter the percentage of obstacles (value between 0 and 100): " << std:: endl;
        std::cin >> obstacle_percentage;
      }
      obstacle_quantity = size * obstacle_percentage / 100;

      srand(time(NULL)); 
      for(int i = 0; i < obstacle_quantity; i++) {
        int random_row = rand()%(world.GetUpperLimit() - world.GetLowerLimit()) + world.GetLowerLimit();
        int random_col = rand()%(world[random_row].GetUpperLimit() - world[random_row].GetLowerLimit()) + world[random_row].GetLowerLimit();
        
        SetWorldState('0', random_row, random_col);
        SetWorldValue(true, random_row, random_col);
      }
    break;

    case 1:
      std::cout << "Enter the percentage of obstacles (value between 0 and 100): " << std:: endl;
      std::cin >> obstacle_percentage;
      while ((obstacle_percentage < 0) || (obstacle_percentage > 100)) {
        std::cout << "ERROR: value outside the range between 0 and 100" << std::endl;
        std::cout << "Enter the percentage of obstacles (value between 0 and 100): " << std:: endl;
        std::cin >> obstacle_percentage;
      }
      obstacle_quantity = size * obstacle_percentage / 100;

      for(int i = 0; i < obstacle_quantity; i++) {
        do {
          std::cout << "Enter the X coordinate of the obstacle " << i+1 << " : ";
          std::cin >> x;
        while ((x < 0) || (x > row_max * 2 - 1)) {
          std::cout << "ERROR: the X-coordinate is not within the defined world" << std::endl;
          std::cout << "Enter a coordinate between " << 0 << " and " << row_max * 2 - 1 << std:: endl;
          std::cin >> x;
        }
        std::cout << "Enter the Y coordinate of the obstacle: " << i+1 << " : ";
        std::cin >> y;
        while ((y < 0) || ( y > col_max * 2 - 1)) {
          std::cout << "ERROR: the Y-coordinate is not within the defined world" << std::endl;
          std::cout << "Enter a coordinate between " << 0 << " and " << col_max * 2 - 1 << std:: endl;
          std::cin >> y;
        }
    
        } while (GetWorldValue(x, y) == true);  // as long as the box is already occupied
      x += row_min;
      y += col_min;
      SetWorldState('0', x, y);
      SetWorldValue(true, x, y);
      }
    break;

    case 2:
      try {
        // relative path
        std::string filename = "./data/coordinates.txt";
        std::ifstream input_file; // reads the contents of the file
        input_file.open(filename.c_str(), std::ifstream::in);

        std::string read, num1, num2;
        unsigned move = 0;

        if (!input_file.is_open()) throw 1;
        
        while(getline(input_file, read)) {
          if (read[0] != '/' && read[1] != '/') {

          for(; move < read.size(); move++) {
            if(read[move] != ',') {
              num1.push_back(read[move]);
            }
            else {
              move++;
              break;
            }
          }
          for(; move < read.size(); move++) {
            num2.push_back(read[move]);
          } 

          x = stoi(num1);
          y = stoi(num2);
          num1.clear();
          num2.clear();
          move = 0;

          if((x < 0) || (x > row_max * 2 - 1) || (y < 0) || ( y > col_max * 2 - 1)) throw 2;

          x += row_min;
          y += col_min;
          SetWorldState('0', x, y);
          SetWorldValue(true, x, y);
          }
        }          
        input_file.close();
      } catch(int& error) {  // errors opening the file
          switch (error)
          {
          case 1:
            std::cout << "ERROR: when trying to open the file" << std::endl;
            break;
          case 2:
            std::cout << "ERROR: the data is not entered correctly" << std::endl;
            break;
          }
      }
    break;
  }
}

// destructor
World::~World() {
  //delete heuristic_function;
}

// getters and setters
char World::GetWorldState(int i, int j) { return world[i][j].GetState(); }

bool World::GetWorldValue(int i, int j) {
  try {
    return world[i][j].GetValue(); 
  }
  
  catch(...) {
    throw std::exception();
  }
}

int World::GetWorldX(int i, int j) { return world[i][j].GetX(); }

int World::GetWorldY(int i, int j) { return world[i][j].GetY(); }

void World::SetRow(int row_) { row = row_; }

void World::SetColumn(int column_) { column = column_; }

void World::SetSize(int size_) { size = size_; }

void World::SetWorldState(char state_, int i, int j) { world[i][j].SetState(state_); }

void World::SetWorldValue(bool value_, int i, int j) { world[i][j].SetValue(value_); }

void World::ToggleWorldValue(int i, int j) {
  if(world[i][j].GetValue() == false)
    world[i][j].SetValue(true);
  else
    world[i][j].SetValue(false);
}

void World::SetWorld(World_t& new_world) {
  world.resize(new_world.GetSize());
  world.SetLowerLimit(new_world.GetLowerLimit());

  for(int i = world.GetLowerLimit(); i < world.GetUpperLimit(); i++) {
    world[i].resize(new_world[i].GetSize());
    world[i].SetLowerLimit(new_world[i].GetLowerLimit());
    for(int j = world[i].GetLowerLimit(); j < world[i].GetUpperLimit(); j++) {
      world[i][j] = new_world[i][j];
    }
  }
}

void World::PrintWorld(void) {
  PrintHorizontalWall();
  for(int i = world.GetLowerLimit(); i < world.GetUpperLimit(); i++) {
    std::cout << "|";
    for(int j = world[i].GetLowerLimit(); j < world[i].GetUpperLimit(); j++) {
      if (GetWorldState(i,j) == '0') {
        std::cout << "\033[;36m0\033[0m";
      } else if (GetWorldState(i,j) == 'X') {
        std::cout << "\033[;32mX\033[0m";
      } else {
        std::cout <<  GetWorldState(i,j) ;
      }
    }
    std::cout << "|" << std::endl;
  }
  PrintHorizontalWall();
}

void World::PrintHorizontalWall(void) {   
  for(int i = world[0].GetLowerLimit(); i < world[0].GetUpperLimit() + 2; i++) {
    std::cout << "⬛";
  }
  std::cout << std::endl;
}

/*void World::Update(std::vector<Vehicle>& vehicle) {
  for(int i = 0; i < vehicle.size(); i++) {
    if ((GetWorldValue(vehicle[i].GetRow(), vehicle[i].GetColumn())) == false){ // white box
      SetWorldValue(true, vehicle[i].GetRow(), vehicle[i].GetColumn());
    }
    else {
      SetWorldValue(false, vehicle[i].GetRow(), vehicle[i].GetColumn());  // black box
    } 
  }
}*/

void World::PrintGrid(Vehicle* vehicle) {
  PrintHorizontalWall();
    for(int i = world.GetLowerLimit(); i < world.GetUpperLimit(); i++) {
      std::cout << "⬛";
      for(int j = world[i].GetLowerLimit(); j < world[i].GetUpperLimit(); j++) {
        if((i == vehicle->GetRow()) && (j == vehicle->GetColumn()))
          //vehicle->PrintDirection();
          if((i == vehicle->GetOrigin().first) && (j == vehicle->GetOrigin().second)) {
            std::cout << "🍀";
          } else {
            std::cout << "🚖";   //🚖🟩🟥✅"; green: \U0001f7e9
          }
        else if ((i == vehicle->GetDestinationRow()) && (j == vehicle->GetDestinationColumn())) {
          //std::cout << "\033[;31m\u2691\033[0m";
          std::cout << "🚩";
        }
        else if (GetWorldState(i,j) == '0') {
          std::cout << "\033[;36m⬛\033[0m";
        } else if (GetWorldState(i,j) == 'X') {
          std::cout << "\033[;32mX\033[0m";
        } else {
          std::cout << "\033[;36m⬜\033[0m"; // GetWorldState(i,j) ;
        }
      }
      std::cout << "⬛" << std::endl;
    }
  PrintHorizontalWall();
}

void World::PrintSolucion(Vehicle* vehicle) {
  while (!vehicle->Solution_.empty()){
    Posicion_t aux = vehicle->Solution_.top();
    SetWorldState('X',aux.first, aux.second);
    vehicle->Solution_.pop();
  }

  PrintHorizontalWall();
    for(int i = world.GetLowerLimit(); i < world.GetUpperLimit(); i++) {
      std::cout << "⬛";
      for(int j = world[i].GetLowerLimit(); j < world[i].GetUpperLimit(); j++) {
        //if((i == vehicle->GetRow()) && (j == vehicle->GetColumn()))
          //vehicle->PrintDirection();
        if((i == vehicle->GetOrigin().first) && (j == vehicle->GetOrigin().second)) {
          std::cout << "🍀";
        } else if ((i == vehicle->GetDestinationRow()) && (j == vehicle->GetDestinationColumn())) {
          //std::cout << "\033[;31m\u2691\033[0m";
          std::cout << "🚩";
        } else if (GetWorldState(i,j) == '0') {
          std::cout << "\033[;36m⬛\033[0m";
        } else if (GetWorldState(i,j) == 'X') {
          std::cout << "🚖";   //🚖🟩🟥✅"; green: \U0001f7e9
        } else {
          std::cout << "\033[;36m⬜\033[0m"; // GetWorldState(i,j);
        }
      }
      std::cout << "⬛" << std::endl;
    }
  PrintHorizontalWall();
}

bool World::VehicleOut(Vehicle* vehicle) {
  bool condition = false;
  if((vehicle->GetRow() >= world.GetUpperLimit()) || (vehicle->GetColumn() >= world.GetUpperLimit()) || (vehicle->GetRow() < world.GetLowerLimit()) || (vehicle->GetColumn() < world.GetLowerLimit()))
    condition = true;
  return condition;
}

void World::TryPosition(Vehicle* vehicle){
  try {
    Cell temp;
    temp = GetCell(vehicle->GetRow(), vehicle->GetColumn());
  } catch(std::exception()) {
    std::cout << "ERROR: the taxi has left the simulation environment" << std::endl;
    throw(std::exception());
  }
}