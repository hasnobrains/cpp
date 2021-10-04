#include <iostream>
#include <map>
#include <vector>

using namespace std;

template <typename T> T Sqr(T x);
template <typename T> vector<T> Sqr(vector<T> v);
template <typename K, typename V> map<K, V> Sqr(map<K, V> m);
template <typename K, typename V> pair<K, V> Sqr(pair<K, V> p);


template <typename T> T Sqr(T x) { return x * x; }

template <typename T> vector<T> Sqr(vector<T> v)
{
    for (auto& item : v)
    {
        item = Sqr(item);
    }
    return v;
}

template <typename K, typename V> map<K, V> Sqr(map<K, V> m)
{
    for (auto& [key, value] : m)
    {
        m[key] = Sqr(value);
    }
    return m;
}

template <typename K, typename V> pair<K, V> Sqr(pair<K, V> p)
{
    p.first = Sqr(p.first);
    p.second = Sqr(p.second);
    return p;
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
