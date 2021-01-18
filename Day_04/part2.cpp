// #include <cstddef>
// #include <cstdint>
// #include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>
#include <tuple>
// #include <vector>
using namespace std;

void print(std::set<string> const &s)
{
    std::copy(s.begin(),
            s.end(),
            std::ostream_iterator<string>(std::cout, " "));
}

tuple<bool, long> is_number(string const &s){
    // Assume it's int size since... the inputs want it
    char* p;
    long converted = std::strtol(s.c_str(), &p, 10);
    if (*p) {
      // conversion failed because the input wasn't a number
        return {false,-1};
    } else {
      // use converted
        return {true,converted};
    }
}



bool parse_byr(string const &s){
    tuple<bool,long> res = is_number(s);
    bool it_is_number = get<0>(res);
    long number = get<1>(res);
    if (it_is_number){
        if(number >= 1920 && number <= 2002){
            return true;
        }
    }
    return false;
}

bool parse_iyr(string const &s){
    tuple<bool,long> res = is_number(s);
    bool it_is_number = get<0>(res);
    long number = get<1>(res);
    if (it_is_number){
        if(number >= 2010 && number <= 2020){
            return true;
        }
    }
    return false;
}

bool parse_eyr(string const &s){
    tuple<bool,long> res = is_number(s);
    bool it_is_number = get<0>(res);
    long number = get<1>(res);
    if (it_is_number){
        if(number >= 2020 && number <= 2030){
            return true;
        }
    }
    return false;
}

bool parse_hgt(string const &s){
    string unit = s.substr(s.length()-2);
    cout << "Height unit !!!" << unit << '\n';
    if (unit != "cm" and unit != "in") return false;

    string height_string = s.substr(0,s.length()-2);
    cout << "Height !!!" << height_string << '\n';
    tuple<bool,long> res = is_number(s.substr(0,s.length()-2));
    bool it_is_number = get<0>(res);
    long height = get<1>(res);
    cout << "Height !!!" << height << '\n';
    if (it_is_number){
        if (unit == "cm"){
            if (height >= 150 && height <= 193){
                return true;
            }
        } else if (unit == "in") {
            if (height >= 59 && height <= 76){
                return true;
            }
        }
    }
    return false;
}

bool parse_hcl(string const &s){
    string validString = "0123456789abcdef";
    char prefix = s.at(0);
    if(prefix != '#') return false;

    string hcl = s.substr(1);
    for (char character: hcl){
        if (validString.find(character) == string::npos){
            return false;
        }
    }
    return true;
}

bool parse_ecl(string const &s){
    set<string> valid_eye_colors = {"amb","blu","brn","gry","grn","hzl","oth"};
    if (valid_eye_colors.find(s) != valid_eye_colors.end()) return true;
    return false;
}

bool parse_pid(string const &s){
    if (s.length() != 9){
        return false;
    }
    tuple<bool,long> res = is_number(s);
    bool is_number = get<0>(res);
    return is_number;
}

bool parse_cid(string const &s){
    return true;
}

bool parser_factory(string const &key, string const &s){
    cout << key << ' ' <<  s << ' ' << '\n';
    if (key == "byr") return parse_byr(s);
    if (key == "iyr") return parse_iyr(s);
    if (key == "eyr") return parse_eyr(s);
    if (key == "hgt") return parse_hgt(s);
    if (key == "hcl") return parse_hcl(s);
    if (key == "ecl") return parse_ecl(s);
    if (key == "pid") return parse_pid(s);
    if (key == "cid") return parse_cid(s);
    return false;
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
            value = kv.substr(kv.find(':')+1);
            cout << "Field is: " << field << " Value is: " << value << '\n';
            bool is_field_valid = parser_factory(field,value);
            cout << is_field_valid << '\n';
            if (is_field_valid){
                fields.insert(field);
            }
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
