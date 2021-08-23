#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class SortedStrings {
    public:
        void AddString(const string& s) {
            // добавить строку s в набор
            sorted.push_back(s);
            sort(begin(sorted), end(sorted));
        }

        vector<string> GetSortedStrings() {
            // получить набор из всех добавленных строк в отсортированном порядке
            return sorted;
        }

    private:
        // приватные поля
        vector<string> sorted;
};


void PrintSortedStrings(SortedStrings& strings) {
    for (const string& s : strings.GetSortedStrings()) {
        cout << s << " ";
    }
    cout << endl;
}

int main() {
    SortedStrings strings;

    strings.AddString("first");
    strings.AddString("third");
    strings.AddString("second");
    PrintSortedStrings(strings);

    strings.AddString("second");
    PrintSortedStrings(strings);

    return 0;
}

