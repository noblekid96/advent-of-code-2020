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
    long long x;
    long long y;
};

void update(Coords& coord, int dx, int dy){
    coord.x = coord.x + dx;
    coord.y = coord.y + dy;
}

void rotateLeft(Coords& coord, int num90degrees){
  Coords old_coord = Coords({coord.x,coord.y});
  for (int i = 0 ; i < num90degrees; i ++){
    coord.y = old_coord.x;
    coord.x = -1 * old_coord.y;
    old_coord.x = coord.x;
    old_coord.y = coord.y;
  }
}

void rotateRight(Coords& coord, int num90degrees){
  Coords old_coord = Coords({coord.x,coord.y});
  for (int i = 0 ; i < num90degrees; i ++){
    coord.x = old_coord.y;
    coord.y = -1 * old_coord.x;
    old_coord.x = coord.x;
    old_coord.y = coord.y;
  }
}

int main(){
    string line;
    Coords coord = Coords({0,0});
    Coords waypoint = Coords({10,1});
    char move;
    int mag;
    int numRots;
    long long dx;
    long long dy;
    while (getline(cin, line)) {
        move = line.at(0);
        // cout << move << '\n';
        mag = atoi(line.substr(1,line.length()).c_str());
        switch (move) {
        case 'F':
          dx = mag * waypoint.x;
          dy = mag * waypoint.y;
          update(coord, dx, dy);
          break;
        case 'L':
          numRots = mag/90;
          rotateLeft(waypoint, numRots);
          break;
        case 'R':
          numRots = mag/90;
          rotateRight(waypoint, numRots);
          break;
        case 'N':
          dx = mag * directions[NORTH].dx;
          dy = mag * directions[NORTH].dy;
          update(waypoint, dx, dy);
          break;
        case 'S':
          dx = mag * directions[SOUTH].dx;
          dy = mag * directions[SOUTH].dy;
          update(waypoint, dx, dy);
          break;
        case 'E':
          dx = mag * directions[EAST].dx;
          dy = mag * directions[EAST].dy;
          update(waypoint, dx, dy);
          break;
        case 'W':
          dx = mag * directions[WEST].dx;
          dy = mag * directions[WEST].dy;
          update(waypoint, dx, dy);
          break;
        }
        cout << "Waypoint: {" << waypoint.x << ',' << waypoint.y << "}\n";
    }
    cout << "Coordinates: " << coord.x << " " << coord.y << '\n';
    cout << "Manhattan Coordinates: " << abs(coord.x) + abs(coord.y) << '\n';
}
