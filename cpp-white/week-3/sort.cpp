#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> v(n);

    for (auto& i: v)
    {
        cin >> i;
    }

    sort(begin(v), end(v), [](int x, int y){ return abs(x) < abs(y); });

    for (auto& item: v)
    {
        cout << item << " ";
    }

    cout << endl;

    return 0;
}
