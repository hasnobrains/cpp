#include "condition_parser.h"
#include "database.h"
#include "date.h"
#include "node.h"

#include <iostream>
#include <stdexcept>

using namespace std;

string ParseEvent(istream& is)
{
    string event;
    getline(is >> ws, event);
    return event;
}

void TestAll();

int main()
{
    TestAll();

    Database db;

    for (string line; getline(cin, line);)
    {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add")
        {
            // Add 2017-11-07 big sport event
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        }
        else if (command == "Print")
        {
            db.Print(cout);
        }
        else if (command == "Del")
        {
            // Del event != "holiday"
            // Del date < 2017-01-01 AND (event == "holiday" OR event == "sport
            // event")
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date,
                                         const string& event) {
                return condition->Evaluate(date, event);
            };
            int count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;
        }
        else if (command == "Find")
        {
            // Find date < 2017-11-06
            // Find date >= 2017-01-01 AND date < 2017-07-01 AND event == "sport
            // event"
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date,
                                         const string& event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto& entry : entries)
            {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        }
        else if (command == "Last")
        {
            // Last 2017-06-01
            try
            {
                cout << db.Last(ParseDate(is)) << endl;
            }
            catch (invalid_argument&)
            {
                cout << "No entries" << endl;
            }
        }
        else if (command.empty())
        {
            continue;
        }
        else
        {
            throw logic_error("Unknown command: " + command);
        }
    }

    return 0;
}

void TestParseEvent()
{
    {
        istringstream is("event");
        AssertEqual(ParseEvent(is), "event",
                    "Parse event without leading spaces");
    }
    {
        istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ",
                    "Parse event with leading spaces");
    }
    {
        istringstream is("  first event  \n  second event");
        vector<string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, vector<string>{"first event  ", "second event"},
                    "Parse multiple events");
    }
}

void TestDel()
{

    {
        Database db;
        {

            istringstream is("2017-06-01 1st of June\n");
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        }
        {

            istringstream is("2017-07-08 8th of July\n");
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        }
        {

            istringstream is("2017-07-08 Someone's birthday\n");
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        }
        {

            istringstream is("date == 2017-07-08\n");
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date,
                                         const string& event) {
                return condition->Evaluate(date, event);
            };
            AssertEqual(db.RemoveIf(predicate), 2, "Equal 2");
        }
    }
}

void TestPrint()
{
    {
        Database db;
        {
            istringstream is("2017-01-01 Holiday\n");
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        }
        {
            istringstream is("2017-03-08 Holiday\n");
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        }
        {
            istringstream is("2017-1-1 New Year\n");
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        }
        {
            istringstream is("2017-1-1 New Year\n");
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        }
        string result = "2017-01-01 Holiday\n"
                        "2017-01-01 New Year\n"
                        "2017-03-08 Holiday\n";
        ostringstream os;
        db.Print(os);
        AssertEqual(os.str(), result, "");
    }
}

void TestFind()
{
    {
        Database db;
        {
            istringstream is("2017-01-01 Holiday\n");
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        }
        {
            istringstream is("2017-03-08 Holiday\n");
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        }
        {
            istringstream is("2017-01-01 New Year\n");
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        }
        {
            istringstream is("event != \"working day\"\n");
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date,
                                         const string& event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            ostringstream os;
            for (const auto& entry : entries)
            {
                os << entry << endl;
            }
            string result = "2017-01-01 Holiday\n"
                            "2017-01-01 New Year\n"
                            "2017-03-08 Holiday\n";
            AssertEqual(os.str(), result, "Check string");
            AssertEqual(entries.size(), 3, "Check number");
        }
    }
}

