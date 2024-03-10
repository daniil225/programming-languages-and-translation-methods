#include <iostream>
#include <stdio.h>
#include "table_const.h"
#include "table_var.h"
#include <fstream>

using namespace std;



int main()
{
    fstream fout;
    fout.open("AbuseCode.mlg");

    TableConst<string> a;
    TableVar b;

    a.ReadFile("reserved_words.txt");
    //cout << "a.Contains(\"int\") = " << a.Contains("int") << endl;
    //cout << "a.Contains(\"main\") = " << a.Contains("main") << endl;

    string type, nameVariable;

    for(; !fout.eof(); )
    {
        fout >> type; fout >> nameVariable;
        
        if(a.Contains(type))
        {
            b.Add(nameVariable);

            if(type == "int")
            {
                cout << type << "\n";
                b.set_type(nameVariable,1);
            }
            if(type == "void")
                b.set_type(nameVariable,0);
        }
        
        
    }

    Lexeme c;
    b.get_lexeme("a", c);
    cout << "c.name = " << c.Name << endl;
    cout << "c.type = " << (c.Type==1?"int":"void") << endl;
    b.get_lexeme("main", c);
    cout << "c.name = " << c.Name << endl;
    cout << "c.type = " << (c.Type==1?"int":"void") << endl;
    
    //int num;
    
    //cout << "a.get_num(\"return\", num): num = " << num << endl;

    //string str;
    //a.get_val(num, str);
    //cout << "a.get_val(num, str): str = " << str << endl;

    // b.Add("avriable");
    // b.Add("vairable");
    // b.Add("vairalbe");
    // b.Add("variable");
    // int hash, chain;
    // b.GetLocation("variable", hash, chain);
    // cout << "b.GetLocation(\"variable\", hash, chain): hash = " << hash << "  chain = " << chain << endl;

    //b.set_type("variable", 2);
    //b.set_dimension("variable", 3);
    //b.set_is_init("variable", true);
    //b.set_is_init("variable", false, 1);
    //b.set_is_init("variable", true, 2);
    //lexeme c;
    //b.get_lexeme("variable", c);

    //cout << "c.name = " << c.name << endl;
    //cout << "c.type = " << c.type << endl;
    //cout << "c.is_init[0] = " << c.is_init[0] << endl;
    //cout << "c.is_init[1] = " << c.is_init[1] << endl;
    //cout << "c.is_init[2] = " << c.is_init[2] << endl;

    fout.close();

    return 0;
}
