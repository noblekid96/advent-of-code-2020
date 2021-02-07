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
#include <bitset>
using namespace std;

int main(){
    string line;
    vector<int> my_ticket;
    stringstream parser;
    set<int> valid_nums;
    unordered_map<string,set<int>> fields;
    set<string> all_fields;
    vector<vector<int>> valid_ticket_fields;
    bool finding_invalid = false;
    long long sum = 0;

    while(getline(cin,line)){
        string tmp = "";
        if (line == "your ticket:") {
          // cout << "Hello" << '\n';
          getline(cin, line);
          parser.clear();
          parser << line;
          while(getline(parser,tmp,',')){
            int field = atoi(tmp.c_str());
            my_ticket.push_back(field);
          }
          finding_invalid = true;
          continue;
        }
        if (finding_invalid && line.find(',') != string::npos) {
          parser.clear();
          parser << line;
          int pos = 0;
          vector<int> ticket_fields;
          bool is_valid = true;
          while (getline(parser, tmp, ',')) {
            int field = atoi(tmp.c_str());
            if (valid_nums.find(field) == valid_nums.end()) {
              is_valid = false;
            }
            ticket_fields.push_back(field);
          }
          if(is_valid){
            valid_ticket_fields.push_back(ticket_fields);
          }
        } else if (!finding_invalid){
          parser.clear();
          parser << line;
          set<int> field_nums;
          string field_name;
          int delim_idx = line.find(':');
          if (delim_idx != string::npos){
            field_name = line.substr(0, delim_idx);
            fields[field_name] = field_nums;
            all_fields.insert(field_name);
            // cout << "Field name: " << field_name << '\n';
          }

          while (getline(parser, tmp, ' ')) {
            // if (tmp.find(':') != string::npos) {
            //   field_name = tmp.substr(0,tmp.length()-1);
            //   fields[field_name] = field_nums;
            //   all_fields.push_back(field_name);
            //   cout << "Field name: " << field_name << '\n';
            //   }
            if (tmp.find('-') != string::npos) {
              int delim_idx = tmp.find('-');
              int bound1 = atoi(tmp.substr(0, delim_idx).c_str());
              int bound2 =
                  atoi(tmp.substr(delim_idx + 1, tmp.length()).c_str());
              // cout << "Bounds: " << bound1 << ',' << bound2 << '\n';
              for (int i = bound1; i <= bound2; i++) {
                valid_nums.insert(i);
                fields[field_name].insert(i);
              }
            }
          }
        }
    }

    // Check which fields is which position of the ticket
    unordered_map<int,set<string>> positions_field_names;
    for (int i = 0 ; i < my_ticket.size(); i ++ ){
      positions_field_names[i] = all_fields;
    }

    // cout << "Ticket fields" << '\n';
    // for(vector<int> ticket_fields : valid_ticket_fields){
    //   for(int field: ticket_fields){
    //     // cout << field << ", ";
    //   }
    //   // cout << "Next "<< '\n';
    // }

    for (vector<int> ticket_fields : valid_ticket_fields) {
      for (int pos = 0 ; pos < ticket_fields.size(); pos ++ ) {
        int pos_value = ticket_fields[pos];
        // set<string> possible_pos_fields = positions_field_names[pos];
        set<string> new_possible_pos_fields;
        for( string possible_pos_field: positions_field_names[pos]){
          if (fields[possible_pos_field].find(pos_value) != fields[possible_pos_field].end()){
            new_possible_pos_fields.insert(possible_pos_field);
          }
        }
        positions_field_names[pos] = new_possible_pos_fields;
      }
    }
    // unordered_map<string,vector<int>> possible_fields_positions;
    for(auto& pos_fields: positions_field_names){
      // cout << "Position: " << pos_fields.first << " Field Names: ";
      for(string field_name : pos_fields.second){
        // cout << field_name;
        // cout << ", ";
        // possible_fields_positions[field_name].push_back(pos_fields.first);
      }
      // cout << '\n';
    }
    unordered_map<int, string> definite_pos_fields;
    set<string> found;
    for (int i = 0; i < all_fields.size(); i++) {
      for (string field : all_fields) {
        if(found.find(field) != found.end()){
          continue;
        }
        int num_occurences = 0;
        vector<int> occured_at = {};
        for (int j = 0; j < all_fields.size(); j++) {
          if (positions_field_names[j].find(field) !=
              positions_field_names[j].end()) {
            num_occurences++;
            // cout << "Found it: " << field << " at " << j << '\n';
            occured_at.push_back(j);
          }
        }
        // cout << "Num occurences: " << num_occurences << " for field: " << field << '\n';
        if (num_occurences == 1) {
          // cout << "Found it only at: " << field << " at " << occured_at[0] << '\n';
          set<string> new_set;
          new_set.insert(field);
          found.insert(field);
          positions_field_names[occured_at[0]] = new_set;
          definite_pos_fields[occured_at[0]] = field;
        }
      }
    }

    unsigned long long result = 1;
    for (auto& definite_pos_field: definite_pos_fields){
      // cout << '{' << definite_pos_field.first << ':' << definite_pos_field.second << '}' << ',';
      if (definite_pos_field.second.find("departure") != string::npos){
      //   cout << "My ticket field Idx: " << definite_pos_field.first << '\n';
      //   cout << "My ticket field value: " <<  my_ticket[definite_pos_field.first] << '\n';
        result *= my_ticket[definite_pos_field.first];
      }
    }
    cout << "result: " << result << '\n';


    // for(auto& pos_fields: possible_fields_positions){
    //   cout << "Field name: " << pos_fields.first << " Positions : ";
    //   for(int positions : pos_fields.second){
    //     cout << positions;
    //     cout << ", ";
    //   }
    //   cout << '\n';
    // }
    // for (int i : fields["row"]){
    //   cout << i << ' ' << '\n';
    // }
// cout << "Sum of invalid numbers: " << sum << '\n';
}
