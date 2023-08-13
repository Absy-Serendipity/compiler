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

void Node::printTree(int depth) {

    for (int i = 0; i < depth; ++i) {
        cout << "   ";
    }

    if (depth > 0) {
        cout << "├─ ";
    }

    cout << getTokenName() << " : " << getTokenValue() << endl;

    for (Node* child : childNodeList) {
        child->printTree(depth + 1);
    }
}

void Node::replaceToken(Node* replaced, Node* replacing){
    delete replaced->token;
    replaced->token = replacing->token;
    replaced->childNodeList = replacing->childNodeList;
}

void Node::removeEpsilonMove(){
    for (vector<Node*>::iterator i = this->childNodeList.begin(); i != this->childNodeList.end();){
        if ((*i)->getTokenValue().empty() && (*i)->getChildNodeList().empty()){
            delete (*i)->token;
            delete (*i);
            i = this->childNodeList.erase(i);
        }
        else{
            (*i)->removeEpsilonMove();
            i++;
        }
    }
}
void Node::removeSingleSuccessor(){

    if (this->getChildNodeList().size() == 1){

        this->replaceToken(this, this->getChildNodeList().at(0));

        this->removeSingleSuccessor();
        return;
    }
    for (vector<Node*>::iterator i = this->childNodeList.begin(); i != this->childNodeList.end(); i++){
        (*i)->removeSingleSuccessor();
    }
}

void Node::removeSyntacticDetails(){
    for (vector<Node*>::iterator i = this->childNodeList.begin(); i != this->childNodeList.end();){

        if ((*i)->getTokenName() == "rbrace" || (*i)->getTokenName() == "lbrace" || (*i)->getTokenName() == "rparen"
        || (*i)->getTokenName() == "lparen" || (*i)->getTokenName() == "semi" || (*i)->getTokenName() == "comma"
        ){

            delete (*i)->token;
            delete (*i);
            i = this->childNodeList.erase(i);
        }

        else{
            (*i)->removeSyntacticDetails();
            i++;
        }
    }
}

void Node::swapOperator(){
//    if (!childNodeList.empty()){
//        cout << childNodeList.size() << endl;
//    }
//
//    for (Node* child : childNodeList) {
//        child->swapOperator();
//    }
    cout << this->childNodeList.size() << endl;
    for (vector<Node*>::iterator i = this->childNodeList.begin(); i != this->childNodeList.end();){

        if ((*i)->getTokenName() == "addsub" || (*i)->getTokenName() == "multidiv" || (*i)->getTokenName() == "comp"){

            delete this->token;

            this->token = (*i)->token;

            i = this->childNodeList.erase(i);


        }
        else{
            (*i)->swapOperator();
            i++;
        }



    }
}

void Node::abstractTree() {

    this->removeEpsilonMove();
    this->removeSyntacticDetails();
    this->removeSingleSuccessor();

    this->swapOperator();
}