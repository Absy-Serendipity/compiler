//
// Created by 박영재 on 2023/08/11.
//

#ifndef COMPILERPRJ_NODE_H
#define COMPILERPRJ_NODE_H


#include "LexicalAnalyzer.h"
#include "queue"

class Node {
private:
    Token* token;
    vector<Node*> childNodeList;


    void replaceToken(Node* replaced, Node* replacing);
    void removeEpsilonMove();
    void removeSingleSuccessor();
    void removeSyntacticDetails();
    void swapOperator();
    void removeIrrelevantToken();
    void removeVDECLASSIGN();
    void replaceSTMT();
    void removeBLOCK();
public:
    Node(Token* token);
    void addChild(Node* childNode);
    vector<Node*>& getChildNodeList();
    string getTokenName();
    string getTokenValue();
    Token* getToken();

    void printTree(int depth = 0);
    void abstractTree();
};


#endif //COMPILERPRJ_NODE_H
