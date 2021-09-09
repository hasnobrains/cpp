#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace std;

// Реализуйте здесь
// * класс Matrix
// * оператор ввода для класса Matrix из потока istream
// * оператор вывода класса Matrix в поток ostream
// * оператор проверки на равенство двух объектов класса Matrix
// * оператор сложения двух объектов класса Matrix

class Matrix
{
  public:
    Matrix()
    {
        num_rows = 0;
        num_cols = 0;
        m = vector<vector<int>>(num_rows, vector<int>(num_cols));
    }

    Matrix(int _num_rows, int _num_cols)
    {
        CheckRowAndColumnNums(_num_rows, _num_cols);
        num_rows = _num_rows;
        num_cols = _num_cols;
        m = vector<vector<int>>(num_rows, vector<int>(num_cols));
        // from course answers
        // m.assign(num_rows, vector<int>(num_cols));
    }

    void Reset(int _num_rows, int _num_cols)
    {
        CheckRowAndColumnNums(_num_rows, _num_cols);
        num_rows = _num_rows;
        num_cols = _num_cols;
        m = vector<vector<int>>(num_rows, vector<int>(num_cols));
    }

    int At(int row_id, int col_id) const
    {
        CheckRowAndColumnId(row_id, col_id);
        return m[row_id][col_id];
    }

    int& At(int row_id, int col_id)
    {
        CheckRowAndColumnId(row_id, col_id);
        return m[row_id][col_id];
    }

    int GetNumRows() const { return num_rows; }

    int GetNumColumns() const { return num_cols; }

  private:
    vector<vector<int>> m;
    int num_rows;
    int num_cols;

    void CheckRowAndColumnNums(int _num_rows, int _num_cols)
    {
        if (_num_rows < 0)
        {
            throw out_of_range("Number of rows less than 0: " +
                               to_string(_num_rows));
        }

        if (_num_cols < 0)
        {
            throw out_of_range("Number of columns less than 0: " +
                               to_string(_num_cols));
        }
    }

    void CheckRowAndColumnId(int row_id, int col_id) const
    {
        if (row_id < 0 || row_id >= num_rows)
        {
            throw out_of_range("");
        }

        if (col_id < 0 || col_id >= num_cols)
        {
            throw out_of_range("");
        }
    }
};


Matrix FillMatrix(const string& s)
{
    stringstream ss(s);

    int num_rows, num_cols;

    ss >> num_rows >> num_cols;

    cout << num_rows << " " << num_cols << endl;
    Matrix m(num_rows, num_cols);

    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            ss >> m.At(i, j);

            if (ss.fail())
                throw runtime_error("Wrong input: " + s);

            cout << m.At(i, j) << (j == num_cols - 1 ? "\n" : " ");
        }
    }

    return m;
}


istream& operator>>(istream& is, Matrix& m)
{
    if (is)
    {
        int num_rows, num_cols;

        is >> num_rows >> num_cols;

        m.Reset(num_rows, num_cols);

        for (int i = 0; i < num_rows; i++)
        {
            for (int j = 0; j < num_cols; j++)
            {
                is >> m.At(i, j);

                if (is.fail())
                    throw runtime_error("");
            }
        }
    }

    return is;
}


ostream& operator<<(ostream& os, const Matrix& m)
{
    int num_rows = m.GetNumRows();
    int num_cols = m.GetNumColumns();

    os << num_rows << " " << num_cols << endl;
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            os << m.At(i, j) << (j == num_cols - 1 ? "" : " ");
        }

        os << (i == num_rows - 1 || num_cols == 0 ? "" : "\n");
    }

    return os;
}


bool operator==(const Matrix& lhs, const Matrix& rhs)
{
    int num_rows = lhs.GetNumRows();
    int num_cols = lhs.GetNumColumns();

    if ((num_rows == 0 || num_cols == 0) &&
        (rhs.GetNumRows() == 0 || rhs.GetNumColumns() == 0))
    {
        return true;
    }

    if (num_rows != rhs.GetNumRows() || num_cols != rhs.GetNumColumns())
    {
        return false;
    }

    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            if (lhs.At(i, j) != rhs.At(i, j))
                return false;
        }
    }

    return true;
}


Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
    int num_rows = lhs.GetNumRows();
    int num_cols = lhs.GetNumColumns();

    if ((num_rows == 0 || num_cols == 0) &&
        (rhs.GetNumRows() == 0 || rhs.GetNumColumns() == 0))
    {
        return Matrix();
    }

    if (num_rows != rhs.GetNumRows() || num_cols != rhs.GetNumColumns())
    {
        throw invalid_argument("Diffenrent matrix sizes");
    }

    Matrix m(num_rows, num_cols);

    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            m.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
        }
    }

    return m;
}


int main()
{
    Matrix one;
    Matrix two;

    // istringstream input("3 5\n"
    //                     "6 4 -1 9 8\n"
    //                     "12 1 2 9 -5\n"
    //                     "-4 0 12 8 6\n"
    //                     "\n"
    //                     "3 5\n"
    //                     "5 1 0 -8 23\n"
    //                     "14 5 -6 6 9\n"
    //                     "8 0 5 4 1");


    // istringstream input("3 5\n"
    //                     "6 4 -1 9 8\n"
    //                     "12 1 2 9 -5\n"
    //                     "-4 0 12 8 6\n"
    //                     "\n"
    //                     "3\n"
    //                     "6 4 -1\n");
    //
    // input >> one >> two;
    // cout << (one == two) << endl;
    //
    // one.Reset(0, 0);
    // cout << one.At(2, 4) << endl;
    // Matrix a;
    // cout << a.GetNumColumns() << ' ' << a.GetNumRows();
    // Matrix a1(7, 0);
    // cout << a1.GetNumColumns() << ' ' << a1.GetNumRows();
    // {
    //     Matrix b(7, 0);
    //     cout << b;
    // }
    // cout << (Matrix(0, 7) + Matrix(5, 0));


    cin >> one >> two;
    cout << one + two << endl;

    return 0;
}
