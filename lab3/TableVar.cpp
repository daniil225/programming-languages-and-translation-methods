#include "TableVar.h"
// Размер хэш-таблицы по умолчанию
#define default_hashnum 100

// Подсчет хэша
int TableVar::get_hash(string name)
{
    int hash = 0;
    for(int i = 0; i < (int)name.size(); i++)
        hash += name[i];
    return hash % hashnum;
}

// Подсчет номера в цепочке
int TableVar::get_chain(string name)
{
    for(int i = 0, h = get_hash(name); i < (int)table[h].size(); i++)
        if(name == table[h][i].name) return i;
    return -1;
}

// Конструктор с размером таблицы по умолчанию
TableVar::TableVar()
{
    hashnum=default_hashnum;
    table = new vector<Lexeme> [hashnum];
}

// Конструктор с пользовательским размером таблицы
TableVar::TableVar(int new_hashnum)
{
    hashnum=new_hashnum;
    table = new vector<Lexeme> [hashnum];
}

// Деструктор
TableVar::~TableVar()
{
    for(int i = 0; i < hashnum; i++)
        table[i].clear();
    delete [] table;
}

// Проверка есть ли элемент в таблице
inline bool TableVar::contains(string name)
{
    if(get_chain(name) != -1) return true;
    return false;
}

// Добавление нового имени идентификатора или значения константы
bool TableVar::add(string name)
{
    if(contains(name)) return false;
    int h = get_hash(name);
    table[h].push_back(Lexeme(name));
    return true;
}

// Задание типа по хэшу и номеру в цепочке
bool TableVar::set_type(int hash, int chain, int type)
{
    if(chain == -1) return false;
    table[hash][chain].type = type;
    return true;
}

// Задание типа по имени идентификатора или значению константы
bool TableVar::set_type(string name, int type)
{
    int hash = get_hash(name), chain = get_chain(name);
    return set_type(hash, chain, type);
}

// Задание размерности по хэшу и номеру в цепочке
bool TableVar::set_dimension(int hash, int chain, int dimension)
{
    if(chain == -1) return false;
    table[hash][chain].dimension = dimension;
    table[hash][chain].is_init.resize(dimension);
    for(int i = 0; i < dimension; i++)
        table[hash][chain].is_init[i] = false;
    return true;
}

// Задание размерности по имени идентификатора или значению константы
bool TableVar::set_dimension(string name, int dimension)
{
    int hash = get_hash(name), chain = get_chain(name);
    return set_dimension(hash, chain, dimension);
}

// Задание флага инициализации для массивов по хэшу и номеру в цепочке
bool TableVar::set_is_init(int hash, int chain, bool is_init, int init_index)
{
    if(chain == -1) return false;
    table[hash][chain].is_init[init_index] = is_init;
    return true;
}

// Задание флага инициализации для массивов по имени идентификатора или значению константы
bool TableVar::set_is_init(string name, bool is_init, int init_index)
{
    int hash = get_hash(name), chain = get_chain(name);
    return set_is_init(hash, chain, is_init, init_index);
}

// Задание флага инициализации по хэшу и номеру в цепочке
bool TableVar::set_is_init(int hash, int chain, bool is_init)
{
    return set_is_init(hash, chain, is_init, 0);
}

// Задание флага инициализации по имени идентификатора или значению константы
bool TableVar::set_is_init(string name, bool is_init)
{
    return set_is_init(name, is_init, 0);
}

// Определение хэша и номера в цепочке
bool TableVar::get_location(string name, int &hash, int &chain)
{
    int h = get_hash(name), c = get_chain(name);
    if(c == -1) return false;
    hash = h;
    chain = c;
    return true;
}

// Получение структуры Lexeme по хэшу и номеру в цепочке
bool TableVar::get_Lexeme(int hash, int chain, Lexeme &Lexeme)
{
    if(chain == -1) return false;
    Lexeme = table[hash][chain];
    return true;
}

// Получение структуры Lexeme по имени идентификатора или значению константы
bool TableVar::get_Lexeme(string name, Lexeme &Lexeme)
{
    int hash = get_hash(name), chain = get_chain(name);
    return get_Lexeme(hash, chain, Lexeme);
}

// Отладочная печать
void TableVar::debug_print(ostream& stream)
{
    for(int i = 0; i < hashnum; i++)
    {
        if(table[i].size())
        {
            stream << i << ":\t[ ";
            for(int j = 0; j < (int)table[i].size(); j++)
            {
                stream << table[i][j].name;
                switch(table[i][j].type)
                {
                case 0:
                    stream << "\tnotype\tdim=";
                    break;
                case 1:
                    stream << "\tint\tdim=";
                    break;
                case 2:
                    stream << "\tfloat\tdim=";
                    break;
                }
                stream << table[i][j].dimension << "\tinit={";
                for(int k = 0; k < table[i][j].dimension; k++)
                {
                    stream << table[i][j].is_init[k];
                    if(k != table[i][j].dimension - 1) stream << " ";
                }
                if(j != (int)table[i].size() - 1) stream << "},\t";
                else stream << "}";
            }
            stream << " ]" << endl;
        }
    }
}

#undef default_hashnum
