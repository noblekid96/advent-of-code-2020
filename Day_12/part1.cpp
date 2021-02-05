#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;

enum compass { EAST = 0, SOUTH = 1, WEST = 2, NORTH = 3}; // Clockwise with east as 0 and north as 3
struct {
    int dx;
    int dy;
} directions[] = {{1,0},{0,-1},{-1,0},{0,1}};

struct Coords {
    int x;
    int y;
};

void update(Coords& coord, int dx, int dy){
    coord.x = coord.x + dx;
    coord.y = coord.y + dy;
}



int main(){
    string line;
    int facing = 0;
    Coords coord = Coords({0,0});
    char move;
    int mag;
    int dx;                                     \
    int dy;
    while (getline(cin, line)) {
        move = line.at(0);
        // cout << move << '\n';
        mag = atoi(line.substr(1,line.length()).c_str());
        switch (move) {
        case 'F':
          dx = mag * directions[facing].dx;
          dy = mag * directions[facing].dy;
          coord.x = coord.x + dx;
          coord.y = coord.y + dy;
          break;
        case 'L':
          facing = (facing + (4 - (mag / 90))) % 4;
          break;
        case 'R':
          facing = (facing + (mag / 90)) % 4;
          break;
        case 'N':
          dx = mag * directions[NORTH].dx;
          dy = mag * directions[NORTH].dy;
          update(coord, dx, dy);
          break;
        case 'S':
          dx = mag * directions[SOUTH].dx;
          dy = mag * directions[SOUTH].dy;
          update(coord, dx, dy);
          break;
        case 'E':
          dx = mag * directions[EAST].dx;
          dy = mag * directions[EAST].dy;
          update(coord, dx, dy);
          break;
        case 'W':
          dx = mag * directions[WEST].dx;
          dy = mag * directions[WEST].dy;
          update(coord, dx, dy);
          break;
        }
        // cout << "Facing " << facing << '\n';
        // cout << "Mag " << mag << '\n';
        // // cout << "Directions: x: " << directions[facing].dx << " y: " <<
        // // directions[facing].dy  << '\n';
        // cout << "dy :" << dy << " dx: " << dx << '\n';
        // cout << "Coordinates: " << coord.x << " " << coord.y << '\n';
    }
    cout << "Coordinates: " << coord.x << " " << coord.y << '\n';
    cout << "Manhattan Coordinates: " << abs(coord.x) + abs(coord.y) << '\n';
}
