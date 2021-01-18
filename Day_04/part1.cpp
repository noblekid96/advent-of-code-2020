// #include <cstddef>
// #include <cstdint>
// #include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>
// #include <tuple>
// #include <vector>
using namespace std;

void print(std::set<string> const &s)
{
    std::copy(s.begin(),
            s.end(),
            std::ostream_iterator<string>(std::cout, " "));
}

int main(){
    ifstream infile;
    infile.open("input.txt");

    string line;
    stringstream linestream;
    string kv;
    string field;
    string value;
    int num_valid_passports = 0;
    set<string> fields;
    set<string> required_fields = {"byr","iyr","eyr","hgt","hcl","ecl","pid","cid"};
    required_fields.erase("cid"); // Optional
    cout << "Required";
    print(required_fields);


    while(getline(infile,line)){
        if (line.length() == 0){
            cout << "Passport fields" << '\n';
            print(fields);
            cout << '\n';
            bool is_valid = true;
            cout << "Empty line detected!!! Passport parsed !!!" << '\n';
            for (string required_field : required_fields){
                if ( fields.find(required_field) == fields.end()){
                    // Invalid passport
                    is_valid = false;
                    break;
                }
            }
            if (is_valid == true){
                cout << "Passport with fields: "; print(fields); cout << " is valid\n";
                num_valid_passports++;
            }
            fields.clear();
        }

        linestream.str(line);
        while (linestream >> kv){
            field = kv.substr(0,kv.find(':'));
            value = kv.substr(kv.find(':'));
            cout << "Field is: " << field << " Value is: " << value << '\n';
            fields.insert(field);
        }
        linestream.clear();
    }
    cout << "Passport fields" << '\n';
    print(fields);
    cout << '\n';
    bool is_valid = true;
    cout << "Empty line detected!!! Passport parsed !!!" << '\n';
    for (string required_field : required_fields){
        if ( fields.find(required_field) == fields.end()){
            // Invalid passport
            is_valid = false;
            break;
        }
    }
    if (is_valid == true){
        cout << "Passport with fields: "; print(fields); cout << " is valid\n";
        num_valid_passports++;
    }

    cout << "Number of valid passports: " << num_valid_passports << '\n';
}
