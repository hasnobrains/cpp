#include <iostream>
#include <set>
#include <map>
#include <string>

using namespace std;

int main()
{
    int counter = 1;
    map<set<string>, int> buses;

    int q;

    cin >> q;

    while (q-- > 0)
    {
        int n;
        cin >> n;

        set<string> bus;

        while (n-- > 0)
        {
            string stop;
            cin >> stop;
            bus.insert(stop);
        }

        if (buses.count(bus) != 0)
        {
            cout << "Already exists for " << buses[bus] << endl;
        }
        else
        {
            cout << "New bus " << counter << endl;
            buses[bus] = counter++;
        }
    }

    return 0;
}
