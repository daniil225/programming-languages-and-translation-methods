#include "lexeme.h"

// Конструктор по умолчанию
Lexeme::Lexeme() {}

// Конструктор с заданием имени идентификатора или значения константы
Lexeme::Lexeme(string new_name)
{
    Name = new_name;
    Type = 0;
    IsInit.push_back(false);
    Dimension = 1;
}

// Деструктор
Lexeme::~Lexeme()
{
    IsInit.clear();
}
