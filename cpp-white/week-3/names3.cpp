#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Person
{
  public:
    Person(string first_name, string last_name, int year)
    {
        fn_history[year] = first_name;
        ln_history[year] = last_name;
        born = year;
    }

    string GetName(map<int, string> name_history, int year) const
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

        if (year < born)
            return;

        string name = GetName(fn_history, year);

        if (name != first_name)
        {
            fn_history[year] = first_name;
        }
    }

    void ChangeLastName(int year, const string &last_name)
    {
        // добавить факт изменения фамилии на last_name в год year

        if (year < born)
            return;

        string name = GetName(ln_history, year);

        if (name != last_name)
        {
            ln_history[year] = last_name;
        }
    }

    string CheckName(string first_name, string last_name) const
    {
        if (first_name.size() == 0 && last_name.size() == 0)
        {
            return "No person";
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

    string GetFullName(int year) const
    {
        // получить имя и фамилию по состоянию на конец года year

        if (year < born)
        {
            return "No person";
        }

        string first_name = GetName(fn_history, year);
        string last_name = GetName(ln_history, year);

        return CheckName(first_name, last_name);
    }

    string GetNameWithHistory(map<int, string> history, int year) const
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

    string GetFullNameWithHistory(int year) const
    {
        // получить все имена и фамилии по состоянию на конец года year

        if (year < born)
        {
            return "No person";
        }

        string first_name = GetNameWithHistory(fn_history, year);
        string last_name = GetNameWithHistory(ln_history, year);

        return CheckName(first_name, last_name);
    }

  private:
    // приватные поля
    map<int, string> fn_history;
    map<int, string> ln_history;
    int born;
};

int main()
{
    Person person("Polina", "Sergeeva", 1960);

    for (int year : {1959, 1960})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }
    person.ChangeFirstName(1960, "Polina");
    person.ChangeLastName(1960, "Sergeeva");

    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");

    for (int year : {1965, 1967})
    {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    return 0;
}
