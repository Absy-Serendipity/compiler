//
// Created by 박영재 on 2023/08/15.
//

#ifndef COMPILERPRJ_SEMANTICANALYZER_H
#define COMPILERPRJ_SEMANTICANALYZER_H

#include "headers/Node.h"
#include "headers/LexicalAnalyzer.h"
#include <unordered_map>
#include <queue>


using namespace std;

class SemanticAnalyzer {
private:

    class symbolTable{
    private:
        unordered_map<string, string> table;
        symbolTable* link;
    public:
        symbolTable(symbolTable* previousSymbolTable){
            this->link = previousSymbolTable;
        }
        symbolTable* getNextLink(){
            return this->link;
        }
        void addSymbol(const string& id, const string& type){
            if (verifyId(id)){
                (this->table)[id] = type;
            }
            else{
                cout << "id is already declared" << endl;
            }
        }
//        void setNextLink(symbolTable* nextLink){
//            this->link = nextLink;
//        }

        unordered_map<string, string>& getTable(){
            return this->table;
        }

        bool verifyId(const string& id){

            symbolTable* currentTable = this;

            while (currentTable != nullptr){
                if (currentTable->getTable().find(id) != currentTable->getTable().end()){
                    return true;
                }
                currentTable = currentTable->getNextLink();
            }
            return false;
        }

    };
    symbolTable* currentSymbolTable;
    Node* AST;


    void addSymbolTable();

public:
    SemanticAnalyzer(Node* header);
    void checkScope();

};


#endif //COMPILERPRJ_SEMANTICANALYZER_H
