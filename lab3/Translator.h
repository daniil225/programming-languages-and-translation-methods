#ifndef Translator_H_INCLUDED
#define Translator_H_INCLUDED

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include "TableConst.h"
#include "TableVar.h"
#include "Lexeme.h"
#include "Token.h"

using namespace std;

class Translator
{
private:
    // Постоянные таблицы
    TableConst<char> letters;      // 0
    TableConst<char> numbers;      // 1
    TableConst<string> operations; // 2
    TableConst<string> keywords;   // 3
    TableConst<char> separators;   // 4
    // Переменные таблицы
    TableVar identifiers;          // 5
    TableVar constants;            // 6
    // Файловые потоки
    ifstream in_source;
    ofstream out_Token;
    ofstream out_error;
    // Анализ строки
    bool analyze_lexical_string(string str);
    // Удаление комментариев
    bool analyze_lexical_decomment(string& str, bool is_changed);
    // Счетчики для подробных сообщений об ошибке
    int analyze_lexical_strnum, analyze_lexical_strinc;
    // Удаление пробелов
    static inline void ltrim(string& out_)
    {
        int notwhite = out_.find_first_not_of(" \t\n");
        out_.erase(0, notwhite);
    }
    static inline void rtrim(string& out_)
    {
        int notwhite = out_.find_last_not_of(" \t\n");
        out_.erase(notwhite + 1);
    }
    static inline void trim(string& out_)
    {
        ltrim(out_);
        rtrim(out_);
    }
    /** Синтаксический анализ    */
    // Определяем какая строка содержится в токене
    string get_Token_text(Token get_t);
    // Структура элемент таблицы разбора
    struct table_parse_elem
    {
        vector<string> terminal; // Терминалы
        int jump;                // Переход
        bool accept;             // Принимать или нет
        bool stack_;             // Класть в стек или нет
        bool return_;            // Возвращать или нет
        bool error;              // Может ли быть ошибка

    };
    // Таблица разбора
    vector<table_parse_elem> table_parse;
    // Структура элемент постфиксной записи
    struct postfix_elem
    {
        string id;
        short int type;
        postfix_elem()
        {
            id = "", type = 0;
        }
        postfix_elem(string id_, int type_)
        {
            id = id_, type = type_;
        }
        postfix_elem(string id_)
        {
            id = id_, type = 1;
        }
        friend ostream& operator << (ostream& ostream_, const postfix_elem& pe_)
        {
            ostream_ << pe_.id;
            return ostream_;
        }
    };
    // Сравнение приоритетов операций
    bool priority_le(string what, string with_what);
    // Постфиксная запись
    vector<postfix_elem> postfix_record;
    // Построение постфиксной записи
    bool make_postfix(vector<Token> t);
public:
    // Конструктор со вводом постоянных таблиц
    Translator();
    // Отладочный вывод таблиц
    void debug_print(ostream& stream);
    // Лексический анализ
    bool analyze_lexical(string file_source, string file_Tokens, string file_error);
    // Синтаксический анализ
    bool analyze_syntactical(string file_Tokens, string file_error);
    // Печать постфиксной записи в файл и на экран
    void postfix_print(string file_tree);
};

#endif // Translator_H_INCLUDED
