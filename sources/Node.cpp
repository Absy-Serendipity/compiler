//
// Created by 박영재 on 2023/08/11.
//

#include "../headers/Node.h"

Node::Node(Token* token){
this->token = token;
}
void Node::addChild(Node* childNode){

//    this->childNodeList.insert(this->childNodeList.begin(), childNode);
    this->childNodeList.push_back(childNode);
}
vector<Node*>& Node::getChildNodeList(){
    return this->childNodeList;
}
string Node::getTokenName(){
    return this->token->name;
}
string Node::getTokenValue(){
    return this->token->value;
}
Token* Node::getToken(){
    return this->token;
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
    for (auto i = this->childNodeList.begin(); i != this->childNodeList.end(); i++){
        (*i)->removeSingleSuccessor();
    }
}

void Node::removeSyntacticDetails(){
    for (auto i = this->childNodeList.begin(); i != this->childNodeList.end();){

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

    for (auto i = this->childNodeList.begin(); i != this->childNodeList.end();){

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
void Node::removeIrrelevantToken(){
    string currentTokenName;
    for (auto i = this->childNodeList.begin(); i != this->childNodeList.end();){
        currentTokenName = (*i)->getTokenName();
        if (currentTokenName == "return"){

            delete (*i)->token;
            delete (*i);
            i = this->childNodeList.erase(i);
        }


        else{
            (*i)->removeIrrelevantToken();
            i++;
        }
    }
}
void Node::removeVDECLASSIGN(){
    queue<Node*> queue;
    queue.push(this);

    Node* currentNode;
    Node* lastChildNode;

    while(!queue.empty()){
        currentNode = queue.front();
        queue.pop();
        if (currentNode->getTokenName() == "VDECL"){

            lastChildNode = *(currentNode->getChildNodeList().end() - 1);

            if (lastChildNode->getTokenName() == "ASSIGN"){
                currentNode->getChildNodeList().pop_back();
                for (auto childNode: lastChildNode->getChildNodeList()){
                    if (childNode->getTokenName() != "assign"){
                        currentNode->addChild(childNode);
                    }
                }
                delete lastChildNode;
            }
        }
        else{
            for (auto childNode: currentNode->getChildNodeList()){
                queue.push(childNode);
            }
        }



    }
}

void Node::replaceSTMT(){
    queue<Node*> queue;
    queue.push(this);

    Node* currentNode;
    while (!queue.empty()){
        currentNode = queue.front();
        queue.pop();
        vector<Node*>& currentChildNodeList = currentNode->getChildNodeList();

        if (currentNode->getTokenName() == "STMT"){

            delete currentNode->token;
            currentNode->token = currentChildNodeList.at(0)->getToken();
            currentChildNodeList.erase(currentChildNodeList.begin());
        }

        for (auto childNode: currentChildNodeList){
            queue.push(childNode);
        }

    }


}
void Node::removeBLOCK(){
    queue<Node*> queue;
    queue.push(this);

    Node* currentNode;


    while(!queue.empty()){

        currentNode = queue.front();
        vector<Node*>& currentChildNodeList = currentNode->getChildNodeList();

        queue.pop();

        auto currentIter =  currentChildNodeList.begin();

        while (currentIter != currentChildNodeList.end()){

            if ((*currentIter)->getTokenName() == "BLOCK"){
                Node* blockNode = (*currentIter);


                currentIter = currentChildNodeList.erase(currentIter);



                currentIter = currentChildNodeList.insert(currentIter,
                                            blockNode->getChildNodeList().begin(),
                                            blockNode->getChildNodeList().end());

                delete blockNode;

            }
            else{
                queue.push(*currentIter);
                currentIter++;
            }


        }

    }

}


void Node::abstractTree() {

    this->removeEpsilonMove();
    this->removeSyntacticDetails();
    this->removeSingleSuccessor();
    this->swapOperator();
    this->removeIrrelevantToken();
    this->removeVDECLASSIGN();
    this->replaceSTMT();
    this->removeBLOCK();
}