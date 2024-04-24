#include "Lexeme.h"

// Конструктор по умолчанию
Lexeme::Lexeme() {}

// Конструктор с заданием имени идентификатора или значения константы
Lexeme::Lexeme(string new_name)
{
    name = new_name;
    type = 0;
    is_init.push_back(false);
    dimension = 1;
}

// Деструктор
Lexeme::~Lexeme()
{
    is_init.clear();
}
