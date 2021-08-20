#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

set<string> BuildMapValuesSet(const map<int, string>& m)
{
    set<string> s;
    for (const auto& v: m)
    {
        s.insert(v.second);
    }
    return s;
}

