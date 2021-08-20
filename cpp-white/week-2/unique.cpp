#include <iostream>
#include <set>
#include <string>

using namespace std;

int main()
{
    int n;
    cin >> n;

    set<string> uniq;

    while (n-- > 0)
    {
        string s;
        cin >> s;

        uniq.insert(s);
    }

    cout << uniq.size() << endl;
}
