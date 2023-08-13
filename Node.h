//
// Created by 박영재 on 2023/08/11.
//

#ifndef COMPILERPRJ_NODE_H
#define COMPILERPRJ_NODE_H


#include "headers/LexicalAnalyzer.h"

class Node {
private:
    Token* token;
    vector<Node*> childNodeList;


    void replaceToken(Node* replaced, Node* replacing);
    void removeEpsilonMove();
    void removeSingleSuccessor();
    void removeSyntacticDetails();
    void swapOperator();
public:
    Node(Token* token);
    void addChild(Node* childNode);
    vector<Node*> getChildNodeList();
    string getTokenName();
    string getTokenValue();
    void printTree(int depth = 0);
    void abstractTree();
};


#endif //COMPILERPRJ_NODE_H
