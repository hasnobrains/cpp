#include <iostream>
#include <vector>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith_mentors(RandomIt range_begin,
                                                RandomIt range_end, char prefix)
{

    // Все строки, начинающиеся с '<prefix>', больше или равны строке "<prefix>"
    auto left = lower_bound(range_begin, range_end, string(1, prefix));

    // Составим следующий в алфавите символ.
    // Не страшно, если prefix = 'z':
    // в этом случае мы получим следующий за 'z' символ в таблице символов
    char next_prefix = static_cast<char>(prefix + 1);

    // Строка "<next_prefix>" в рамках буквенных строк
    // является точной верхней гранью
    // множества строк, начнающихся с '<prefix>'
    auto right = lower_bound(range_begin, range_end, string(1, next_prefix));

    return {left, right};
}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin,
                                        RandomIt range_end, char prefix)
{
    struct comp
    {
        bool operator()(const string& s, const char c) const
        {
            return s.at(0) < c;
        }
        bool operator()(const char c, const string& s) const
        {
            return c < s.at(0);
        }
    };

    return make_pair(lower_bound(range_begin, range_end, prefix, comp{}),
                     upper_bound(range_begin, range_end, prefix, comp{}));
}

int main()
{
    const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};

    const auto m_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
    for (auto it = m_result.first; it != m_result.second; ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    const auto p_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
    cout << (p_result.first - begin(sorted_strings)) << " "
         << (p_result.second - begin(sorted_strings)) << endl;

    const auto z_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
    cout << (z_result.first - begin(sorted_strings)) << " "
         << (z_result.second - begin(sorted_strings)) << endl;

    // moscow murmansk
    // 2 2
    // 3 3

    return 0;
}
