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
vector<string> image;
vector<vector<string>> image_orientations;
vector<string> sea_monster = {"                  # ","#    ##    ##    ###"," #  #  #  #  #  #   "};

void generate_image(){
    for(int i = 0 ; i < GRID_SIZE; i ++){
        for(int j = 0 ; j < GRID_SIZE; j ++){
            if (j == 0){
                for(int k = 1 ; k < S-1; k ++){
                    image.push_back(grid[i][j].body[k].substr(1,S-2));
                }
            } else {
                for(int k = 1 ; k < S-1; k ++){
                    cout << "DEBUG: image size" << image.size() << " index: " << i*(S-2) + k-1 << '\n';
                    image[i*(S-2) + k-1] += grid[i][j].body[k].substr(1,S-2);
                }
            }
        }
    }
}

int num_hash_image(vector<string>& rot_image){
    int num_hash = 0;
    for (string image_line: rot_image){
        for (char image_char : image_line){
            if(image_char == '#'){
                num_hash++;
            }
        }
    }
    return num_hash;
}


int count_seamonsters(){
    int num_seamonsters = 0;
    int image_rows = image.size();
    int image_cols = image[0].length();
    int seamon_rows = sea_monster.size();
    int seamon_cols = sea_monster[0].length();
    for (vector<string> rot_image : image_orientations) {
      for (int i = 0; i + seamon_rows - 1 < image_rows; i++) {
        for (int j = 0; j + seamon_cols - 1 < image_cols; j++) {
          bool found = true;
          for (int k = 0; k < seamon_rows; k++) {
            for (int l = 0; l < seamon_cols; l++) {
              if (sea_monster[k][l] == ' ') {
                continue;
              }
              if (sea_monster[k][l] =='#' && rot_image[i + k][j + l] == '.') {
                found = false;
              }
            }
          }
          if (!found) {
              continue;
          }
          num_seamonsters++;
          for (int k = 0; k < seamon_rows; k++) {
            for (int l = 0; l < seamon_cols; l++) {
              if (sea_monster[k][l] == '#') {
                rot_image[i+k][j+l] = 'O';
              }
            }
          }
        }
      }
      if(num_seamonsters > 0){
          cout << "Rough sea with monsters " << '\n';
          for(string sealine : rot_image){
              cout << sealine << '\n';
          }
          cout << '\n';
          cout << "Number of seamonsters found: " << num_seamonsters << '\n';
          return(num_hash_image(rot_image));
      }
    }
    return 0;
}

void generate_image_orientations(){
    vector<string> ref_image = image;
    vector<string> new_image;
    for (int j = 0; j < 4; j++) {
      for (int i = 0; i < ref_image.size(); i++) {
        // Rotate by 90 degrees clockwise
        string rotated_line = "";
        for (string line : ref_image) {
            // cout << "Ref body line" << line << '\n';
          rotated_line.insert(rotated_line.begin(), line[i]);
        }
        // cout << "Rotated line: " << rotated_line << " Ref body line: " << ref_body[i] << '\n';
        new_image.push_back(rotated_line);
      }
      image_orientations.push_back(new_image);
      ref_image = new_image;
      new_image.clear();
    }

    vector<vector<string>> flipped_images;
    vector<string> new_flipped_image;
    for (vector<string> rotated_image: image_orientations){
        // vector<string> new_flipped_image;
        new_flipped_image = rotated_image;
        reverse(new_flipped_image.begin(),new_flipped_image.end());
        flipped_images.push_back(new_flipped_image);
        new_flipped_image.clear();
    }
    image_orientations.insert(image_orientations.end(),flipped_images.begin(),flipped_images.end());
}

void print_image_orientations() {
  int orientation_num = 0;
  for (vector<string> rot_image : image_orientations) {
    cout << "Image orientation: " << orientation_num << '\n';
    for (string image_line : rot_image) {
      cout << image_line << '\n';
    }
    cout << '\n';
    orientation_num++;
  }
}

void search(int row, int col, set<int> &visited) {
  if (row == GRID_SIZE) {
    // print();
    cout << "Did I reach here?" << '\n';
    printf("product = %lld\n", (long long)grid[0][0].id *
                                   grid[GRID_SIZE - 1][0].id *
                                   grid[0][GRID_SIZE - 1].id *
                                   grid[GRID_SIZE - 1][GRID_SIZE - 1].id);
    generate_image();
    generate_image_orientations();
    print_image_orientations();
    // int num_hash = num_hash_image();
    int roughness = count_seamonsters();
    // cout << "Number of seamonsters found: " << num_seamonsters << '\n';
    cout << "Roughness : " << roughness << '\n';
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
            cout << "Tile id: " << tiles.id << " orientation " << orientation_num <<'\n';
            for (string line: tiles.body){
                cout << line << '\n';
            }
            cout << '\n';
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
    cout << "Reached? " << '\n';

    // Perform backtracking and see which tiles fit
    GRID_SIZE = llround(sqrt(tileset.size()));
    cout << "Grid size: " << GRID_SIZE << '\n';
    set<int> visited_ids;
    search(0, 0, visited_ids);
    // generate_image();
    // generate_image_orientations();
    // print_image_orientations();
    // int num_seamonsters = count_seamonsters();
    // cout << "Number of seamonsters found: " << num_seamonsters << '\n';
}
