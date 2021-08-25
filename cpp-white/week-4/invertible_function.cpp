#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class FunctionParts
{
  public:
    FunctionParts(char o, double v)
    {
        operation = o;
        value = v;
    }

    double Apply(double v) const
    {
        switch (operation)
        {
            case '+':
                v += value;
                break;
            case '-':
                v -= value;
                break;
            case '*':
                v *= value;
                break;
            case '/':
                v /= value;
                break;
            default:
                cout << "Operation '" << operation << "' is unsupported!"
                     << endl;
                break;
        }

        return v;
    }

    void Invert()
    {
        switch (operation)
        {
            case '+':
                operation = '-';
                break;
            case '-':
                operation = '+';
                break;
            case '*':
                operation = '/';
                break;
            case '/':
                operation = '*';
                break;
            default:
                cout << "Operation '" << operation << "' is unsupported!"
                     << endl;
                break;
        }
    }

  private:
    char operation;
    double value;
};

class Function
{
  public:
    void AddPart(char operation, double value)
    {
        parts.push_back({operation, value});
    }

    void Invert()
    {
        for (auto &p : parts)
        {
            p.Invert();
        }

        reverse(begin(parts), end(parts));
    }

    double Apply(double value) const
    {
        for (const auto &p : parts)
        {
            value = p.Apply(value);
        }

        return value;
    }

  private:
    vector<FunctionParts> parts;
};
