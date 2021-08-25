#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ifstream input("input.txt");

    int n, m;

    if (input)
    {
        input >> n;
        input.ignore(1);
        input >> m;
    }

    for (int i = n; i > 0; i--)
    {
        for (int j = m; j > 0; j--)
        {
            int v;
            input >> v;
            cout << setw(10) << v << (j == 1 ? "" : " ");
            input.ignore(1);
        }

        cout << (i == 1 ? "" : "\n");
    }
}
