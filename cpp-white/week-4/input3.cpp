#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<double> v;
    ifstream input("input.txt");

    cout << fixed << setprecision(3);

    double value;

    while (input >> value)
    {
        cout << value << endl;
    }
}
