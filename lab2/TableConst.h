#ifndef TABLE_CONST_H_
#define TABLE_CONST_H_

#include <fstream>
#include <string>
#include <set>

using namespace std;

// Класс постоянных таблиц
template <typename Type> class TableConst
{
private:
    set<Type> Table;
public:
    // Конструктор по умолчанию
    TableConst() {}

    
    // Добавление элемента в таблицу
    inline void Add(Type elem)
    {
        Table.insert(elem);
    }

    // Чтение таблицы из файла
    bool ReadFile(string Name)
    {
        ifstream fs(Name.c_str(), ios::in);
        if(!fs.is_open()) return false;
        Type elem;
        while (!fs.eof())
        {
            fs >> elem;
            Add(elem);
        }
        return true;
    }
    // Проверка есть ли элемент в таблице
    bool Contains(Type elem)
    {
        typename set<Type>::iterator it = Table.find(elem);
        if(it == Table.end()) return false;
        return true;
    }
    // Поиск номера по значению
    bool GetNum(Type elem, int &num)
    {
        if(!Contains(elem)) return false;
        num = static_cast<int>(distance(Table.begin(), Table.find(elem)));
        return true;
    }
    
    // Поиск значения по номеру
    bool GetVal(int num, Type &elem)
    {
        if(num < 0 || num >= Table.size()) return false;
        typename set<Type>::iterator it = Table.begin();
        for(int i = 0; i < num; i++)
            it++;
        elem = *it;
        return true;
    }
        
    // Деструктор
    ~TableConst()
    {
        Table.clear();
    }
};

#endif
