#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../headers/LexicalAnalyzer.h"
#include "../headers/SyntaxAnalyzer.h"
#include "../headers/Node.h"
#include "../SemanticAnalyzer.h"
using namespace std;


int main() {


    string inputString = "int main(){"
                         "int x = 10;"
                         "string y = \"compiler\";"
                         "int z = add(x, 10);"
                         "char a = '1';"
                         "if (z > 100){ z = z - 100; }"

                         "return 0;"
                         "}";

//
    inputString = "int add(int x, int y, int z){"
                  "return x + y;"
                  "}"
                  "int main() {\n"

                         "string y = \"compiler\";"
                         "int x = 0;"
                         "        while (x > 0 & x <100 | false) {\n"
                         "            x = x + 1;\n"
                         "        }\n"
                         "x = add(x, y);"
                         "    return 0;\n"
                         "}";



    LexicalAnalyzer lexicalAnalyzer(inputString);

//    vector<Token*> symbolTable;
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
//    syntaxTree->printTree();
    syntaxTree->abstractTree();
//    cout << "\n\n\n\n\n\n\n\n\n";
    syntaxTree->printTree();

    SemanticAnalyzer semanticAnalyzer(syntaxTree);
    semanticAnalyzer.checkScope();

    return 0;
}






































