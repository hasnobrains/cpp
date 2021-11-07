#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main()
{
    int n = 0;

    cin >> n;

    vector<int> v(n);

    iota(v.rbegin(), v.rend(), 1);

    do
    {
        for (auto& e : v)
        {
            cout << e << " ";
        }
        cout << endl;
    } while (prev_permutation(v.begin(), v.end()));

    return 0;
}
