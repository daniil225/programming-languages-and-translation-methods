#ifndef TABLE_CONST_H_INCLUDED
#define TABLE_CONST_H_INCLUDED

#include <fstream>
#include <string>
#include <set>

using namespace std;

// Класс постоянных таблиц
template <typename type> class TableConst
{
private:
    set<type> table;
public:
    // Конструктор по умолчанию
    TableConst() {}
    // Деструктор
    ~TableConst()
    {
        table.clear();
    }
    // Добавление элемента в таблицу
    inline void Add(type elem)
    {
        table.insert(elem);
    }
    // Чтение таблицы из файла
    bool ReadFile(string name)
    {
        ifstream fs(name.c_str(), ios::in);
        if(!fs.is_open()) return false;
        type elem;
        while (!fs.eof())
        {
            fs >> elem;
            Add(elem);
        }
        return true;
    }
    // Проверка есть ли элемент в таблице
    bool Contains(type elem)
    {
        typename set<type>::iterator it = table.find(elem);
        if(it == table.end()) return false;
        return true;
    }
    // Поиск номера по значению
    bool get_num(type elem, int &num)
    {
        if(!Contains(elem)) return false;
        num = static_cast<int>(distance(table.begin(), table.find(elem)));
        return true;
    }
    // Поиск значения по номеру
    bool get_val(int num, type &elem)
    {
        if(num < 0 || num >= static_cast<int>(table.size())) return false;
        typename set<type>::iterator it = table.begin();
        for(int i = 0; i < num; i++)
            it++;
        elem = *it;
        return true;
    }
};

#endif // TABLE_CONST_H_INCLUDED
