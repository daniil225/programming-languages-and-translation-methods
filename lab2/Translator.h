#ifndef TRANSLATOR_H_
#define TRANSLATOR_H_

#include <iostream>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <string>
#include "TableConst.h"
#include "TableVar.h"
#include "Lexeme.h"
#include "Token.h"

using namespace std;

class Translator
{
private:
    // Постоянные таблицы
    TableConst<char> Letters;      // 0
    TableConst<char> Numbers;      // 1
    TableConst<string> Operations; // 2
    TableConst<string> KeyWords;   // 3
    TableConst<char> Separators;   // 4
    
    // Переменные таблицы
    TableVar Identifiers;          // 5
    TableVar Constants;            // 6
    
    // Файловые потоки
    ifstream in_source;
    ofstream out_token;
    ofstream out_error;
    
    // Счетчики для подробных сообщений об ошибке
    int AnalyzeLexicalStrnum, AnalyzeLexicalStrinc;

    // Анализ строки
    bool AnalyzeLexicalString(string str);
    
    // Удаление комментариев
    bool AnalyzeLexicalDecomment(string& str, bool is_changed);
    

    // Удаление пробелов
    static inline void Ltrim(string& out_)
    {
        int notwhite = static_cast<int>(out_.find_first_not_of(" \t\n"));
        out_.erase(0, static_cast<size_t>(notwhite));
    }

    static inline void Rtrim(string& out_)
    {
        int notwhite = static_cast<int>(out_.find_last_not_of(" \t\n"));
        out_.erase(static_cast<size_t>(notwhite + 1));
    }

    static inline void Trim(string& out_)
    {
        Ltrim(out_);
        Rtrim(out_);
    }

public:
    // Конструктор со вводом постоянных таблиц
    Translator();
    
    // Лексический анализ
    bool AnalyzeLexical(string file_source, string file_tokens, string file_error);
    
    // Отладочный вывод таблиц
    void DebugPrint(ostream& stream);

    ~Translator() = default;
};

#endif
