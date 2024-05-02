#include <iostream>
#include <random>
#include <ctime>
#include <string>

using namespace std;

inline void ltrim(string &str) {
    str.erase(str.begin(), find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));
}

inline void rtrim(string &str) {
    str.erase(find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), str.end());
}

inline void trim(string &str) {
    rtrim(str);
    ltrim(str);
}

string generateRandomLabel() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis('A', 'Z');
    string label;
    
    for (int i = 0; i < 8; ++i) {
        label += static_cast<char>(dis(gen));
    }

    return label;
}