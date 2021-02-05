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

int main(){
    string line;
    set<double > buses;
    double arrival = -1;
    double closest_departure = 99999999999;
    double earliest_busid = -1;
    while(getline(cin,line)){
        if(arrival == -1){
            arrival = atoi(line.c_str());
        } else {
            stringstream ss(line);
            while( ss.good() ){
                string substr;
                getline(ss, substr, ',');
                if (substr != "x"){
                    buses.insert(atoi(substr.c_str()));
                }
            }
        }
    }

    // End of input parsing
    for (double bus_id: buses){
        double quotient = arrival / bus_id;
        double next_departure = ceil(quotient) * bus_id;
        if (next_departure < closest_departure){
            closest_departure = next_departure;
            earliest_busid = bus_id;
        }
    }
    cout << "Earliest bus id: " << earliest_busid << " Earliest departure: " << closest_departure << '\n';
    cout << "Answer: " << earliest_busid * (closest_departure - arrival) << '\n';
}
