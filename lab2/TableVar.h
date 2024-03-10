#ifndef TABLE_VAR_H_
#define TABLE_VAR_H_

#include <fstream>
#include <string>
#include <vector>
#include "Lexeme.h"

using namespace std;

// Класс переменных таблиц
class TableVar
{
private:
    // Размер таблицы
    int HashNum;

    // Указатель на массив цепочек
    vector<Lexeme> *Table;
    
    // Подсчет хэша
    int GetHash(string Name);
    
    // Подсчет номера в цепочке
    int GetChain(string Name);
public:
    // Конструктор с размером таблицы по умолчанию
    TableVar();
    
    // Конструктор с пользовательским размером таблицы
    TableVar(int _hashnum);

    // Определение хэша и номера в цепочке
    bool GetLocation(string Name, int &hash, int &Chain);
    
    // Проверка есть ли элемент в таблице
    inline bool Contains(string Name);
    
    // Добавление нового имени идентификатора или значения константы
    bool Add(string Name);
    
    // Задание типа по хэшу и номеру в цепочке
    bool SetType(int hash, int Chain, int Type);
    
    // Задание типа по имени идентификатора или значению константы
    bool SetType(string Name, int Type);
    
    // Задание размерности по хэшу и номеру в цепочке
    bool SetDimension(int hash, int Chain, int Dimension);
    
    // Задание размерности по имени идентификатора или значению константы
    bool SetDimension(string Name, int Dimension);
    
    // Задание флага инициализации по хэшу и номеру в цепочке
    bool SetIsInit(int hash, int Chain, bool IsInit);
    
    // Задание флага инициализации по имени идентификатора или значению константы
    bool SetIsInit(string Name, bool IsInit);
    
    // Задание флага инициализации для массивов по хэшу и номеру в цепочке
    bool SetIsInit(int hash, int Chain, bool IsInit, int init_index);
    
    // Задание флага инициализации для массивов по имени идентификатора или значению константы
    bool SetIsInit(string Name, bool IsInit, int init_index);
    
    // Получение структуры lexeme по хэшу и номеру в цепочке
    bool GetLexeme(int hash, int Chain, Lexeme &lexeme);
    
    // Получение структуры lexeme по имени идентификатора или значению константы
    bool GetLexeme(string Name, Lexeme &lexeme);
    
    // Отладочная печать
    void DebugPrint(ostream& stream);

    // Деструктор
    ~TableVar();
};

#endif
