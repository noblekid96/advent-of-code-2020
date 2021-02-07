#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

struct cube {
  int x, y, z, w;
  char state;

  bool isActive() { return state == '#'; }
};

// void update_dimensions(vector<vector<vector<cube>>>& dimensions, int x,int y,int z, cube new_cube){
//     dimensions[z][y][x] = new_cube;
// }

int count_active_neighbours(cube center,
                            vector<vector<vector<vector<cube>>>> &dimensions) {
  int proximity = 1;
  int active_neighbours = 0;
  for (int w = -proximity; w <= proximity; w++) {
    for (int z = -proximity; z <= proximity; z++) {
      for (int y = -proximity; y <= proximity; y++) {
        for (int x = -proximity; x <= proximity; x++) {
          if (x == 0 && y == 0 && z == 0 && w == 0) {
            continue;
          }
          // cout << center.x << center.y << center.z << '\n';
          if ((center.x + x) < 0 || (center.x + x) >= dimensions.size() ||
              (center.y + y) < 0 || (center.y + y) >= dimensions.size() ||
              (center.z + z) < 0 || (center.z + z) >= dimensions.size() ||
              (center.w + w) < 0 || (center.w + w) >= dimensions.size()) {
            continue;
          }
          if (dimensions[center.w + w][center.z + z][center.y + y][center.x + x].isActive()) {
            active_neighbours++;
          }
        }
      }
    }
  }
  // cout << "Center coordinates: " << center.x <<','<< center.y << ',' <<
  // center.z << '\n'; cout << "Number of neighbours considered: " <<
  // num_neighbours_encountered << '\n';
  return active_neighbours;
}

void print_dimensions(vector<vector<vector<vector<cube>>>> &dimensions) {
  int space_of_interest = dimensions.size();
  cout << "Printing dimensions layout" << '\n';
  for (int w = 0; w < space_of_interest; w++) {
    for (int z = 0; z < space_of_interest; z++) {
      cout << "W = " << w - space_of_interest / 2 << '\n';
      cout << "Z = " << z - space_of_interest / 2 << '\n';
      for (int y = 0; y < space_of_interest; y++) {
        for (int x = 0; x < space_of_interest; x++) {
          cout << dimensions[w][z][y][x].state;
        }
        cout << '\n';
      }
    }
  }
  cout << "\n\n";
}

// bool compare_dimensions(vector<vector<vector<cube>>>& dimensions1,vector<vector<vector<cube>>>& dimensions2){
//     int space_of_interest = dimensions1.size();
//     for ( int z = 0 ; z < space_of_interest; z++ ){
//       for (int y = 0; y < space_of_interest; y++) {
//         for (int x = 0; x < space_of_interest; x++) {
//             if (dimensions1[z][y][x].state != dimensions2[z][y][x].state){
//                 return false;
//             }
//         }
//       }
//     }
//     return true;
// }

long long count_num_active(vector<vector<vector<vector<cube>>>> &dimensions) {
  int space_of_interest = dimensions.size();
  long long num_active = 0;
  for (int w = 0; w < space_of_interest; w++) {
    for (int z = 0; z < space_of_interest; z++) {
      for (int y = 0; y < space_of_interest; y++) {
        for (int x = 0; x < space_of_interest; x++) {
          if (dimensions[w][z][y][x].isActive()) {
            num_active++;
          }
        }
      }
    }
  }
  return num_active;
}

int main() {
  string line;
  vector<vector<vector<vector<cube>>>> dimensions;
  // vector<vector<cube>> initial_state;
  int num_cycles = 6;
  int init_planes = 2*num_cycles;

  // Initialize the 4D space that will be affected
  for (int w = 0; w <= 2 * init_planes; w++) {
    vector<vector<vector<cube>>> dimension_3;
    for (int z = 0; z <= 2 * init_planes; z++) {
      vector<vector<cube>> dimension;
      for (int y = 0; y <= 2 * init_planes; y++) {
        vector<cube> plane;
        for (int x = 0; x <= 2 * init_planes; x++) {
          cube new_cube;
          new_cube.x = x;
          new_cube.y = y;
          new_cube.z = z;
          new_cube.w = w;
          new_cube.state = '.';
          plane.push_back(new_cube);
        }
        dimension.push_back(plane);
      }
      dimension_3.push_back(dimension);
    }
    dimensions.push_back(dimension_3);
  }
  // print_dimensions(dimensions);

  int y = -1;
  while (getline(cin, line)) {
    vector<cube> cube_1d_plane;
    for (int col = 0; col < line.size(); col++) {
      dimensions[init_planes][init_planes][init_planes+y][(init_planes)-1+col].state = line[col];
    }
    y++;
  }
  // print_dimensions(dimensions);

  for (int i = 0; i < num_cycles; i++) {
    // bool is_stable = false;
    // while(!is_stable){
    vector<vector<vector<vector<cube>>>> old_dimensions = dimensions;
    int space_of_interest = dimensions.size();
    for (int w = 0; w < space_of_interest; w++) {
      for (int z = 0; z < space_of_interest; z++) {
        for (int y = 0; y < space_of_interest; y++) {
          for (int x = 0; x < space_of_interest; x++) {
            cube cube = old_dimensions[w][z][y][x];
            int active_neighbours =
                count_active_neighbours(cube, old_dimensions);
            if (cube.isActive() &&
                (active_neighbours != 2 and active_neighbours != 3)) {
              dimensions[w][z][y][x].state = '.';
            }
            if (!cube.isActive() && active_neighbours == 3) {
              dimensions[w][z][y][x].state = '#';
            }
          }
        }
      }
    }
    // is_stable = compare_dimensions(dimensions,old_dimensions);
    // }
  }
  // print_dimensions(dimensions);
  // for (vector<cube> cubes: dimensions[0][0]){
  //   for (cube cubeys : cubes){
  //     cout << cubeys.state;
  //   }
  //   cout << '\n';
  // }
  cout << "Number of active cubes: " << count_num_active(dimensions) << '\n';
}
