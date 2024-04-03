#include <iostream>
#include <stdio.h>
#include "TableConst.h"
#include "TableVar.h"
#include "translator.h"

using namespace std;

int main()
{

    Translator a;
    cout << a.AnalyzeLexical("files/source.txt","files/tokens.txt","files/errors.txt");
    a.DebugPrint(cout);
    return 0;
}
