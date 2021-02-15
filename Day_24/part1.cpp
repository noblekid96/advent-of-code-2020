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

int main(){
    string line;
    vector<string> directions;
    unordered_map<string,bool> tiles;
    int num_black = 0;

    while(getline(cin,line)){
        directions.push_back(line);
    }
    for(string dir: directions){
        vector<string> moves;
        HexCoord tile_coord;
        for(int i = 0 ; i < dir.length(); i ++){
            if (dir[i] == 'n' or dir[i] == 's') {
                moves.push_back(string(1,dir[i])+string(1,dir[i+1]));
                i++;
            } else {
                moves.push_back(string(1,dir[i]));
            }
        }
        cout << "Moves: ";
        for(string move: moves){ // Follow cube coordinate system for hexagonals
            cout << move << ' ';
            tile_coord.move(move);
        }
        cout << "Final tile coordinate: ";
        cout << "X: " << tile_coord.x << " Y: " << tile_coord.y << '\n';
        cout << '\n';
        string tile_coord_str = tile_coord.repr();
        if(!tiles.count(tile_coord_str)){
            tiles[tile_coord_str] = true; // It's black
        } else {
            tiles[tile_coord_str] = !tiles[tile_coord_str];
        }
    }
    for (auto& tile_coord: tiles){
        cout << tile_coord.first << '\n';
        cout << tile_coord.second << '\n';
        if(tile_coord.second){
            num_black++;
        }
    }
    cout << "Number of black tiles: " << num_black << '\n';
}
