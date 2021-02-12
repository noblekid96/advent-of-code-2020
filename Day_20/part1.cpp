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

typedef unsigned long long long_t;

struct Tile{
    int id;
    vector<string> body;
    string left;
    string right;
    string top;
    string bottom;

    Tile(){}

    void init_tile(int tile_id, vector<string> new_body){
        id = tile_id;
        body = new_body;
        // cout << "Tile: " << id << " body size " << new_body.size() << '\n';
        top = body[0];
        bottom = body[body.size()-1];

        for(string line: body){
            left.insert(left.begin(),line[0]);
            right.insert(right.begin(),line[line.size()-1]);
        }
    }

    bool isLeft(Tile& other_tile){
        return (right == other_tile.left);
    }
    bool isRight(Tile& other_tile){
        return (left == other_tile.right);
    }
    bool isTop(Tile& other_tile){
        return (bottom == other_tile.top);
    }
    bool isBottom(Tile& other_tile){
        return (top == other_tile.bottom);
    }
};

vector<Tile> tile_orientations(Tile& ref_tile){
    vector<string> ref_body = ref_tile.body;
    vector<Tile> tile_orientations;
    vector<Tile> flipped_tiles;

    for (int j = 0; j < 4; j++) {
        vector<string> new_body;
      for (int i = 0; i < ref_body.size(); i++) {
        // Rotate by 90 degrees clockwise
        string rotated_line = "";
        for (string line : ref_body) {
            // cout << "Ref body line" << line << '\n';
          rotated_line.insert(rotated_line.begin(), line[i]);
        }
        // cout << "Rotated line: " << rotated_line << " Ref body line: " << ref_body[i] << '\n';
        new_body.push_back(rotated_line);
      }

      Tile new_tile = Tile();
      new_tile.init_tile(ref_tile.id,new_body);
      ref_body = new_body;
      new_body.clear();
      tile_orientations.push_back(new_tile);
    }

    for (Tile rotated_tile: tile_orientations){
        vector<string> new_body;
        new_body = rotated_tile.body;
        reverse(new_body.begin(),new_body.end());
        Tile new_tile = Tile();
        new_tile.init_tile(ref_tile.id, new_body);
        new_body.clear();
        flipped_tiles.push_back(new_tile);
    }
    tile_orientations.insert(tile_orientations.end(),flipped_tiles.begin(),flipped_tiles.end());
    return tile_orientations;
}

unordered_map<int,vector<Tile>> tileset;
Tile grid[20][20];
const int S = 10; // TILE SIZE
int GRID_SIZE = -1;

void search(int row, int col, set<int> &visited) {
  if (row == GRID_SIZE) {
    // print();
    cout << "Did I reach here?" << '\n';
    printf("product = %lld\n", (long long)grid[0][0].id *
                                   grid[GRID_SIZE - 1][0].id *
                                   grid[0][GRID_SIZE - 1].id *
                                   grid[GRID_SIZE - 1][GRID_SIZE - 1].id);
    exit(0);
    return;
  }
  for (const auto& id_tiles : tileset) {
    if (!visited.count(id_tiles.first)) {
      // check if this new tile matches adjacent tiles above and on the left
      for (Tile id_tile : id_tiles.second) {
        if (row > 0 && !grid[row - 1][col].isTop(id_tile)) {
            // cout << "Lol" << '\n';
          continue;
        }
        if (col > 0 && !grid[row][col - 1].isLeft(id_tile)) {
            // cout << "lel" << '\n';
          continue;
        }
        grid[row][col] = id_tile;
        visited.insert(id_tiles.first);
        if (col == GRID_SIZE - 1) {
          // cout << "Searching row " << row + 1 << "column " << col << '\n';
          search(row + 1, 0, visited);
        } else {
          // cout << "Searching row " << row + 1 << " column " << col << '\n';
          search(row, col + 1, visited);
        }
        // cout << "Backtracking... " << '\n';
        visited.erase(id_tiles.first);
      }
    }
  }
}

void print_orientations(){
    for(auto &tile_set : tileset){
        int orientation_num = 0;
        for (Tile tiles: tile_set.second){
            // cout << "Tile id: " << tiles.id << " orientation " << orientation_num <<'\n';
            for (string line: tiles.body){
                // cout << line << '\n';
            }
            // cout << '\n';
            orientation_num ++;
        }
    }
}

int main(){
    string line;
    vector<string> tile_body;
    int tile_id = -1;

    while(getline(cin,line)){
        // cout << line << '\n';
        if(line.find("Tile") != string::npos){
            if (tile_body.size() > 0 && tile_id != -1){
              Tile tile = Tile();
              tile.init_tile(tile_id, tile_body);
              tileset[tile_id].push_back(tile);
              tile_body.clear();
            }
            string tile_id_str = line.substr(5,line.size());
            tile_id = atoi(tile_id_str.substr(0,tile_id_str.length()-1).c_str());
            vector<Tile> tile_id_tiles;
            tileset[tile_id] = tile_id_tiles;
        } else {
            if(line.length() > 0){
                tile_body.push_back(line);
            }
        }
    }
    if (tile_body.size() > 0 && tile_id != -1){
        Tile tile = Tile();
        tile.init_tile(tile_id,tile_body);
        tileset[tile_id].push_back(tile);
        tile_body.clear();
    }
    for (auto& tiles : tileset){
        // cout << tiles.second[0].body[0] << '\n';
        vector<Tile> tile_orientation = tile_orientations(tiles.second[0]);
        // cout << "Tile " << tiles.first << "orientations" << tile_orientation.size()<< '\n';
        tileset[tiles.first] = tile_orientation;
    }
    // print_orientations();

    // Perform backtracking and see which tiles fit
    GRID_SIZE = llround(sqrt(tileset.size()));
    cout << "Grid size: " << GRID_SIZE << '\n';
    set<int> visited_ids;
    search(0, 0, visited_ids);
}
