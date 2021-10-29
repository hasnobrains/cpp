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

int GetDistinctRealRootCount(double a, double b, double c)
{
    double d = b * b - 4 * a * c;

    if (a == 0)
    {
        if (b == 0)
        {
            return 0;
        }

        return 1;
    }


    if (d == 0)
    {
        return 1;
    }
    else if (d > 0)
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

void Test1() { AssertEqual(GetDistinctRealRootCount(3, 7, -6), 2); }
void Test2() { AssertEqual(GetDistinctRealRootCount(-1, 7, 8), 2); }
void Test3() { AssertEqual(GetDistinctRealRootCount(4, 4, 1), 1); }
void Test4() { AssertEqual(GetDistinctRealRootCount(2, 1, 1), 0); }
void Test5() { AssertEqual(GetDistinctRealRootCount(0, 1, 1), 1); }
void Test6() { AssertEqual(GetDistinctRealRootCount(1, 0, 0), 1); }
void Test7() { AssertEqual(GetDistinctRealRootCount(1, 0, 1), 0); }
void Test8() { AssertEqual(GetDistinctRealRootCount(-1, 0, 1), 2); }
void Test9() { AssertEqual(GetDistinctRealRootCount(-1, 1, 0), 2); }
void Test10() { AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0); }
void Test11() { AssertEqual(GetDistinctRealRootCount(0, 1, 0), 1); }

int main()
{
    TestRunner runner;
    // добавьте сюда свои тесты
    runner.RunTest(Test1, "test1");
    runner.RunTest(Test2, "test2");
    runner.RunTest(Test3, "test3");
    runner.RunTest(Test4, "test4");
    runner.RunTest(Test5, "test5");
    runner.RunTest(Test6, "test6");
    runner.RunTest(Test7, "test7");
    runner.RunTest(Test8, "test8");
    runner.RunTest(Test9, "test9");
    runner.RunTest(Test10, "test10");
    runner.RunTest(Test11, "test11");

    return 0;
}
