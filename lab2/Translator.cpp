#include "Translator.h"

// Конструктор со вводом постоянных таблиц
Translator::Translator()
{
    Letters.ReadFile("files/table_letters.txt");
    Numbers.ReadFile("files/table_numbers.txt");
    Operations.ReadFile("files/table_operations.txt");
    KeyWords.ReadFile("files/table_keywords.txt");
    Separators.ReadFile("files/table_separators.txt");
}

// Лексический анализ
bool Translator::AnalyzeLexical(string file_source, string file_tokens, string file_error)
{
    in_source.open(file_source.c_str(), ios::in);
    out_token.open(file_tokens.c_str(), ios::out);
    out_error.open(file_error.c_str(), ios::out);
    bool flag_error = false;
    // bool flag_coment = false;
    string str;
    AnalyzeLexicalStrnum = 1;
    while(!in_source.eof() && !flag_error)
    {
        getline(in_source, str);
        if(!in_source.eof())
        {
            AnalyzeLexicalStrinc = 0;
            string strold = str;
            if(!AnalyzeLexicalDecomment(str, true))
            {
                out_error << "Error in string " << AnalyzeLexicalStrnum << ": " << strold << endl;
                cout << "Error in string " << AnalyzeLexicalStrnum << ": " << strold << endl;
                return false;
            }
            AnalyzeLexicalStrnum += AnalyzeLexicalStrinc;
            flag_error = !AnalyzeLexicalString(str);
            if(flag_error)
            {
                out_error << "Error in string " << AnalyzeLexicalStrnum << ": " << str << endl;
                cout << "Error in string " << AnalyzeLexicalStrnum << ": " << str << endl;
            }
            AnalyzeLexicalStrnum ++;
        }
    }
    in_source.close();
    out_token.close();
    out_error.close();
    return !flag_error;
}

// Очистка от комментариев
bool Translator::AnalyzeLexicalDecomment(string& str, bool is_changed)
{
    if(str.size())
    {
        bool change = false;
        size_t index_c = str.find("//"), index_c1 = str.find("/*"), index_c2;
        if (index_c != string::npos && index_c < index_c1)
        {
            str.erase(index_c);
            change = true;
        }
        index_c1 = str.find("/*");
        index_c2 = str.find("*/");
        if(index_c2 < index_c1)
        {
            out_error << "Error: incorrect coment" << endl;
            cout << "Error: incorrect coment" << endl;
            return false;
        }
        while(index_c1 != string::npos && index_c2 != string::npos)
        {
            string tmpstr = str;
            str.erase(index_c1);
            tmpstr.erase(0, index_c2 + 2);
            str += tmpstr;
            index_c1 = str.find("/*");
            index_c2 = str.find("*/");
            change = true;
        }
        index_c1 = str.find("/*");
        index_c2 = str.find("*/");
        if(index_c1 != string::npos && index_c2 == string::npos)
        {
            str.erase(index_c1);
            string tmpstr;
            if(!in_source.eof())
            {
                getline(in_source, tmpstr);
                AnalyzeLexicalStrinc++;
            }
            else
            {
                out_error << "Error: incorrect coment" << endl;
                cout << "Error: incorrect coment" << endl;
                return false;
            }
            while(tmpstr.find("*/") == string::npos)
            {
                if(!in_source.eof())
                {
                    getline(in_source, tmpstr);
                    AnalyzeLexicalStrinc++;
                }
                else
                {
                    out_error << "Error: incorrect coment" << endl;
                    cout << "Error: incorrect coment" << endl;
                    return false;
                }
            }
            index_c2 = tmpstr.find("*/");
            tmpstr.erase(0, index_c2 + 2);
            str += " " + tmpstr;
            change = true;
        }
        index_c1 = str.find("/*");
        index_c2 = str.find("*/");
        if((index_c1 != string::npos && index_c2 == string::npos) ||
                (index_c1 == string::npos && index_c2 != string::npos))
        {
            out_error << "Error: incorrect coment" << endl;
            cout << "Error: incorrect coment" << endl;
            return false;
        }
        if(is_changed)
            return AnalyzeLexicalDecomment(str, change);
    }
    return true;
}

