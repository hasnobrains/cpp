#include <exception>
#include <iostream>

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
        if (denominator == 0)
        {
            throw invalid_argument("");
        }

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

Rational operator+(const Rational& lhs, const Rational& rhs)
{
    int lcm = LeastCommonMultiple(lhs.Denominator(), rhs.Denominator());
    return Rational(lhs.Numerator() * lcm / lhs.Denominator() +
                        rhs.Numerator() * lcm / rhs.Denominator(),
                    lcm);
}

Rational operator-(const Rational& lhs, const Rational& rhs)
{
    int lcm = LeastCommonMultiple(lhs.Denominator(), rhs.Denominator());
    return Rational(lhs.Numerator() * lcm / lhs.Denominator() -
                        rhs.Numerator() * lcm / rhs.Denominator(),
                    lcm);
}

Rational operator*(const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs.Numerator() * rhs.Numerator(),
                    lhs.Denominator() * rhs.Denominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs)
{
    if (rhs.Numerator() == 0)
    {
        throw domain_error("");
    }

    int lcm = LeastCommonMultiple(lhs.Denominator(), rhs.Denominator());
    return Rational(lhs.Numerator() * rhs.Denominator(),
                    lhs.Denominator() * rhs.Numerator());
}

ostream& operator<<(ostream& os, const Rational& r)
{
    os << r.Numerator() << "/" << r.Denominator();
    return os;
}

istream& operator>>(istream& is, Rational& r)
{
    int n, d;
    char c;

    if (is)
    {
        is >> n >> c >> d;
        if (is)
        {
            if (c == '/')
            {
                r = Rational(n, d);
            }
            else
            {
                is.setstate(ios_base::failbit);
            }
        }
    }

    return is;
}

bool operator<(const Rational& lhs, const Rational& rhs)
{
    int lcm = LeastCommonMultiple(lhs.Denominator(), rhs.Denominator());
    return lhs.Numerator() * lcm / lhs.Denominator() <
           rhs.Numerator() * lcm / rhs.Denominator();
}

int main()
{
    try
    {
        char operation;
        Rational lhs, rhs;
        cin >> lhs >> operation >> rhs;

        switch (operation)
        {
            case '+':
                cout << lhs + rhs << endl;
                break;
            case '-':
                cout << lhs - rhs << endl;
                break;
            case '*':
                cout << lhs * rhs << endl;
                break;
            case '/':
                cout << lhs / rhs << endl;
                break;
        }
    }
    catch (invalid_argument&)
    {
        cout << "Invalid argument" << endl;
    }
    catch (domain_error&)
    {
        cout << "Division by zero" << endl;
    }

    return 0;
}
