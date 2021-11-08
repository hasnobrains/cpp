#include "test_runner.h"
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

using namespace std;

class Date
{
  public:
    Date() { timestamp = time(nullptr); };

    Date(int y, int m, int d)
    {
        if (NoSuchDate(y, m, d))
        {
            throw runtime_error("No such date: " + to_string(y) + to_string(m) +
                                to_string(d));
        }

        struct tm tm = {0, 0, 0, d, m - 1, y - 1900};
        timestamp = mktime(&tm);
    }

    bool NoSuchDate(int y, int m, int d)
    {
        int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if (m < 1 || m > 12)
        {
            // cerr << "Month value is invalid: " << m << endl;
            return true;
        }

        if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0))
        {
            ++days[1];
        }

        if (d < 1 || d > days[m - 1])
        {
            // cerr << "Day value is invalid: " << d << endl;
            return true;
        }

        return false;
    }

    time_t GetTimestamp() const { return timestamp; }

  private:
    time_t timestamp;
};

ostream& operator<<(ostream& os, const Date& date)
{
    time_t timestamp = date.GetTimestamp();
    struct tm* tm = localtime(&timestamp);
    os << setw(4) << setfill('0') << tm->tm_year + 1900 << "-" << setw(2)
       << tm->tm_mon + 1 << "-" << setw(2) << tm->tm_mday;
    return os;
}

Date ParseDate(const string& s)
{
    stringstream ss(s);

    int year, month, day;
    char c1, c2;

    ss >> year >> c1 >> month >> c2 >> day;

    if (ss.fail() || ss.peek() != EOF || c1 != '-' || c2 != '-')
    {
        cerr << "Wrong date format: " << s << endl;
        throw runtime_error("Wrong date format: " + s);
    }

    return Date(year, month, day);
}

istream& operator>>(istream& is, Date& date)
{
    string s;

    if (is)
    {
        is >> s;
        date = ParseDate(s);
    }

    return is;
}

const int seconds_per_day = 60 * 60 * 24;

int operator-(const Date& rhs, const Date& lhs)
{
    return difftime(rhs.GetTimestamp(), lhs.GetTimestamp()) / seconds_per_day;
}

bool operator<(const Date& lhs, const Date& rhs)
{
    return lhs.GetTimestamp() < rhs.GetTimestamp();
}

bool operator<=(const Date& lhs, const Date& rhs)
{
    return lhs.GetTimestamp() <= rhs.GetTimestamp();
}

bool cmp(const pair<time_t, double>& a, const pair<time_t, double>& b)
{
    return a.first < b.first;
}

class Budget
{
  public:
    void Earn(const Date& from, const Date& to, double amount)
    {
        int range = to - from + 1;

        if (range > 0)
        {
            amount /= range;
        }

        time_t from_timestamp = from.GetTimestamp();
        time_t to_timestamp = to.GetTimestamp();

        vector<pair<time_t, double>> b;

        for (time_t t = from_timestamp; t <= to_timestamp; t += seconds_per_day)
        {
            b.push_back(make_pair(t, amount));
        }

        vector<pair<time_t, double>> tmp;
        tmp.resize(v.size() + b.size());

        merge(begin(v), end(v), begin(b), end(b), begin(tmp), cmp);

        v = tmp;
    }

    double ComputeIncome(const Date& from, const Date& to)
    {
        auto fold = [from, to](double accumulator, pair<time_t, double> b) {
            if (b.first >= from.GetTimestamp() && b.first <= to.GetTimestamp())
            {
                return accumulator + b.second;
            }
            else
            {
                return accumulator;
            }
        };

        return accumulate(begin(v), end(v), 0.0, fold);
    }

  private:
    vector<pair<time_t, double>> v;
};

