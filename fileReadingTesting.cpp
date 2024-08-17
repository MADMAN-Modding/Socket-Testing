#include <iostream>
#include <fstream>

using namespace std;
int main() {
    ifstream file("test.txt");

    string line;

    while (getline(file, line)) {
        cout << line;
    }

    return 0;
}