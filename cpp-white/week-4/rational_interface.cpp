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

int main()
{
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10)
        {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3)
        {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3)
        {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3)
        {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1)
        {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 ||
            defaultConstructed.Denominator() != 1)
        {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    cout << "OK" << endl;
    return 0;
}
