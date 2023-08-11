//
// Created by 박영재 on 2023/08/11.
//

#include "Node.h"

Node::Node(Token* token){
this->token = token;
}
void Node::addChild(Node* childNode){
    this->childNodeList.push_back(childNode);
}
vector<Node*> Node::getChildNodeList(){
    return this->childNodeList;
}
string Node::getTokenName(){
    return this->token->name;
}
string Node::getTokenValue(){
    return this->token->value;
}