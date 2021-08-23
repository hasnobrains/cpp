#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>

using namespace std;

bool my_sort(const string& x, const string& y)
{
    int size = x.size();

    if (size > y.size())
    {
        size = y.size();
    }

    for(int i = 0; i < size; i++)
    {
        char _x = tolower(x[i]);
        char _y = tolower(y[i]);

        if (_x == _y) continue;

        return _x < _y;
    }

    return true;

}

int main()
{
    int n;
    cin >> n;

    vector<string> v(n);

    for (auto& i: v)
    {
        cin >> i;
    }

    sort(begin(v), end(v), my_sort);

    for (auto& item: v)
    {
        cout << item << " ";
    }

    cout << endl;

    return 0;
}
