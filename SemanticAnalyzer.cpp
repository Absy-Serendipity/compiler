//
// Created by 박영재 on 2023/08/15.
//

#include "SemanticAnalyzer.h"

SemanticAnalyzer::SemanticAnalyzer(Node* header){
    this->AST = header;
    this->currentSymbolTable = nullptr;
}


void SemanticAnalyzer::checkScope(){
    queue<Node*> queue;

    queue.push(this->AST);

    Node* currentNode;
    vector<Node*> currentChildNodeList;

    while (!queue.empty()){
        currentNode = queue.front();

        string currentTokenName = currentNode->getTokenName();
        currentChildNodeList = currentNode->getChildNodeList();
        auto iter = currentChildNodeList.begin();

        if (currentTokenName == "BLOCK"){
            auto newSymbolTable = new symbolTable(this->currentSymbolTable);
            this->currentSymbolTable = newSymbolTable;
        }
        else if (currentTokenName == "FDECL" || currentTokenName == "VDECL" || currentTokenName == "ARG" || currentTokenName == "MOREARGS"){
            this->currentSymbolTable->addSymbol(currentChildNodeList.at(1)->getTokenValue(), currentChildNodeList.at(0)->getTokenValue());
            iter = iter + 2;
        }
        else if (currentTokenName == "id"){
            if (this->currentSymbolTable->verifyId(currentNode->getTokenValue())){
                cout << currentNode->getTokenValue() << " well formed" << endl;
            }
            else{
                cout << currentNode->getTokenValue() << " not well formed" << endl;
                exit(0);
            }
        }


        queue.pop();

        for (; iter != currentChildNodeList.end(); iter++){
            queue.push(*iter);
        }


    }

}

