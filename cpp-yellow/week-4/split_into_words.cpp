#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> SplitIntoWords(const string& s)
{
    vector<string> v;

    for (auto it = begin(s); it != end(s); ++it)
    {
        auto whitespace = find_if(it, end(s), [](auto& c) { return c == ' '; });
        v.push_back({it, whitespace});
        if (whitespace == end(s))
        {
            break;
        }
        it = whitespace;
    }

    return v;
}

int main()
{
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it)
    {
        if (it != begin(words))
        {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}
