#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "headers/LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "Node.h"
using namespace std;


int main() {


    string inputString = "int main(){"
                         "int x = 10;"
                         "int y =  x + 20;"
                         "int z = add(x, y);"
                         "if (z > 100){ z = z - 100; }"
                         "else{"
                         "while(z <100 & x == 10){"
                         "z = z - 1;"
                         "}"
                         "}"
                         "return 0;"
                         "}";

//
//    inputString = "int add(int x, int y){"
//                  "return x + y;"
//                  "}"
//                  "int main(int arg1, char arg2) {\n"
//
//                         "string y = \"compiler\";"
//
//                         "        while (x > 0 & x <100 | false) {\n"
//                         "            x = x + 1;\n"
//                         "        }\n"
//                         "x = add(x, y);"
//                         "    return 0;\n"
//                         "}";



    LexicalAnalyzer lexicalAnalyzer(inputString);
    vector<Token*> symbolTable;
//    Token* token = lexicalAnalyzer.getToken();
//    while (token != nullptr){
//
//        if (token->name != "whitespace"){
//
//            symbolTable.push_back(token);
//
////            cout << "<" << token->name << ", " << token->value << ">" << endl;
//            cout << token->name << " ";
//        }
//
//        token = lexicalAnalyzer.getToken();
//    }

    SyntaxAnalyzer syntaxAnalyzer(lexicalAnalyzer);
//
    Node* syntaxTree = syntaxAnalyzer.analyze();
//
    syntaxTree->printTree();
    syntaxTree->abstractTree();
//    cout << "\n\n\n\n\n\n\n\n\n";
    syntaxTree->printTree();

    return 0;
}






