// Анализ строки
bool Translator::AnalyzeLexicalString(string str)
{
    Trim(str);
    bool flag_error = false;
    if(str.size())
    {
        cout << "AnalyzeLexicalString started with str = "<< str << endl;
        char sym_1 = str[0], sym_2 = str[1];
        // Проверка первого символа
        string str_1, str_2;
        stringstream str_stream;
        str_stream << sym_1;
        str_1 = str_stream.str();
        str_stream << sym_2;
        str_2 = str_stream.str();
        int first_sym_type = -1;
        if(Letters.Contains(sym_1))
            first_sym_type = 0;
        if(Numbers.Contains(sym_1) || sym_1 == '-')
            first_sym_type = 1;
        if(Operations.Contains(str_1) || Operations.Contains(str_2))
            first_sym_type = 2;
        if(Separators.Contains(sym_1))
            first_sym_type = 3;

        switch(first_sym_type)
        {
        /*case -1: // Недопустимый символ
        {
            out_error << "Error: unresolved first symbol" << endl;
            cout << "Error: unresolved first symbol" << endl;
            return false;
        }
        break;*/
        case 0: // Идентификатор
        {
            // Получим полное название идентификатора
            string idname = str;
            int i;
            bool finded = false;
            for(i = 1; i < static_cast<int>(idname.size()) && !finded; i++)
                finded = !(Letters.Contains(str[static_cast<size_t>(i)]) || Numbers.Contains(str[static_cast<size_t>(i)]));
            if(finded)
            {
                idname.erase(static_cast<size_t>( i - 1 ));
                str.erase(0, static_cast<size_t>( i - 1 ));
            }
            else
                str.erase(0);
            Trim(idname);
            Trim(str);
            if(KeyWords.Contains(idname)) // Если ключевое слово
            {
                if(KeyWords.GetNum(idname, i))
                    out_token << Token(3, i, -1);
            }
            else // Иначе в таблицу идентификаторов
            {
                Identifiers.Add(idname);
                int Table, Chain;
                Identifiers.GetLocation(idname, Table, Chain);
                out_token << Token(5, Table, Chain);
            }
            return AnalyzeLexicalString(str);
        }
        break;
        case 1:  // Константа
        {
            string constval = str;
            int i;
            bool finded = false;
            for(i = 1; i < static_cast<int>(constval.size()) && !finded; i++)
                finded = !(Numbers.Contains(str[static_cast<size_t>(i)]) || str[static_cast<size_t>(i)] == '.' || str[static_cast<size_t>(i)] == ' ');
            string str_t1, str_t2;
            stringstream str_stream_t;
            str_stream_t << str[static_cast<size_t>(i-1)];
            str_t1 = str_stream_t.str();
            str_stream_t << str[static_cast<size_t>(i)];
            str_t2 = str_stream_t.str();
            if(!Operations.Contains(str_t1) && !Operations.Contains(str_t2) && !Separators.Contains(str[static_cast<size_t>(i-1)]))
            {
                out_error << "Error: incorrect constant" << endl;
                cout << "Error: incorrect constant" << endl;
                return false;
            }
            if(finded)
            {
                constval.erase(static_cast<size_t>(i-1));
                str.erase(0, static_cast<size_t>(i-1));
            }
            else
                str.erase(0);
            Trim(constval);
            Trim(str);
            if(constval.find_last_of('.') - constval.find_first_of('.') != 0)
            {
                out_error << "Error: incorrect constant" << endl;
                cout << "Error: incorrect constant" << endl;
                return false;
            }
            else
            {
                Constants.Add(constval);
                int Table, Chain;
                Identifiers.GetLocation(constval, Table, Chain);
                out_token << Token(6, Table, Chain);
            }
            return AnalyzeLexicalString(str);
        }
        break;
        case 2: // Операция
        {
            int Table;
            if(Operations.Contains(str_2)) // Двухсимвольная
            {
                Operations.GetNum(str_2, Table);
                out_token << Token(4, Table, -1);
                str.erase(0, 2);
                Trim(str);
                return AnalyzeLexicalString(str);
            }
            if(Operations.Contains(str_1)) // Односимвольная
            {
                Operations.GetNum(str_1, Table);
                out_token << Token(4, Table, -1);
                str.erase(0, 1);
                Trim(str);
                return AnalyzeLexicalString(str);
            }
        }
        break;
        case 3: // Разделитель
        {
            int Table;
            Separators.GetNum(str[0], Table);
            out_token << Token(4, Table, -1);
            str.erase(0, 1);
            Trim(str);
            return AnalyzeLexicalString(str);
        }
        break;
        default: // Непонятно что
        {
            out_error << "Error: can`t determine symbol \"" << str_1 << "\"" << endl;
            cout << "Error: can`t determine symbol \"" << str_1 << "\"" << endl;
            return false;
        }
        break;
        }
    }
    return !flag_error;
}

// Отладочный вывод таблиц
void Translator::DebugPrint(ostream& stream)
{
    stream << "ID`s:" << endl;
    Identifiers.DebugPrint(stream);
    stream << "CONST`s:" << endl;
    Constants.DebugPrint(stream);
}

