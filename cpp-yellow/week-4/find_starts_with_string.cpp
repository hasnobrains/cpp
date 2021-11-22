#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt>
FindStartsWith_mentors(RandomIt range_begin, RandomIt range_end, string prefix)
{

    // Все строки, начинающиеся с prefix, больше или равны строке "<prefix>"
    auto left = lower_bound(range_begin, range_end, prefix);

    // Составим строку, которая в рамках буквенных строк является
    // точной верхней гранью множества строк, начинающихся с prefix
    string upper_bound = prefix;
    ++upper_bound[upper_bound.size() - 1];

    // Первое встреченное слово, не меньшее upper_bound,
    // обязательно является концом полуинтервала
    auto right = lower_bound(range_begin, range_end, upper_bound);

    return {left, right};
}

template <typename RandomIt>
pair<RandomIt, RandomIt>
FindStartsWith(RandomIt range_begin, RandomIt range_end, const string& prefix)
{
    // cout << "prefix -> " << prefix << " [";
    // for (auto it = range_begin; it != range_end; ++it)
    // {
    //     cout << (it != range_begin ? ", " : "") << *it;
    // }
    // cout << "]" << endl;

    // auto comp = [](const string& s1, const string& s2) {
    //     for (size_t i = 0; i < s1.size() && i < s2.size(); ++i)
    //     {
    //         if (s1[i] < s2[i])
    //         {
    //             return true;
    //         }
    //         if (s2[i] < s1[i])
    //         {
    //             return false;
    //         }
    //     }
    //
    //     return false;
    // };
    //
    auto comp = [](const string& s1, const string& s2) {
        return s1.compare(0, s2.size(), s2, 0, s2.size()) < 0;
    };

    auto lower_it = lower_bound(range_begin, range_end, prefix, comp);
    string prefix2 = prefix;
    ++(prefix2.back());
    auto upper_it = lower_bound(range_begin, range_end, prefix2, comp);

    return make_pair(lower_it, upper_it);
}

void Test()
{
    {
        const vector<string> sorted_strings = {"aaa", "aaa", "aaaaaaa",
                                               "aaaaaaaaaaaaaa"};

        const auto result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), "aaa");
        for (auto it = result.first; it != result.second; ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
        cout << (result.first - begin(sorted_strings)) << " "
             << (result.second - begin(sorted_strings)) << endl;
    }
    {
        const vector<string> sorted_strings = {"moscow", "motovilikha",
                                               "murmansk"};

        const auto result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), {});
        for (auto it = result.first; it != result.second; ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
        cout << (result.first - begin(sorted_strings)) << " "
             << (result.second - begin(sorted_strings)) << endl;
    }
    {
        const vector<string> sorted_strings = {};

        const auto result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), "mos");
        for (auto it = result.first; it != result.second; ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
        cout << (result.first - begin(sorted_strings)) << " "
             << (result.second - begin(sorted_strings)) << endl;
    }
    {
        const vector<string> sorted_strings = {"moscow", "motovilikha",
                                               "murmansk"};

        const auto result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), "mov");
        for (auto it = result.first; it != result.second; ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
        cout << (result.first - begin(sorted_strings)) << " "
             << (result.second - begin(sorted_strings)) << endl;
    }
    {
        const vector<string> sorted_strings = {"moscow", "motovilikha",
                                               "murmansk"};

        const auto result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), "love");
        for (auto it = result.first; it != result.second; ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
        cout << (result.first - begin(sorted_strings)) << " "
             << (result.second - begin(sorted_strings)) << endl;
    }
    {
        const vector<string> sorted_strings = {"moscow", "motovilikha",
                                               "murmansk"};

        const auto result =
            FindStartsWith(begin(sorted_strings), end(sorted_strings), "no");
        for (auto it = result.first; it != result.second; ++it)
        {
            cout << *it << " ";
        }
        cout << endl;
        cout << (result.first - begin(sorted_strings)) << " "
             << (result.second - begin(sorted_strings)) << endl;
    }
}

int main()
{
    // TestRunner tr;
    // tr.RunTest(Test, "Test");
    // return 0;

    const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};

    const auto mo_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
    for (auto it = mo_result.first; it != mo_result.second; ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    const auto mt_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
    cout << (mt_result.first - begin(sorted_strings)) << " "
         << (mt_result.second - begin(sorted_strings)) << endl;

    const auto na_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
    cout << (na_result.first - begin(sorted_strings)) << " "
         << (na_result.second - begin(sorted_strings)) << endl;

    // moscow motovilikha
    // 2 2
    // 3 3

    return 0;
}
