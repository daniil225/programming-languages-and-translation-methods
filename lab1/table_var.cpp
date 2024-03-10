#include "table_var.h"
#include <cstdint>
// Размер хэш-таблицы по умолчанию
#define default_hashnum 100

// Подсчет хэша
int TableVar::GetHash(string name)
{
    int hash = 0;
    for(int i = 0; i < static_cast<int>(name.size()); i++)
        hash += name[static_cast<uint64_t>(i)];
    return hash % HashNum;
}

// Подсчет номера в цепочке
int TableVar::GetChain(string name)
{
    for(int i = 0, h = GetHash(name); i < static_cast<int>(Table[h].size()); i++)
        if(name == Table[static_cast<uint64_t>(h)][static_cast<uint64_t>(i)].Name) return i;
    return -1;
}

// Конструктор с размером таблицы по умолчанию
TableVar::TableVar()
{
    HashNum=DefaultHashnum;
    Table = new vector<Lexeme> [HashNum];
}

// Конструктор с пользовательским размером таблицы
TableVar::TableVar(int new_hashnum)
{
    HashNum=new_hashnum;
    Table = new vector<Lexeme> [HashNum];
}

// Деструктор
TableVar::~TableVar()
{
    for(int i = 0; i < HashNum; i++)
        Table[i].clear();
    delete [] Table;
}

// Проверка есть ли элемент в таблице
inline bool TableVar::Contains(string name)
{
    if(GetChain(name) != -1) return true;
    return false;
}

// Добавление нового имени идентификатора или значения константы
bool TableVar::Add(string name)
{
    if(Contains(name)) return false;
    int h = GetHash(name);
    Table[h].push_back(Lexeme(name));
    return true;
}

// Задание типа по хэшу и номеру в цепочке
bool TableVar::SetType(int hash, int chain, int type)
{
    if(chain == -1) return false;
    Table[static_cast<uint64_t>(hash)][static_cast<uint64_t>(chain)].Type = type;
    return true;
}

// Задание типа по имени идентификатора или значению константы
bool TableVar::set_type(string name, int type)
{
    int hash = GetHash(name), chain = GetChain(name);
    return SetType(hash, chain, type);
}

// Задание размерности по хэшу и номеру в цепочке
bool TableVar::SetDimension(int hash, int chain, int dimension)
{
    if(chain == -1) return false;
    Table[static_cast<uint64_t>(hash)][static_cast<uint64_t>(chain)].Dimension = dimension;
    Table[static_cast<uint64_t>(hash)][static_cast<uint64_t>(chain)].IsInit.resize(static_cast<uint64_t>(dimension));
    for(int i = 0; i < dimension; i++)
        Table[static_cast<uint64_t>(hash)][static_cast<uint64_t>(chain)].IsInit[static_cast<uint64_t>(i)] = false;
    return true;
}

// Задание размерности по имени идентификатора или значению константы
bool TableVar::SetDimension(string name, int dimension)
{
    int hash = GetHash(name), chain = GetChain(name);
    return SetDimension(hash, chain, dimension);
}

// Задание флага инициализации для массивов по хэшу и номеру в цепочке
bool TableVar::SetIsInit(int hash, int chain, bool is_init, int init_index)
{
    if(chain == -1) return false;
   Table[static_cast<uint64_t>(hash)][static_cast<uint64_t>(chain)].IsInit[static_cast<uint64_t>(init_index)] = is_init;
    return true;
}

// Задание флага инициализации для массивов по имени идентификатора или значению константы
bool TableVar::SetIsInit(string name, bool is_init, int init_index)
{
    int hash = GetHash(name), chain = GetChain(name);
    return SetIsInit(hash, chain, is_init, init_index);
}

// Задание флага инициализации по хэшу и номеру в цепочке
bool TableVar::SetIsInit(int hash, int chain, bool is_init)
{
    return SetIsInit(hash, chain, is_init, 0);
}

// Задание флага инициализации по имени идентификатора или значению константы
bool TableVar::SetIsInit(string name, bool is_init)
{
    return SetIsInit(name, is_init, 0);
}

// Определение хэша и номера в цепочке
bool TableVar::GetLocation(string name, int &hash, int &chain)
{
    int h = GetHash(name), c = GetChain(name);
    if(chain == -1) return false;
    hash = h;
    chain = c;
    return true;
}

// Получение структуры lexeme по хэшу и номеру в цепочке
bool TableVar::GetLexeme(int hash, int chain, Lexeme &lexeme)
{
    if(chain == -1) return false;
    lexeme = Table[static_cast<uint64_t>(hash)][static_cast<uint64_t>(chain)];
    return true;
}

// Получение структуры lexeme по имени идентификатора или значению константы
bool TableVar::get_lexeme(string name, Lexeme &lexeme)
{
    int hash = GetHash(name), chain = GetChain(name);
    return GetLexeme(hash, chain, lexeme);
}

#undef default_hashnum
