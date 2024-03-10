#ifndef LEXEME_H_
#define LEXEME_H_

#include <string>
#include <vector>

using namespace std;

// Класс для хранения идентификаторов и констант
class Lexeme
{
public:
    // Имя идентификатора или значение константы
    string Name;
    
    // Тип, 0 - не определен, 1 - int
    int Type;
    
    // Массив флагов "илициализировано ли" размерности Dimension
    vector<bool> IsInit;
    
    // Размерность массива, для переменных и констант - 1.
    int Dimension;
    
    // Конструктор по умолчанию
    Lexeme();
    
    // Конструктор с заданием имени идентификатора или значения константы
    Lexeme(string new_name);
    
    // Оператор присваивания
    Lexeme &operator = (const Lexeme &other)
    {
        if(this != &other)
        {
            Name = other.Name;
            Type = other.Type;
            Dimension = other.Dimension;
            IsInit = other.IsInit;
        }
        return *this;
    }

    // Деструктор
    ~Lexeme();
    
};

#endif
