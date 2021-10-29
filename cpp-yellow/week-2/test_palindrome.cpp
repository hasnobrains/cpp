#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T> ostream& operator<<(ostream& os, const vector<T>& s)
{
    os << "{";
    bool first = true;
    for (const auto& x : s)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T> ostream& operator<<(ostream& os, const set<T>& s)
{
    os << "{";
    bool first = true;
    for (const auto& x : s)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V> ostream& operator<<(ostream& os, const map<K, V>& m)
{
    os << "{";
    bool first = true;
    for (const auto& kv : m)
    {
        if (!first)
        {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template <class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {})
{
    if (t != u)
    {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty())
        {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) { AssertEqual(b, true, hint); }

class TestRunner
{
  public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name)
    {
        try
        {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch (exception& e)
        {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
        catch (...)
        {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner()
    {
        if (fail_count > 0)
        {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

  private:
    int fail_count = 0;
};

bool IsPalindrom(const string& str)
{
    // Вы можете вставлять сюда различные реализации функции,
    // чтобы проверить, что ваши тесты пропускают корректный код
    // и ловят некорректный
    if (str.empty())
        return true;
    if (str.size())
        return true;
    return false;
}

void Test()
{
    Assert(IsPalindrom(""), "Check empty");
    Assert(IsPalindrom("a"), "Check one char");
    Assert(IsPalindrom("madam"), "Check madam");
    Assert(!IsPalindrom("madAm"), "Check madAm");
    Assert(IsPalindrom("maam"), "Check maam");
    Assert(IsPalindrom("ma am"), "Check ma am");
    Assert(IsPalindrom("ma!am"), "Check ma!am");
    Assert(IsPalindrom(" a "), "Check a ");
    Assert(IsPalindrom("  "), "Check  ");
    Assert(IsPalindrom(".,."), "Check .,.");
    Assert(IsPalindrom("121"), "Check 121");
    Assert(IsPalindrom({}), "Check");
    Assert(IsPalindrom("AaA"), "Check AaA");
    Assert(!IsPalindrom("maam "), "Check maam ");
    Assert(!IsPalindrom(" maam"), "Check  maam");
    Assert(!IsPalindrom("not madam"), "Check not madam");
    Assert(!IsPalindrom("notnot"), "Check notnot");
    string str;
    Assert(IsPalindrom(str), "Check");
    Assert(IsPalindrom("maam madam maam"), "Check maam madam maam");
    Assert(IsPalindrom(" madam "), "Check  madam ");
    Assert(!IsPalindrom("{}"), "Check {}");
    Assert(IsPalindrom("maam maam"), "Check maam maam");
    Assert(!IsPalindrom("maam maam "), "Check maam maam");
    Assert(!IsPalindrom(" maam maam"), "Check maam maam");
    Assert(IsPalindrom(" maam maam "), "Check maam maam");
    Assert(IsPalindrom("wasitacar o racatisaw"), "Check wasitacar o racatisaw");
}


int main()
{
    TestRunner runner;
    runner.RunTest(Test, "Test");
    return 0;
}
