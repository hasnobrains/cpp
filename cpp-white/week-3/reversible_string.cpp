#include <iostream>
#include <string>

using namespace std;

class ReversibleString
{
    public:
        ReversibleString () {}

        ReversibleString(const string& _s)
        {
            s = _s;
        }

        void Reverse()
        {
            int len = s.size();

            for (int i = 0; i < len / 2; i++)
            {
                char c = s[i];
                s[i] = s[len - 1 - i];
                s[len - 1 - i] = c;
            }
        }

        string ToString() const
        {
            return s;
        }

    private:

        string s;
};


int main() {
  ReversibleString s("live");
  s.Reverse();
  cout << s.ToString() << endl;

  s.Reverse();
  const ReversibleString& s_ref = s;
  string tmp = s_ref.ToString();
  cout << tmp << endl;

  ReversibleString empty;
  cout << '"' << empty.ToString() << '"' << endl;

  return 0;
}

