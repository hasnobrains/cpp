#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

int GreatestCommonDivisor(int a, int b)
{
    a = abs(a);
    b = abs(b);

    // пока оба числа положительны, будем их уменьшать, не меняя их НОД
    while (a > 0 && b > 0)
    {
        // возьмём большее из чисел и заменим его остатком от деления на
        // второе действительно, если a и b делятся на x, то a - b и b
        // делятся на x тогда и a % b и b делятся на x, так что можно a
        // заменить на a % b
        if (a > b)
        {
            a %= b;
        }
        else
        {
            b %= a;
        }
    }

    // если одно из чисел оказалось равно нулю, значит, на последней
    // итерации большее число разделилось на меньшее
    return a + b;
}

int LeastCommonMultiple(int a, int b)
{
    return abs(a) * abs(b) / GreatestCommonDivisor(a, b);
}

class Rational
{
  public:
    Rational()
    {
        p = 0;
        q = 1;
    }

    Rational(int numerator, int denominator)
    {
        if (numerator == 0)
        {
            p = 0;
            q = 1;
            return;
        }

        if (denominator < 0)
        {
            numerator *= -1;
            denominator *= -1;
        }

        int gcd = GreatestCommonDivisor(numerator, denominator);

        p = numerator / gcd;
        q = denominator / gcd;
    }

    int Numerator() const { return p; }

    int Denominator() const { return q; }

  private:
    int p;
    int q;
};

bool operator==(const Rational& lhs, const Rational& rhs)
{
    return lhs.Numerator() == rhs.Numerator() &&
           lhs.Denominator() == rhs.Denominator();
}

bool operator<(const Rational& lhs, const Rational& rhs)
{
    int lcm = LeastCommonMultiple(lhs.Denominator(), rhs.Denominator());
    return lhs.Numerator() * lcm / lhs.Denominator() <
           rhs.Numerator() * lcm / rhs.Denominator();
}

int main()
{
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3)
        {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs)
        {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}})
        {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2)
        {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
