#ifndef TableVar_H_INCLUDED
#define TableVar_H_INCLUDED

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
    int hashnum;
    // Указатель на массив цепочек
    vector<Lexeme> *table;
    // Подсчет хэша
    int get_hash(string name);
    // Подсчет номера в цепочке
    int get_chain(string name);
public:
    // Конструктор с размером таблицы по умолчанию
    TableVar();
    // Конструктор с пользовательским размером таблицы
    TableVar(int new_hashnum);
    // Деструктор
    ~TableVar();
    // Определение хэша и номера в цепочке
    bool get_location(string name, int &hash, int &chain);
    // Проверка есть ли элемент в таблице
    inline bool contains(string name);
    // Добавление нового имени идентификатора или значения константы
    bool add(string name);
    // Задание типа по хэшу и номеру в цепочке
    bool set_type(int hash, int chain, int type);
    // Задание типа по имени идентификатора или значению константы
    bool set_type(string name, int type);
    // Задание размерности по хэшу и номеру в цепочке
    bool set_dimension(int hash, int chain, int dimension);
    // Задание размерности по имени идентификатора или значению константы
    bool set_dimension(string name, int dimension);
    // Задание флага инициализации по хэшу и номеру в цепочке
    bool set_is_init(int hash, int chain, bool is_init);
    // Задание флага инициализации по имени идентификатора или значению константы
    bool set_is_init(string name, bool is_init);
    // Задание флага инициализации для массивов по хэшу и номеру в цепочке
    bool set_is_init(int hash, int chain, bool is_init, int init_index);
    // Задание флага инициализации для массивов по имени идентификатора или значению константы
    bool set_is_init(string name, bool is_init, int init_index);
    // Получение структуры Lexeme по хэшу и номеру в цепочке
    bool get_Lexeme(int hash, int chain, Lexeme &Lexeme);
    // Получение структуры Lexeme по имени идентификатора или значению константы
    bool get_Lexeme(string name, Lexeme &Lexeme);
    // Отладочная печать
    void debug_print(ostream& stream);
};

#endif // TableVar_H_INCLUDED
