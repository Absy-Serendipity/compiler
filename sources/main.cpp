#include <fstream>
#include <string>
#include "../headers/LexicalAnalyzer.h"
#include "../headers/SyntaxAnalyzer.h"
#include "../headers/Node.h"
#include "../headers/SemanticAnalyzer.h"
using namespace std;


int main() {

    string inputString = "int add(int x, int y, int z){"
                  "return x + y;"
                  "}"
                  "int main(int x, int y) {\n"

                         "string y = \"compiler\";"
                         "int x = 0;"
                         "        while (x > 0 & x <100 | false) {\n"
                         "            x = x + 1;\n"
                         "        }\n"
                         "x = add(x, y);"
                         "    return 0;\n"
                         "}";



    LexicalAnalyzer lexicalAnalyzer(inputString);

    SyntaxAnalyzer syntaxAnalyzer(lexicalAnalyzer);

    Node* syntaxTree = syntaxAnalyzer.analyze();

    syntaxTree->abstractTree();
    syntaxTree->printTree();

    SemanticAnalyzer semanticAnalyzer(syntaxTree);


//    working on semanticAnalyzer
//    semanticAnalyzer.checkScope();

    return 0;
}






































