#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void PrintVectorPart(const vector<int>& numbers)
{
    auto negative = find_if(begin(numbers), end(numbers),
                            [](const int& n) { return n < 0; });

    auto it = negative;

    while (it != begin(numbers))
    {
        --it;
        cout << *it << " ";
    }
}


int main()
{
    PrintVectorPart({6, 1, 8, -5, 4});
    cout << endl;
    PrintVectorPart({-6, 1, 8, -5, 4}); // ничего не выведется
    cout << endl;
    PrintVectorPart({6, 1, 8, 5, 4});
    cout << endl;
    return 0;
}