void TestLast()
{
    {
        Database db;
        {
            istringstream is("2017-01-01 New Year\n");
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        }
        {
            istringstream is("2017-03-08 Holiday\n");
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        }
        {
            istringstream is("2017-01-01 Holiday\n");
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        }
        {
            ostringstream os;

            try
            {
                istringstream is("2016-12-31\n");
                os << db.Last(ParseDate(is));
            }
            catch (invalid_argument&)
            {
                os << "No entries";
            }

            string result = "No entries";
            // cout << "os " << os.str() << endl;
            AssertEqual(os.str(), result, "No entries");
        }
        {
            ostringstream os;

            try
            {
                istringstream is("2017-01-01\n");
                os << db.Last(ParseDate(is));
            }
            catch (invalid_argument&)
            {
                os << "No entries";
            }

            string result = "2017-01-01 Holiday";
            // cout << "os " << os.str() << endl;
            AssertEqual(os.str(), result, "2017-01-01 Holiday");
        }
        {
            ostringstream os;

            try
            {
                istringstream is("2017-06-01\n");
                os << db.Last(ParseDate(is));
            }
            catch (invalid_argument&)
            {
                os << "No entries";
            }

            string result = "2017-03-08 Holiday";
            // cout << "os " << os.str() << endl;
            AssertEqual(os.str(), result, "2017-03-08 Holiday");
        }
    }
}

void TestMix()
{
    Database db;
    {
        istringstream is("2017-11-21 Tuesday\n");
        const auto date = ParseDate(is);
        const auto event = ParseEvent(is);
        db.Add(date, event);
    }
    {
        istringstream is("2017-11-20 Monday\n");
        const auto date = ParseDate(is);
        const auto event = ParseEvent(is);
        db.Add(date, event);
    }
    {
        istringstream is("2017-11-21 Weekly meeting\n");
        const auto date = ParseDate(is);
        const auto event = ParseEvent(is);
        db.Add(date, event);
    }
    {
        string result = "2017-11-20 Monday\n"
                        "2017-11-21 Tuesday\n"
                        "2017-11-21 Weekly meeting\n";
        ostringstream os;
        db.Print(os);
        AssertEqual(os.str(), result, "");
    }
    {
        istringstream is("event != \"Weekly meeting\"\n");
        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date& date, const string& event) {
            return condition->Evaluate(date, event);
        };

        const auto entries = db.FindIf(predicate);
        ostringstream os;
        for (const auto& entry : entries)
        {
            os << entry << endl;
        }
        string result = "2017-11-20 Monday\n"
                        "2017-11-21 Tuesday\n";
        AssertEqual(os.str(), result, "Check string");
        AssertEqual(entries.size(), 2, "Check number");
    }
    {
        ostringstream os;

        try
        {
            istringstream is("2017-11-30\n");
            os << db.Last(ParseDate(is));
        }
        catch (invalid_argument&)
        {
            os << "No entries";
        }

        string result = "2017-11-21 Weekly meeting";
        // cout << "os " << os.str() << endl;
        AssertEqual(os.str(), result, "2017-11-21 Weekly meeting");
    }
    {

        istringstream is("date > 2017-11-20\n");
        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date& date, const string& event) {
            return condition->Evaluate(date, event);
        };
        AssertEqual(db.RemoveIf(predicate), 2, "Equal 2");
    }
    {
        ostringstream os;

        try
        {
            istringstream is("2017-11-30\n");
            os << db.Last(ParseDate(is));
        }
        catch (invalid_argument&)
        {
            os << "No entries";
        }

        string result = "2017-11-20 Monday";
        // cout << "os " << os.str() << endl;
        AssertEqual(os.str(), result, "2017-11-20 Monday");
    }
    {
        ostringstream os;

        try
        {
            istringstream is("2017-11-01\n");
            os << db.Last(ParseDate(is));
        }
        catch (invalid_argument&)
        {
            os << "No entries";
        }

        string result = "No entries";
        // cout << "os " << os.str() << endl;
        AssertEqual(os.str(), result, "No entries");
    }
}

void TestAll()
{
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseCondition, "TestParseCondition");
    tr.RunTest(TestDel, "TestDel");
    tr.RunTest(TestPrint, "TestPrint");
    tr.RunTest(TestFind, "TestFind");
    tr.RunTest(TestLast, "TestLast");
    tr.RunTest(TestMix, "TestMix");
}
