#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <sstream>
#include <string>
using namespace std;


int main() {
    string input_s;

    char ch;

    getline(cin, input_s);

    stringstream ss(input_s);
    
    vector<int> v;

    for(int number; ss >> number;){
        v.push_back(number);
        ss >> ch;
    }

    for(size_t i = 0 ; i < v.size(); i++){
        cout<< v[i] <<endl;
    }
    
}
