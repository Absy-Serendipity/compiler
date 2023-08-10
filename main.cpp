#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "LexicalAnalyzer.h"
using namespace std;


int main() {
    vector<Token*> symbolTable;

    string inputString = "\"asdfsa!";


    LexicalAnalyzer lexicalAnalyzer(inputString);

    Token* token = lexicalAnalyzer.getToken();
    while (token != nullptr){
        if (token->name != "WHITESPACE"){

            symbolTable.push_back(token);

            cout << "token name: " << token->name << "   tokane value: " << token->value << endl;
        }
        token = lexicalAnalyzer.getToken();
    }



    return 0;
}