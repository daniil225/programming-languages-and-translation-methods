#ifndef Token_H_INCLUDED
#define Token_H_INCLUDED
#include <iostream>
#include <fstream>

using namespace std;

// Класс токенов
class Token
{
public:
    int table; // Номер таблицы
    int place; // Положение в таблице
    int chain; // Положение в цепочке
    // Конструкторы
    Token() {};
    Token(int table_, int place_, int chain_)
    {
        table = table_;
        place = place_;
        chain = chain_;
    }
    // Ввод-вывод токенов
    friend istream& operator >> (istream& istream_, Token& Token_)
    {
        istream_ >> Token_.table >> Token_.place >> Token_.chain;
        return istream_;
    }
    friend ostream& operator << (ostream& ostream_, const Token& Token_)
    {
        ostream_ << Token_.table << " " << Token_.place << " " << Token_.chain << endl;
        return ostream_;
    }
};

#endif // Token_H_INCLUDED
