#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Person
{
  public:
    string GetName(map<int, string> name_history, int year)
    {
        string name = "";

        for (auto &item : name_history)
        {
            if (item.first > year)
                break;

            name = item.second;
        }

        return name;
    }

    void ChangeFirstName(int year, const string &first_name)
    {
        // добавить факт изменения имени на first_name в год year
        string name = GetName(fn_history, year);

        if (name != first_name)
        {
            fn_history[year] = first_name;
        }
    }

    void ChangeLastName(int year, const string &last_name)
    {
        // добавить факт изменения фамилии на last_name в год year
        string name = GetName(ln_history, year);

        if (name != last_name)
        {
            ln_history[year] = last_name;
        }
    }

    string CheckName(string first_name, string last_name)
    {
        if (first_name.size() == 0 && last_name.size() == 0)
        {
            return "Incognito";
        }

        if (first_name.size() != 0 && last_name.size() == 0)
        {
            return first_name + " with unknown last name";
        }

        if (first_name.size() == 0 && last_name.size() != 0)
        {
            return last_name + " with unknown first name";
        }

        return first_name + " " + last_name;
    }

    string GetFullName(int year)
    {
        // получить имя и фамилию по состоянию на конец года year

        string first_name = GetName(fn_history, year);
        string last_name = GetName(ln_history, year);

        return CheckName(first_name, last_name);
    }

    string GetNameWithHistory(map<int, string> history, int year)
    {
        vector<string> v;
        string name = "";
        string previous_names = "";

        for (auto &h : history)
        {
            if (h.first > year)
                break;

            v.push_back(h.second);
        }

        if (!v.empty())
        {
            int last = v.size() - 1;

            name += v[last];

            for (int i = last - 1; i >= 0; i--)
            {
                if (v[i] == name && previous_names.size() == 0)
                    continue;

                previous_names += (i == last - 1 ? "" : ", ") + v[i];
            }

            if (previous_names.size() > 0)
            {
                name += " (" + previous_names + ")";
            }
        }

        return name;
    }

    string GetFullNameWithHistory(int year)
    {
        // получить все имена и фамилии по состоянию на конец года year

        string first_name = GetNameWithHistory(fn_history, year);
        string last_name = GetNameWithHistory(ln_history, year);

        return CheckName(first_name, last_name);
    }

  private:
    // приватные поля
    map<int, string> fn_history;
    map<int, string> ln_history;
};

int test1()
{
    Person person;

    cout << "Test 1:" << endl;
    person.ChangeFirstName(1900, "Eugene");
    person.ChangeLastName(1900, "Sokolov");
    person.ChangeLastName(1910, "Sokolov");
    person.ChangeFirstName(1920, "Evgeny");
    person.ChangeLastName(1930, "Sokolov");
    cout << person.GetFullNameWithHistory(1940) << endl;
    cout << endl;

    return 0;
}

int test2()
{
    Person person;

    cout << "Test 2:" << endl;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1990, "Polina");
    person.ChangeLastName(1990, "Volkova-Sergeeva");
    cout << person.GetFullNameWithHistory(1990) << endl;

    person.ChangeFirstName(1966, "Pauline");
    cout << person.GetFullNameWithHistory(1966) << endl;

    person.ChangeLastName(1960, "Sergeeva");
    for (int year : {1960, 1967})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1961, "Ivanova");
    cout << person.GetFullNameWithHistory(1967) << endl;

    cout << endl;

    return 0;
}

int test3()
{
    Person person;

    cout << "Test 3:" << endl;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeFirstName(1965, "Appolinaria");

    person.ChangeLastName(1965, "Sergeeva");
    person.ChangeLastName(1965, "Volkova");
    person.ChangeLastName(1965, "Volkova-Sergeeva");

    for (int year : {1964, 1965, 1966})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    cout << endl;

    return 0;
}

int test4()
{
    Person person;

    cout << "Test 4:" << endl;

    int year = 1;
    person.ChangeFirstName(year, std::to_string(year) + "_first");
    person.ChangeLastName(year, std::to_string(year) + "_last");
    std::cout << "year: " << year << '\n';
    std::cout << person.GetFullNameWithHistory(year) << '\n';

    year = 2;
    person.ChangeFirstName(year, std::to_string(year) + "_first");
    person.ChangeLastName(year, std::to_string(year) + "_last");
    std::cout << "year: " << year << '\n';
    std::cout << person.GetFullNameWithHistory(year) << '\n';

    year = 3;
    person.ChangeFirstName(year, std::to_string(2) + "_first");
    person.ChangeLastName(year, std::to_string(2) + "_last");
    std::cout << "year: " << year << '\n';
    std::cout << person.GetFullNameWithHistory(year) << '\n';

    cout << endl;

    return 0;
}

int main()
{
    test1();
    test2();
    test3();
    test4();

    return 0;
}
