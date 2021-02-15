#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include <vector>
#include <set>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

struct HexCoord{
    int x = 0;
    int y = 0;
    int z = 0;
    bool state = false;

    string repr(){
        return to_string(x) + " " + to_string(y) + " " + to_string(z);
    }

    void move(string move){
      if (move == "ne") {
        x++;
        z--;
      } else if (move == "e") {
        x++;
        y--;
      } else if (move == "se") {
        z++;
        y--;
      } else if (move == "nw") {
        y++;
        z--;
      } else if (move == "w") {
        y++;
        x--;
      } else if (move == "sw") {
        z++;
        x--;
      }
    }

};

unordered_map<string, HexCoord> tiles;

int count_black_neighbours(HexCoord& tile,unordered_map<string, HexCoord>& tile_layout) {
  int count = 0;
  vector<string> moves = {"ne", "e", "se", "nw", "w", "sw"};
  for (string move : moves) {
    HexCoord neighbour = tile;
    neighbour.move(move);
    string neighbour_repr = neighbour.repr();
    if (tile_layout.count(neighbour_repr)) {
      if (tile_layout[neighbour_repr].state) {
        // cout << '[' << neighbour_repr << "] is black" << '\n';
        count++;
      }
    } else {
        neighbour.state = false;
      tiles[neighbour_repr] = neighbour;
    }
  }
  // cout << "Tile coord [" << tile.repr() << "] " << "has " << count << " black neighbours" << '\n';
  return count;
}

void discover_neighbours(int depth) {
  vector<string> moves = {"ne", "e", "se", "nw", "w", "sw"};
  for (int i = 0; i < depth; i++) {
    for (auto &tile_coord : tiles) {
      HexCoord tile = tile_coord.second;
      for (string move : moves) {
        HexCoord neighbour = tile;
        neighbour.move(move);
        string neighbour_repr = neighbour.repr();
        if (!tiles.count(neighbour_repr)) {
          neighbour.state = false;
          tiles[neighbour_repr] = neighbour;
        }
      }
    }
  }
}

int main() {
  string line;
  vector<string> directions;
  int num_black = 0;

  while (getline(cin, line)) {
    directions.push_back(line);
  }
  for (string dir : directions) {
    vector<string> moves;
    HexCoord tile_coord;
    for (int i = 0; i < dir.length(); i++) {
      if (dir[i] == 'n' or dir[i] == 's') {
        moves.push_back(string(1, dir[i]) + string(1, dir[i + 1]));
        i++;
      } else {
        moves.push_back(string(1, dir[i]));
      }
    }
    cout << "Moves: ";
    for (string move : moves) { // Follow cube coordinate system for hexagonals
      cout << move << ' ';
      tile_coord.move(move);
    }
    cout << "Final tile coordinate: ";
    cout << "X: " << tile_coord.x << " Y: " << tile_coord.y << '\n';
    cout << '\n';
    string tile_coord_str = tile_coord.repr();
    if (!tiles.count(tile_coord_str)) {
      tile_coord.state = true;
      tiles[tile_coord_str] = tile_coord; // It's black
    } else {
      tiles[tile_coord_str].state = !tiles[tile_coord_str].state;
    }
  }
  for (auto &tile_coord : tiles) {
    cout << tile_coord.first << '\n';
    cout << tile_coord.second.state << '\n';
    if (tile_coord.second.state) {
      num_black++;
    }
  }
  cout << "Number of black tiles: " << num_black << '\n';
  //Discovery phase
  discover_neighbours(10);
  for (int day = 1; day <= 100; day++) {
    unordered_map<string, HexCoord> old_tiles = tiles;
    int day_num_black = 0;
    for (auto &tile : old_tiles) {
      int num_black_neighbours = count_black_neighbours(tile.second,old_tiles);
      if (tile.second.state) { // 0 or more than 2
        if (num_black_neighbours == 0 or num_black_neighbours > 2) {
          tiles[tile.first].state = false;
        }
      } else {
        if (num_black_neighbours == 2) {
          tiles[tile.first].state = true;
        }
      }
    }
    for(auto& tile: tiles){
      if (tile.second.state) {
        day_num_black++;
      }
    }
    cout << "Day " << day << ": " << day_num_black << '\n';
  }
}
