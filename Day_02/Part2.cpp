#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(){
    ifstream infile;
    infile.open("input.txt");

    string range;
    string letter_input;
    string password;

    int num_valid_passwords;
    while(infile >> range >> letter_input >> password){
        cout << range << ' ' << letter_input << ' ' << password << ' ' << '\n';
        string count_delimiter = "-";
        int position1 = stoi(range.substr(0,range.find(count_delimiter)));
        int position2 = stoi(range.substr(range.find(count_delimiter)+count_delimiter.length(),range.size()));
        // cout << min_count << ' ' << max_count << '\n';

        char letter = letter_input.at(0);

        if (password.at(position1-1) == letter ^ password.at(position2-1) == letter ){
            cout << password + " is valid!" << '\n';
            num_valid_passwords++;
        }
    }
    cout << "Number of valid passwords: " << num_valid_passwords << '\n';
    return 0;
}
