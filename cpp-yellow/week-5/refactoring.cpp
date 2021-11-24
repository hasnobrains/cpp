#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human
{
  public:
    Human(const string& type, const string& name) : Type(type), Name(name) {}

    virtual void Walk(const string& destination)
    {
        Log() << " walks to: " << destination << endl;
    }

    ostream& Log() { return cout << Type << ": " << Name; }

    const string Type;
    const string Name;
};

class Student : public Human
{
  public:
    Student(const string& name, const string& favouriteSong)
        : Human("Student", name), FavouriteSong(favouriteSong)
    {
    }

    void Learn() { Log() << " learns" << endl; }

    void Walk(const string& destination) override
    {
        Human::Walk(destination);
        SingSong();
    }

    void SingSong() { Log() << " sings a song: " << FavouriteSong << endl; }

    const string FavouriteSong;
};


class Teacher : public Human
{
  public:
    Teacher(const string& name, const string& subject)
        : Human("Teacher", name), Subject(subject)
    {
    }

    void Teach() { Log() << " teaches: " << Subject << endl; }

    const string Subject;
};


class Policeman : public Human
{
  public:
    Policeman(const string& name) : Human("Policeman", name) {}

    void Check(const Human& h)
    {
        Log() << " checks " << h.Type << ". " << h.Type
              << "'s name is: " << h.Name << endl;
    }
};


void VisitPlaces(Human h, vector<string> places)
{
    for (auto p : places)
    {
        h.Walk(p);
    }
}

int main()
{
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
