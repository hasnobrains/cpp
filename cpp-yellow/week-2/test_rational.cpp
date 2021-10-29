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

#ifdef MYENV
class Rational
{
  public:
    // Вы можете вставлять сюда различные реализации,
    // чтобы проверить, что ваши тесты пропускают корректный код
    // и ловят некорректный

    Rational()
    {
        numerator = 0;
        denominator = 1;
    }

    Rational(int numerator, int denominator)
    {
        this->numerator = numerator;
        this->denominator = denominator;
    }

    int Numerator() const { return numerator; }

    int Denominator() const { return denominator; }

  private:
    int numerator;
    int denominator;
};
#endif

void Test()
{
    {
        Rational rational;
        AssertEqual(rational.Numerator(), 0, "Check numerator 0");
        AssertEqual(rational.Denominator(), 1, "Check denominator 1");
    }
    {
        Rational rational(1, 2);
        AssertEqual(rational.Numerator(), 1, "Check numerator 1");
        AssertEqual(rational.Denominator(), 2, "Check denominator 2");
    }
    {
        Rational rational(2, 4);
        AssertEqual(rational.Numerator(), 1, "Check numerator not 2");
        AssertEqual(rational.Denominator(), 2, "Check denominator not 4");
    }
    {
        Rational rational(6, 9);
        AssertEqual(rational.Numerator(), 2, "Check numerator not 6");
        AssertEqual(rational.Denominator(), 3, "Check denominator not 9");
    }
    {
        Rational rational(1, -2);
        AssertEqual(rational.Numerator(), -1, "Check numerator -1");
        AssertEqual(rational.Denominator(), 2, "Check denominator not -2");
    }
    {
        Rational rational(-1, 2);
        AssertEqual(rational.Numerator(), -1, "Check numerator -1");
        AssertEqual(rational.Denominator(), 2, "Check denominator 2");
    }
    {
        Rational rational(-1, -2);
        AssertEqual(rational.Numerator(), 1, "Check numerator not -1");
        AssertEqual(rational.Denominator(), 2, "Check denominator not -2");
    }
    {
        Rational rational(0, 2);
        AssertEqual(rational.Numerator(), 0, "Check numerator 0");
        AssertEqual(rational.Denominator(), 1, "Check denominator not 2");
    }
    {
        Rational rational(0, -1);
        AssertEqual(rational.Numerator(), 0, "Check numerator 0");
        AssertEqual(rational.Denominator(), 1, "Check denominator not -1");
    }
    {
        Rational rational(4, 2);
        AssertEqual(rational.Numerator(), 2, "Check numerator 2");
        AssertEqual(rational.Denominator(), 1, "Check denominator 1");
    }
    {
        Rational rational(3, 3);
        AssertEqual(rational.Numerator(), 1, "Check numerator 1");
        AssertEqual(rational.Denominator(), 1, "Check denominator 1");
    }
}

int main()
{
    TestRunner runner;
    runner.RunTest(Test, "Test");

    return 0;
}
