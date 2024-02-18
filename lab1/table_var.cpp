#include "table_var.h"
#include <cstdint>
// Размер хэш-таблицы по умолчанию
#define default_hashnum 100

// Подсчет хэша
int table_var::get_hash(string name)
{
    int hash = 0;
    for(int i = 0; i < static_cast<int>(name.size()); i++)
        hash += name[static_cast<uint64_t>(i)];
    return hash % hashnum;
}

// Подсчет номера в цепочке
int table_var::get_chain(string name)
{
    for(int i = 0, h = get_hash(name); i < static_cast<int>(table[h].size()); i++)
        if(name == table[static_cast<uint64_t>(h)][static_cast<uint64_t>(i)].name) return i;
    return -1;
}

// Конструктор с размером таблицы по умолчанию
table_var::table_var()
{
    hashnum=default_hashnum;
    table = new vector<lexeme> [hashnum];
}

// Конструктор с пользовательским размером таблицы
table_var::table_var(int new_hashnum)
{
    hashnum=new_hashnum;
    table = new vector<lexeme> [hashnum];
}

// Деструктор
table_var::~table_var()
{
    for(int i = 0; i < hashnum; i++)
        table[i].clear();
    delete [] table;
}

// Проверка есть ли элемент в таблице
inline bool table_var::contains(string name)
{
    if(get_chain(name) != -1) return true;
    return false;
}

// Добавление нового имени идентификатора или значения константы
bool table_var::add(string name)
{
    if(contains(name)) return false;
    int h = get_hash(name);
    table[h].push_back(lexeme(name));
    return true;
}

// Задание типа по хэшу и номеру в цепочке
bool table_var::set_type(int hash, int chain, int type)
{
    if(chain == -1) return false;
    table[static_cast<uint64_t>(hash)][static_cast<uint64_t>(chain)].type = type;
    return true;
}

// Задание типа по имени идентификатора или значению константы
bool table_var::set_type(string name, int type)
{
    int hash = get_hash(name), chain = get_chain(name);
    return set_type(hash, chain, type);
}

// Задание размерности по хэшу и номеру в цепочке
bool table_var::set_dimension(int hash, int chain, int dimension)
{
    if(chain == -1) return false;
    table[static_cast<uint64_t>(hash)][static_cast<uint64_t>(chain)].dimension = dimension;
    table[static_cast<uint64_t>(hash)][static_cast<uint64_t>(chain)].is_init.resize(static_cast<uint64_t>(dimension));
    for(int i = 0; i < dimension; i++)
        table[static_cast<uint64_t>(hash)][static_cast<uint64_t>(chain)].is_init[static_cast<uint64_t>(i)] = false;
    return true;
}

// Задание размерности по имени идентификатора или значению константы
bool table_var::set_dimension(string name, int dimension)
{
    int hash = get_hash(name), chain = get_chain(name);
    return set_dimension(hash, chain, dimension);
}

// Задание флага инициализации для массивов по хэшу и номеру в цепочке
bool table_var::set_is_init(int hash, int chain, bool is_init, int init_index)
{
    if(chain == -1) return false;
   table[static_cast<uint64_t>(hash)][static_cast<uint64_t>(chain)].is_init[static_cast<uint64_t>(init_index)] = is_init;
    return true;
}

// Задание флага инициализации для массивов по имени идентификатора или значению константы
bool table_var::set_is_init(string name, bool is_init, int init_index)
{
    int hash = get_hash(name), chain = get_chain(name);
    return set_is_init(hash, chain, is_init, init_index);
}

// Задание флага инициализации по хэшу и номеру в цепочке
bool table_var::set_is_init(int hash, int chain, bool is_init)
{
    return set_is_init(hash, chain, is_init, 0);
}

// Задание флага инициализации по имени идентификатора или значению константы
bool table_var::set_is_init(string name, bool is_init)
{
    return set_is_init(name, is_init, 0);
}

// Определение хэша и номера в цепочке
bool table_var::get_location(string name, int &hash, int &chain)
{
    int h = get_hash(name), c = get_chain(name);
    if(chain == -1) return false;
    hash = h;
    chain = c;
    return true;
}

// Получение структуры lexeme по хэшу и номеру в цепочке
bool table_var::get_lexeme(int hash, int chain, lexeme &lexeme)
{
    if(chain == -1) return false;
    lexeme = table[static_cast<uint64_t>(hash)][static_cast<uint64_t>(chain)];
    return true;
}

// Получение структуры lexeme по имени идентификатора или значению константы
bool table_var::get_lexeme(string name, lexeme &lexeme)
{
    int hash = get_hash(name), chain = get_chain(name);
    return get_lexeme(hash, chain, lexeme);
}

#undef default_hashnum