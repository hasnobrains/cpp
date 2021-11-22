#include "test_runner.h"
#include <deque>
#include <iostream>
#include <sstream>

using namespace std;

deque<string> BuildExpression(istream& is)
{
    deque<string> expression;
    int x, n;
    is >> x >> n;

    expression.push_back(to_string(x));

    while (n-- > 0)
    {
        expression.push_front("(");
        expression.push_back(")");

        string operation, operand;
        is >> operation >> operand;

        expression.push_back(" " + operation + " " + operand);
    }

    return expression;
}

void Test()
{
    {
        istringstream ss("8\n"
                         "3\n"
                         "* 3\n"
                         "- 6\n"
                         "/ 1\n");

        for (auto& item : BuildExpression(ss))
        {
            cout << item;
        }
        cout << endl;
    }
    {
        istringstream ss("8\n"
                         "3\n"
                         "* 3\n"
                         "- -6\n"
                         "/ 1\n");

        for (auto& item : BuildExpression(ss))
        {
            cout << item;
        }
        cout << endl;
    }
    {
        istringstream ss("8\n"
                         "0\n");

        for (auto& item : BuildExpression(ss))
        {
            cout << item;
        }
        cout << endl;
    }
}

int main()
{
    // TestRunner tr;
    // tr.RunTest(Test, "Test");
    // return 0;

    for (auto& item : BuildExpression(cin))
    {
        cout << item;
    }
    cout << endl;

    return 0;
}
