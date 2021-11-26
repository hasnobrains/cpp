#pragma once

#include <sstream>
#include <vector>

using namespace std;

enum class TokenType
{
    DATE,
    EVENT,
    COLUMN,
    LOGICAL_OP,
    COMPARE_OP,
    PAREN_LEFT,
    PAREN_RIGHT,
};

struct Token
{
    const string value;
    const TokenType type;
};

ostream& operator<<(ostream& os, const Token& token);
vector<Token> Tokenize(istream& cl);