void Test()
{
    {
        Budget budget;
        double expected = 0.0;
        double income =
            budget.ComputeIncome(Date(2000, 2, 1), Date(2099, 2, 1));
        AssertEqual(income, expected, "empty");
    }
    {
        Budget budget;
        double expected = 0.0;
        double income =
            budget.ComputeIncome(Date(2099, 2, 1), Date(2000, 2, 1));
        AssertEqual(income, expected, "empty backwards");
    }
    {
        Budget budget;
        budget.Earn(Date(2000, 2, 1), Date(2000, 3, 1), 20);
        double expected = 0.6666666666666666296592325;
        double income =
            budget.ComputeIncome(Date(2000, 2, 1), Date(2000, 2, 1));
        AssertEqual(income, expected, "one day income");
    }
    {
        Budget budget;
        budget.Earn(Date(2000, 2, 1), Date(2000, 3, 1), 20);
        double expected = 1.333333333333333259318465;
        double income =
            budget.ComputeIncome(Date(2000, 2, 1), Date(2000, 2, 2));
        AssertEqual(income, expected, "two days income");
    }
    {
        Budget budget;
        budget.Earn(Date(2000, 2, 1), Date(2000, 3, 1), 20);
        double income =
            budget.ComputeIncome(Date(2000, 2, 1), Date(2000, 3, 1));
        AssertEqual(income, 20, "20 days income");
    }
    {
        Budget budget;
        budget.Earn(Date(2000, 2, 1), Date(2000, 3, 1), 20);
        double income =
            budget.ComputeIncome(Date(2000, 3, 1), Date(2000, 2, 1));
        AssertEqual(income, 0.0, "20 days income backwards");
    }
    {
        Budget budget;
        budget.Earn(Date(2000, 2, 1), Date(2000, 3, 1), 20);
        double income =
            budget.ComputeIncome(Date(2000, 1, 1), Date(2000, 3, 1));
        AssertEqual(income, 20, "from 2000-1-1");
    }
    {
        Budget budget;
        budget.Earn(Date(2000, 2, 1), Date(2000, 3, 1), 20);
        double income =
            budget.ComputeIncome(Date(2000, 2, 1), Date(2000, 4, 1));
        AssertEqual(income, 20, "to 2000-4-1");
    }
    {
        Budget budget;
        budget.Earn(Date(2000, 2, 1), Date(2000, 3, 1), 20);
        double income =
            budget.ComputeIncome(Date(2000, 1, 1), Date(2099, 12, 31));
        AssertEqual(income, 20, "from 2000-1-1 to 2099-12-31");
    }
    {
        Budget budget;
        budget.Earn(Date(2000, 2, 1), Date(2000, 3, 1), 20);
        budget.Earn(Date(2000, 2, 3), Date(2000, 2, 3), 10);
        double expected = 10.6666666666666666296592325;
        double income =
            budget.ComputeIncome(Date(2000, 2, 3), Date(2000, 2, 3));
        AssertEqual(income, expected, "one day two incomes");
    }
    {
        Budget budget;
        budget.Earn(Date(2000, 2, 1), Date(2000, 3, 1), 20);
        budget.Earn(Date(2000, 2, 3), Date(2000, 2, 3), 10);
        double expected = 30.00000000000002131628207;
        double income =
            budget.ComputeIncome(Date(2000, 1, 1), Date(2099, 12, 31));
        AssertEqual(income, expected, "from 2000-1-1 to 2099-12-31");
    }
    {
        Budget budget;
        budget.Earn(Date(2000, 2, 1), Date(2000, 3, 1), 20);
        budget.Earn(Date(2000, 2, 3), Date(2000, 2, 3), 10);
        double expected = 0.0;
        double income =
            budget.ComputeIncome(Date(2099, 1, 1), Date(2000, 12, 31));
        AssertEqual(income, expected, "from 2000-1-1 to 2099-12-31 backeards");
    }
}

int main()
{
    // TestRunner tr;
    // tr.RunTest(Test, "Test");
    // return 0;

    Budget budget;

    int n;

    cin >> n;

    while (n-- > 0)
    {
        string command_code;
        cin >> command_code;

        if (command_code == "Earn")
        {
            Date from, to;
            int amount;
            cin >> from >> to >> amount;

            budget.Earn(from, to, amount);
        }
        else if (command_code == "ComputeIncome")
        {
            Date from, to;
            cin >> from >> to;
            cout << setprecision(25) << budget.ComputeIncome(from, to) << endl;
        }
        else
        {
            cerr << "Unknown command " << command_code << endl;
        }
    }
}
