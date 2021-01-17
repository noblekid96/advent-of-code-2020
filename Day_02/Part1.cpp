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
        // cout << range << ' ' << letter_input << ' ' << password << ' ' << '\n';
        string count_delimiter = "-";
        int min_count = stoi(range.substr(0,range.find(count_delimiter)));
        int max_count = stoi(range.substr(range.find(count_delimiter)+count_delimiter.length(),range.size()));
        // cout << min_count << ' ' << max_count << '\n';

        char letter = letter_input.at(0);


        // cout << letter << '\n';
        // cout << password << '\n';
        int charCount = 0;
        for (char character : password){
            if (character == letter){
                charCount++;
            }
        }
        // cout << charCount << '\n';
        if (min_count <= charCount && charCount <= max_count){
            // cout << password + " is valid!" << '\n';
            num_valid_passwords++;
        }
    }
    cout << "Number of valid passwords: " << num_valid_passwords << '\n';
    return 0;
}
