#include <iostream>
#include <random>
#include <ctime>
#include <string>

using namespace std;

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