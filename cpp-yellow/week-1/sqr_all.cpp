#include <iostream>
#include <map>
#include <vector>

using namespace std;

template <typename Collection> Collection Sqr(const Collection& c);

template <typename Collection> Collection Sqr(const Collection& c)
{
    Collection new;
    for (const auto& item : c)
    {
        newitem* item;
    }
}


int main()
{
    // Пример вызова функции
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v))
    {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {{4, {2, 2}}, {7, {4, 3}}};
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs))
    {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second
             << endl;
    }
    return 0;
}
