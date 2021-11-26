#include "token.h"

#include <stdexcept>

using namespace std;

vector<Token> Tokenize(istream& cl)
{
    vector<Token> tokens;

    char c;
    while (cl >> c)
    {
        if (isdigit(c))
        {
            string date(1, c);
            for (int i = 0; i < 3; ++i)
            {
                while (isdigit(cl.peek()))
                {
                    date += cl.get();
                }
                if (i < 2)
                {
                    date += cl.get(); // Consume '-'
                }
            }
            tokens.push_back({date, TokenType::DATE});
        }
        else if (c == '"')
        {
            string event;
            getline(cl, event, '"');
            tokens.push_back({event, TokenType::EVENT});
        }
        else if (c == 'd')
        {
            if (cl.get() == 'a' && cl.get() == 't' && cl.get() == 'e')
            {
                tokens.push_back({"date", TokenType::COLUMN});
            }
            else
            {
                throw logic_error("Unknown token");
            }
        }
        else if (c == 'e')
        {
            if (cl.get() == 'v' && cl.get() == 'e' && cl.get() == 'n' &&
                cl.get() == 't')
            {
                tokens.push_back({"event", TokenType::COLUMN});
            }
            else
            {
                throw logic_error("Unknown token");
            }
        }
        else if (c == 'A')
        {
            if (cl.get() == 'N' && cl.get() == 'D')
            {
                tokens.push_back({"AND", TokenType::LOGICAL_OP});
            }
            else
            {
                throw logic_error("Unknown token");
            }
        }
        else if (c == 'O')
        {
            if (cl.get() == 'R')
            {
                tokens.push_back({"OR", TokenType::LOGICAL_OP});
            }
            else
            {
                throw logic_error("Unknown token");
            }
        }
        else if (c == '(')
        {
            tokens.push_back({"(", TokenType::PAREN_LEFT});
        }
        else if (c == ')')
        {
            tokens.push_back({")", TokenType::PAREN_RIGHT});
        }
        else if (c == '<')
        {
            if (cl.peek() == '=')
            {
                cl.get();
                tokens.push_back({"<=", TokenType::COMPARE_OP});
            }
            else
            {
                tokens.push_back({"<", TokenType::COMPARE_OP});
            }
        }
        else if (c == '>')
        {
            if (cl.peek() == '=')
            {
                cl.get();
                tokens.push_back({">=", TokenType::COMPARE_OP});
            }
            else
            {
                tokens.push_back({">", TokenType::COMPARE_OP});
            }
        }
        else if (c == '=')
        {
            if (cl.get() == '=')
            {
                tokens.push_back({"==", TokenType::COMPARE_OP});
            }
            else
            {
                throw logic_error("Unknown token");
            }
        }
        else if (c == '!')
        {
            if (cl.get() == '=')
            {
                tokens.push_back({"!=", TokenType::COMPARE_OP});
            }
            else
            {
                throw logic_error("Unknown token");
            }
        }
    }

    return tokens;
}

ostream& operator<<(ostream& os, const Token& token)
{
    switch (token.type)
    {
        case TokenType::DATE:
            os << "DATE";
            break;
        case TokenType::EVENT:
            os << "EVENT";
            break;
        case TokenType::COLUMN:
            os << "COLUMN";
            break;
        case TokenType::LOGICAL_OP:
            os << "LOGICAL_OP";
            break;
        case TokenType::COMPARE_OP:
            os << "COMPARE_OP";
            break;
        case TokenType::PAREN_LEFT:
            os << "PAREN_LEFT";
            break;
        case TokenType::PAREN_RIGHT:
            os << "PAREN_RIGHT";
            break;
    }
    os << ":" << token.value;
    return os;
}
