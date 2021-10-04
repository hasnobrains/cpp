#include <iostream>
#include <map>

using namespace std;

template <typename K, typename V> V& GetRefStrict(map<K, V>& m, K k)
{
    if (m.count(k) == 0)
    {
        throw runtime_error("No element!");
    }

    return m[k];
}

int main()
{
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue

    return 0;
}
