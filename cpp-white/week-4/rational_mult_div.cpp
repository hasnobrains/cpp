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

Rational operator*(const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs.Numerator() * rhs.Numerator(),
                    lhs.Denominator() * rhs.Denominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs)
{
    int lcm = LeastCommonMultiple(lhs.Denominator(), rhs.Denominator());
    return Rational(lhs.Numerator() * rhs.Denominator(),
                    lhs.Denominator() * rhs.Numerator());
}

int main()
{
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal)
        {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal)
        {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}
