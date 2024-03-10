#ifndef TOKEN_H_
#define TOKEN_H_
#include <iostream>
#include <fstream>

using namespace std;

// Класс токенов
class Token
{
public:
    int Table; // Номер таблицы
    int Place; // Положение в таблице
    int Chain; // Положение в цепочке
    // Конструкторы
    Token();
    Token(int table_, int place_, int chain_);
    // Ввод-вывод токенов
    friend istream& operator >> (istream& istream_, Token& token_);
    friend ostream& operator << (ostream& ostream_, const Token& token_);
};

#endif // TOKEN_H_INCLUDED
