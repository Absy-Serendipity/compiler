#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "headers/LexicalAnalyzer.h"
using namespace std;


int main() {
    vector<Token*> symbolTable;

    string inputString = "int main() {\n"
                         "    int x = -10;\n"
                         "    x = -10 - 1;\n"
                         "string y = \"compiler\""
                         "    if (x > 5) {\n"
                         "        while (x > 0) {\n"
                         "            x = x - 1;\n"
                         "        }\n"
                         "    } else {\n"

                         "    }\n"
                         "    return 0;\n"
                         "}";


    LexicalAnalyzer lexicalAnalyzer(inputString);

    Token* token = lexicalAnalyzer.getToken();
    while (token != nullptr){

        if (token->name != "whitespace"){

            symbolTable.push_back(token);

            cout << "token name: " << token->name << "   tokane value: " << token->value << endl;
        }
        token = lexicalAnalyzer.getToken();
    }



    return 0;
}