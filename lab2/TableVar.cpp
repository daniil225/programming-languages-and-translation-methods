#include "TableVar.h"
// Размер хэш-таблицы по умолчанию
#define DefaultHashnum 100

// Подсчет хэша
int TableVar::GetHash(string Name)
{
    int hash = 0;
    for(int i = 0; i < static_cast<int>(Name.size()); i++)
        hash += Name[static_cast<size_t>(i)];
    return hash % HashNum;
}

// Подсчет номера в цепочке
int TableVar::GetChain(string Name)
{
    for(int i = 0, h = GetHash(Name); i < static_cast<int>(Table[h].size()); i++)
        if(Name == Table[static_cast<size_t>(h)][static_cast<size_t>(i)].Name) return i;
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
inline bool TableVar::Contains(string Name)
{
    if(GetChain(Name) != -1) return true;
    return false;
}

// Добавление нового имени идентификатора или значения константы
bool TableVar::Add(string Name)
{
    if(Contains(Name)) return false;
    int h = GetHash(Name);
    Table[h].push_back(Lexeme(Name));
    return true;
}

// Задание типа по хэшу и номеру в цепочке
bool TableVar::SetType(int hash, int Chain, int Type)
{
    if(Chain == -1) return false;
    Table[static_cast<size_t>(hash)][static_cast<size_t>(Chain)].Type = Type;
    return true;
}

// Задание типа по имени идентификатора или значению константы
bool TableVar::SetType(string Name, int Type)
{
    int hash = GetHash(Name), Chain = GetChain(Name);
    return SetType(hash, Chain, Type);
}

// Задание размерности по хэшу и номеру в цепочке
bool TableVar::SetDimension(int hash, int Chain, int Dimension)
{
    if(Chain == -1) return false;
    Table[static_cast<size_t>(hash)][static_cast<size_t>(Chain)].Dimension = Dimension;
    Table[static_cast<size_t>(hash)][static_cast<size_t>(Chain)].IsInit.resize(static_cast<size_t>(Dimension));
    for(int i = 0; i < Dimension; i++)
        Table[static_cast<size_t>(hash)][static_cast<size_t>(Chain)].IsInit[static_cast<size_t>(i)] = false;
    return true;
}

// Задание размерности по имени идентификатора или значению константы
bool TableVar::SetDimension(string Name, int Dimension)
{
    int hash = GetHash(Name), Chain = GetChain(Name);
    return SetDimension(hash, Chain, Dimension);
}

// Задание флага инициализации для массивов по хэшу и номеру в цепочке
bool TableVar::SetIsInit(int hash, int Chain, bool is_init, int init_index)
{
    if(Chain == -1) return false;
    Table[static_cast<size_t>(hash)][static_cast<size_t>(Chain)].IsInit[static_cast<size_t>(init_index)] = is_init;
    return true;
}

// Задание флага инициализации для массивов по имени идентификатора или значению константы
bool TableVar::SetIsInit(string Name, bool is_init, int init_index)
{
    int hash = GetHash(Name), Chain = GetChain(Name);
    return SetIsInit(hash, Chain, is_init, init_index);
}

// Задание флага инициализации по хэшу и номеру в цепочке
bool TableVar::SetIsInit(int hash, int Chain, bool is_init)
{
    return SetIsInit(hash, Chain, is_init, 0);
}

// Задание флага инициализации по имени идентификатора или значению константы
bool TableVar::SetIsInit(string Name, bool is_init)
{
    return SetIsInit(Name, is_init, 0);
}

// Определение хэша и номера в цепочке
bool TableVar::GetLocation(string Name, int &hash, int &Chain)
{
    int h = GetHash(Name), c = GetChain(Name);
    if(Chain == -1) return false;
    hash = h;
    Chain = c;
    return true;
}

// Получение структуры lexeme по хэшу и номеру в цепочке
bool TableVar::GetLexeme(int hash, int Chain, Lexeme &lexeme)
{
    if(Chain == -1) return false;
    lexeme = Table[static_cast<size_t>(hash)][static_cast<size_t>(Chain)];
    return true;
}

// Получение структуры lexeme по имени идентификатора или значению константы
bool TableVar::GetLexeme(string Name, Lexeme &lexeme)
{
    int hash = GetHash(Name), Chain = GetChain(Name);
    return GetLexeme(hash, Chain, lexeme);
}

// Отладочная печать
void TableVar::DebugPrint(ostream& stream)
{
    for(int i = 0; i < HashNum; i++)
    {
        if(Table[i].size())
        {
            stream << i << ":\t[ ";
            for(int j = 0; j < static_cast<int>(Table[i].size()); j++)
            {
                stream << Table[static_cast<size_t>(i)][static_cast<size_t>(j)].Name;
                switch(Table[static_cast<size_t>(i)][static_cast<size_t>(j)].Type)
                {
                case 0:
                    stream << "\tnotype\tdim=";
                    break;
                case 1:
                    stream << "\tint\tdim=";
                    break;
                }
                stream << Table[static_cast<size_t>(i)][static_cast<size_t>(j)].Dimension << "\tinit={";
                for(int k = 0; k < Table[static_cast<size_t>(i)][static_cast<size_t>(j)].Dimension; k++)
                {
                    stream << Table[static_cast<size_t>(i)][static_cast<size_t>(j)].IsInit[static_cast<size_t>(k)];
                    if(k != Table[static_cast<size_t>(i)][static_cast<size_t>(j)].Dimension - 1) stream << " ";
                }
                if(j != static_cast<int>(Table[static_cast<size_t>(i)].size() - 1)) stream << "},\t";
                else stream << "}";
            }
            stream << " ]" << endl;
        }
    }
}

#undef  DefaultHashnum
