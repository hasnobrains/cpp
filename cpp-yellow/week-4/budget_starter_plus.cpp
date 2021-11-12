#include "test_runner.h"
#include <chrono>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

pair<string, string> SplitTwoStrict(string s, string delimiter)
{
    const size_t pos = s.find(delimiter);
    if (pos == s.npos)
    {
        return {s, ""};
    }
    else
    {
        return {s.substr(0, pos), s.substr(pos + delimiter.length())};
    }
}

pair<string, string> SplitTwo(string s, string delimiter)
{
    const auto [lhs, rhs] = SplitTwoStrict(s, delimiter);
    return {lhs, rhs};
}

string ReadToken(string& s, string delimiter = " ")
{
    const auto [lhs, rhs] = SplitTwo(s, delimiter);
    s = rhs;
    return lhs;
}

int ConvertToInt(string str)
{
    size_t pos;
    const int result = stoi(string(str), &pos);
    if (pos != str.length())
    {
        stringstream error;
        error << "string " << str << " contains " << (str.length() - pos)
              << " trailing chars";
        throw invalid_argument(error.str());
    }
    return result;
}

class Date
{
  public:
    static Date FromString(string str)
    {
        const int year = ConvertToInt(ReadToken(str, "-"));
        const int month = ConvertToInt(ReadToken(str, "-"));
        const int day = ConvertToInt(str);
        return {year, month, day};
    }

    // Weird legacy, can't wait for chrono::year_month_day
    time_t AsTimestamp() const
    {
        tm t;
        t.tm_sec = 0;
        t.tm_min = 0;
        t.tm_hour = 0;
        t.tm_mday = day_;
        t.tm_mon = month_ - 1;
        t.tm_year = year_ - 1900;
        t.tm_isdst = 0;
        return mktime(&t);
    }

  private:
    int year_;
    int month_;
    int day_;

    Date(int year, int month, int day) : year_(year), month_(month), day_(day)
    {
    }
};

int ComputeDaysDiff(const Date& date_to, const Date& date_from)
{
    const time_t timestamp_to = date_to.AsTimestamp();
    const time_t timestamp_from = date_from.AsTimestamp();
    static constexpr int SECONDS_IN_DAY = 60 * 60 * 24;
    return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
}

static const Date START_DATE = Date::FromString("1700-01-01");
static const Date END_DATE = Date::FromString("2100-01-01");
static const size_t DAY_COUNT = ComputeDaysDiff(END_DATE, START_DATE);

void Test()
{
    {
        vector<int> money(DAY_COUNT);
        vector<int> result(DAY_COUNT);

        money[0] = 10;
        money[100] = 10;
        money[1000] = 10;
        money[146095] = 10;

        partial_sum(money.begin(), money.end(), result.begin());
        cout << result[146095] << endl;
        cout << result[0] << endl;
        cout << result[100] << endl;
        cout << result[1000] << endl;
    }
}

int main()
{
    // TestRunner tr;
    // tr.RunTest(Test, "Test");
    // return 0;

    vector<uint64_t> money(DAY_COUNT, 0);
    vector<uint64_t> result(DAY_COUNT, 0);
    size_t e, q;

    cin >> e;

    for (size_t i = 0; i < e; ++i)
    {
        string d;
        cin >> d;
        Date date = Date::FromString(d);
        auto j = ComputeDaysDiff(date, START_DATE);
        cin >> money[j];
    }

    partial_sum(money.begin(), money.end(), result.begin());

    cin >> q;

    for (size_t i = 0; i < q; ++i)
    {
        string f, t;
        cin >> f >> t;
        Date from = Date::FromString(f);
        Date to = Date::FromString(t);
        auto start_indx = ComputeDaysDiff(from, START_DATE);
        auto finish_indx = ComputeDaysDiff(to, START_DATE);

        if (start_indx <= 0)
        {
            cout << result[finish_indx] << endl;
        }
        else
        {
            cout << result[finish_indx] - result[start_indx - 1] << endl;
        }
    }

    return 0;
}
