#ifdef MYENV

#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

enum class Lang
{
    DE,
    FR,
    IT
};


struct Region
{
    string std_name;
    string parent_std_name;
    map<Lang, string> names;
    int64_t population;
};

#endif

auto TieRegionFields(const Region& region)
{
    return make_tuple(region.std_name, region.parent_std_name, region.names,
                      region.population);
}

int FindMaxRepetitionCount(const vector<Region>& regions)
{
    int max = 0;

    map<tuple<string, string, map<Lang, string>, int64_t>, int> m;

    for (auto region : regions)
    {
        auto t = TieRegionFields(region);

        if (m.count(t))
        {
            // cout << region.std_name << " +1" << endl;
            m[t] += 1;

            if (max < m[t])
                max = m[t];
        }
        else
        {
            // cout << region.std_name << " new" << endl;
            m[t] = 1;

            if (max < m[t])
                max = m[t];
        }
    }

    return max;
}

#ifdef MYENV

int main()
{
    cout << FindMaxRepetitionCount({
                {"Moscow",
                 "Russia",
                 {{Lang::DE, "Moskau"},
                  {Lang::FR, "Moscou"},
                  {Lang::IT, "Mosca"}},
                 89},
                {"Russia",
                 "Eurasia",
                 {{Lang::DE, "Russland"},
                  {Lang::FR, "Russie"},
                  {Lang::IT, "Russia"}},
                 89},
                {"Moscow",
                 "Russia",
                 {{Lang::DE, "Moskau"},
                  {Lang::FR, "Moscou"},
                  {Lang::IT, "Mosca"}},
                 89},
                {"Moscow",
                 "Russia",
                 {{Lang::DE, "Moskau"},
                  {Lang::FR, "Moscou"},
                  {Lang::IT, "Mosca"}},
                 89},
                {"Russia",
                 "Eurasia",
                 {{Lang::DE, "Russland"},
                  {Lang::FR, "Russie"},
                  {Lang::IT, "Russia"}},
                 89},
            })
         << endl;

    cout << FindMaxRepetitionCount({
                {"Moscow",
                 "Russia",
                 {{Lang::DE, "Moskau"},
                  {Lang::FR, "Moscou"},
                  {Lang::IT, "Mosca"}},
                 89},
                {"Russia",
                 "Eurasia",
                 {{Lang::DE, "Russland"},
                  {Lang::FR, "Russie"},
                  {Lang::IT, "Russia"}},
                 89},
                {"Moscow",
                 "Russia",
                 {{Lang::DE, "Moskau"},
                  {Lang::FR, "Moscou deux"},
                  {Lang::IT, "Mosca"}},
                 89},
                {"Moscow",
                 "Toulouse",
                 {{Lang::DE, "Moskau"},
                  {Lang::FR, "Moscou"},
                  {Lang::IT, "Mosca"}},
                 89},
                {"Moscow",
                 "Russia",
                 {{Lang::DE, "Moskau"},
                  {Lang::FR, "Moscou"},
                  {Lang::IT, "Mosca"}},
                 31},
            })
         << endl;

    return 0;
}

#endif
