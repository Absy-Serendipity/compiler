#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "headers/LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "Node.h"
using namespace std;


int main() {


    string inputString = "int main(int arg) {\n"
                         "    int x = -10;\n"
                         "    x = -10 - 1;\n"
                         "string y = \"compiler\";"
                         "    if (true) {\n"
                         "        while (false) {\n"
                         "            x = x + 1;\n"
                         "        }\n"
                         "    } else {\n"

                         "    }\n"
                         "    return 0;\n"
                         "}";


    inputString = "int main() {\n"

                         "string y = \"compiler\";"

                         "        while (false) {\n"
                         "            x = x + 1;\n"
                         "        }\n"



                         "    return 0;\n"
                         "}";

//    inputString = "int x = -10;";
    LexicalAnalyzer lexicalAnalyzer(inputString);
    vector<Token*> symbolTable;


    SyntaxAnalyzer syntaxAnalyzer(lexicalAnalyzer);

    Node* syntaxTree = syntaxAnalyzer.analyze();

    syntaxTree->printTree();

    Token* token = lexicalAnalyzer.getToken();
    while (token != nullptr){

        if (token->name != "whitespace"){

            symbolTable.push_back(token);

//            cout << "<" << token->name << ", " << token->value << ">" << endl;
            cout << token->name << " ";
        }



        token = lexicalAnalyzer.getToken();
    }



    return 0;
}