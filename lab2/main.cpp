#include <iostream>
#include <stdio.h>
#include "TableConst.h"
#include "TableVar.h"
#include "translator.h"

using namespace std;

int main()
{
    /*TableConst<string> a;
    a.ReadFile("reserved_words.txt");
    cout << "a.Contains(\"int\") = " << a.Contains("int") << endl;
    cout << "a.Contains(\"double\") = " << a.Contains("double") << endl;

    int num;
    a.GetNum("return", num);
    cout << "a.GetNum(\"return\", num): num = " << num << endl;

    string str;
    a.GetVal(num, str);
    cout << "a.GetVal(num, str): str = " << str << endl;

    TableVar b;
    b.Add("avriable");
    b.Add("vairable");
    b.Add("vairalbe");
    b.Add("variable");
    int hash, Chain;
    b.GetLocation("variable", hash, Chain);
    cout << "b.GetLocation(\"variable\", hash, Chain): hash = " << hash << "  Chain = " << Chain << endl;

    b.SetType("variable", 2);
    b.SetDimension("variable", 3);
    b.SetIsInit("variable", true);
    b.SetIsInit("variable", false, 1);
    b.SetIsInit("variable", true, 2);
    lexeme c;
    b.GetLexeme("variable", c);

    cout << "c.Name = " << c.Name << endl;
    cout << "c.Type = " << c.Type << endl;
    cout << "c.IsInit[0] = " << c.IsInit[0] << endl;
    cout << "c.IsInit[1] = " << c.IsInit[1] << endl;
    cout << "c.IsInit[2] = " << c.IsInit[2] << endl;*/

    Translator a;
    cout << a.AnalyzeLexical("files/source.txt","files/tokens.txt","files/errors.txt");
    a.DebugPrint(cout);
    return 0;
}
