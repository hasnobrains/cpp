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

int main()
{
    try
    {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    }
    catch (invalid_argument&)
    {
    }

    try
    {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    }
    catch (domain_error&)
    {
    }

    cout << "OK" << endl;
    return 0;
}
