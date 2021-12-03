#include <iostream>
#include <set>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border)
// set<int>::const_iterator —
// тип итераторов для константного множества целых чисел
{
    auto it =numbers.lower_bound(border);

    if (it == numbers.begin())
    {
        return it;
    }

    if (it == numbers.end())
    {
        return prev(it);
    }

    if (border - *prev(it) <= *it - border)
    {
        return prev(it);
    }
    else
    {
        return it;
    }
}

int main()
{
    set<int> numbers = {1, 4, 6};
    cout << *FindNearestElement(numbers, 0) << " "
         << *FindNearestElement(numbers, 3) << " "
         << *FindNearestElement(numbers, 5) << " "
         << *FindNearestElement(numbers, 6) << " "
         << *FindNearestElement(numbers, 100) << endl;

    set<int> empty_set;

    cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;

    // 1 4 4 6 6
    // 1

    return 0;
}
