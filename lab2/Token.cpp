#include "Token.h"

Token::Token() { }

Token::Token(int table_, int place_, int chain_)
{
    Table = table_;
    Place = place_;
    Chain = chain_;
}

istream& operator >> (istream& istream_, Token& token_)
{
    istream_ >> token_.Table >> token_.Place >> token_.Chain;
    return istream_;
}

ostream& operator << (ostream& ostream_, const Token& token_)
{
    ostream_ << token_.Table << " " << token_.Place << " " << token_.Chain << endl;
    return ostream_;
}

