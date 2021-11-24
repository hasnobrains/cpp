#include <iomanip>
#include <iostream>
#include <math.h>
#include <memory>
#include <sstream>
#include <vector>

using namespace std;

double pi = 3.14;

class Figure
{
  public:
    virtual string Name() = 0;
    virtual double Perimeter() = 0;
    virtual double Area() = 0;
};

class Triangle : public Figure
{
  public:
    Triangle(int64_t a, int64_t b, int64_t c) : a(a), b(b), c(c) {}
    string Name() override { return "TRIANGLE"; }
    double Perimeter() override { return a + b + c; }
    double Area() override
    {
        double s = static_cast<double>(a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

  private:
    const int64_t a, b, c;
};

class Rect : public Figure
{
  public:
    Rect(int64_t w, int64_t h) : width(w), height(h) {}
    string Name() override { return "RECT"; }
    double Perimeter() override { return 2 * (width + height); }
    double Area() override { return width * height; }

  private:
    const int64_t width, height;
};

class Circle : public Figure
{
  public:
    Circle(int64_t r) : radius(r) {}
    string Name() override { return "CIRCLE"; }
    double Perimeter() override { return 2 * pi * radius; }
    double Area() override { return pi * radius * radius; }

  private:
    const int64_t radius;
};

shared_ptr<Figure> CreateFigure(istringstream& is)
{
    string type;
    is >> type;
    if (type == "TRIANGLE")
    {
        int64_t a, b, c;
        is >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    }
    else if (type == "RECT")
    {
        int64_t w, h;
        is >> w >> h;
        return make_shared<Rect>(w, h);
    }
    else if (type == "CIRCLE")
    {
        int64_t r;
        is >> r;
        return make_shared<Circle>(r);
    }
    return NULL;
}

int main()
{
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line);)
    {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD")
        {
            // Пропускаем "лишние" ведущие пробелы.
            // Подробнее об std::ws можно узнать здесь:
            // https://en.cppreference.com/w/cpp/io/manip/ws
            is >> ws;
            figures.push_back(CreateFigure(is));
        }
        else if (command == "PRINT")
        {
            for (const auto& current_figure : figures)
            {
                cout << fixed << setprecision(3) << current_figure->Name()
                     << " " << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}
