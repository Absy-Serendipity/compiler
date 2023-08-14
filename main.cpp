#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "headers/LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "Node.h"
using namespace std;


int main() {


    string inputString = "int main(int x, string y){"
                         ""
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
//                         "        while (false) {\n"
//                         "            x = x + 1;\n"
//                         "        }\n"
//
//
//
//                         "    return 0;\n"
//                         "}";

    inputString = "while(x > 0 & x <100){"
                  "x = x - 1;"
                  "}";

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