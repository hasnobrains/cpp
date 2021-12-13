#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

#define UPDATE_FIELD(ticket, field, values)                                    \
    {                                                                          \
        map<string, string>::const_iterator it;                                \
        it = values.find(#field);                                              \
        if (it != values.end())                                                \
        {                                                                      \
            istringstream is(it->second);                                      \
            is >> ticket.field;                                                \
        }                                                                      \
    }

bool operator<(const Date& lhs, const Date& rhs)
{
    return tie(lhs.year, lhs.month, lhs.day) <
           tie(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Date& lhs, const Date& rhs)
{
    return tie(lhs.year, lhs.month, lhs.day) ==
           tie(rhs.year, rhs.month, rhs.day);
}

bool operator<(const Time& lhs, const Time& rhs)
{
    return tie(lhs.hours, lhs.minutes) < tie(rhs.hours, rhs.minutes);
}

bool operator==(const Time& lhs, const Time& rhs)
{
    return tie(lhs.hours, lhs.minutes) == tie(rhs.hours, rhs.minutes);
}

ostream& operator<<(ostream& os, const Date& d)
{
    return os << d.year << '-' << d.month << '-' << d.day;
}

ostream& operator<<(ostream& os, const Time& t)
{
    return os << t.hours << ':' << t.minutes;
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

    return {year, month, day};
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

Time ParseTime(const string& s)
{
    stringstream ss(s);

    int hours, minutes;
    char c;

    ss >> hours >> c >> minutes;

    if (ss.fail() || ss.peek() != EOF || c != ':')
    {
        cerr << "Wrong time format: " << s << endl;
        throw runtime_error("Wrong time format: " + s);
    }

    return {hours, minutes};
}

istream& operator>>(istream& is, Time& time)
{
    string s;

    if (is)
    {
        is >> s;
        time = ParseTime(s);
    }

    return is;
}


void TestUpdate()
{
    AirlineTicket t;
    t.price = 0;

    const map<string, string> updates1 = {
        {"departure_date", "2018-2-28"},
        {"departure_time", "17:40"},
    };

    UPDATE_FIELD(t, departure_date, updates1);
    UPDATE_FIELD(t, departure_time, updates1);
    UPDATE_FIELD(t, price, updates1);

    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 0);

    const map<string, string> updates2 = {
        {"price", "12550"},
        {"arrival_time", "20:33"},
    };

    UPDATE_FIELD(t, departure_date, updates2);
    UPDATE_FIELD(t, departure_time, updates2);
    UPDATE_FIELD(t, arrival_time, updates2);
    UPDATE_FIELD(t, price, updates2);

    // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
    // значения этих полей не должны измениться
    ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
    ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
    ASSERT_EQUAL(t.price, 12550);
    ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestUpdate);
}
