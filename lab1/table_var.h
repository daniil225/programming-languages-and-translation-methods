#ifndef TABLE_VAR_H_INCLUDED
#define TABLE_VAR_H_INCLUDED

#include <fstream>
#include <string>
#include <vector>
#include "lexeme.h"

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
    int GetHash(string name);
    // Подсчет номера в цепочке
    int GetChain(string name);
public:
    // Конструктор с размером таблицы по умолчанию
    TableVar();
    // Конструктор с пользовательским размером таблицы
    TableVar(int new_hashnum);
    // Деструктор
    ~TableVar();
    // Определение хэша и номера в цепочке
    bool GetLocation(string name, int &hash, int &chain);
    // Проверка есть ли элемент в таблице
    inline bool Contains(string name);
    // Добавление нового имени идентификатора или значения константы
    bool Add(string name);
    // Задание типа по хэшу и номеру в цепочке
    bool SetType(int hash, int chain, int type);
    // Задание типа по имени идентификатора или значению константы
    bool set_type(string name, int type);
    // Задание размерности по хэшу и номеру в цепочке
    bool SetDimension(int hash, int chain, int dimension);
    // Задание размерности по имени идентификатора или значению константы
    bool set_dimension(string name, int dimension);
    // Задание флага инициализации по хэшу и номеру в цепочке
    bool SetIsInit(int hash, int chain, bool is_init);
    // Задание флага инициализации по имени идентификатора или значению константы
    bool set_is_init(string name, bool is_init);
    // Задание флага инициализации для массивов по хэшу и номеру в цепочке
    bool set_is_init(int hash, int chain, bool is_init, int init_index);
    // Задание флага инициализации для массивов по имени идентификатора или значению константы
    bool set_is_init(string name, bool is_init, int init_index);
    // Получение структуры lexeme по хэшу и номеру в цепочке
    bool GetLexeme(int hash, int chain, Lexeme &lexeme);
    // Получение структуры lexeme по имени идентификатора или значению константы
    bool get_lexeme(string name, Lexeme &lexeme);
};

#endif // TABLE_VAR_H_INCLUDED
