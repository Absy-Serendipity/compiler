//
// Created by 박영재 on 2023/08/10.
//

#include "SyntaxAnalyzer.h"

// constructor
SyntaxAnalyzer::SyntaxAnalyzer(const LexicalAnalyzer& lexicalAnalyzer): lexicalAnalyzer(lexicalAnalyzer){
    this->currentToken = this->nextToken();
};



// getters and subroutines
string SyntaxAnalyzer::getAction(int currentState, const string& inputToken){
    return this->SLRTable[currentState][inputToken];
}
Token* SyntaxAnalyzer::nextToken(){
    return this->lexicalAnalyzer.getToken();
}

vector<string> SyntaxAnalyzer::getRHS(int ruleNumber){
    return this->RHSList.at(ruleNumber);
}
string SyntaxAnalyzer::getLHS(int ruleNumber){
    return this->LHSList.at(ruleNumber);
}












// main routines
void SyntaxAnalyzer::goTo(int stateNumber){
    this->stateStack.push(stateNumber);
}

void SyntaxAnalyzer::shift(){
    auto* newNode = new Node(this->currentToken);
    this->currentToken = this->nextToken();
    this->leftSubstring.push(newNode);
}


void SyntaxAnalyzer::reduce(int ruleNumber){
    string LHS = this->getLHS(ruleNumber);
    vector<string> RHS = this->getRHS(ruleNumber);
    auto* newToken = new Token();
    newToken->value = LHS;
    newToken->name = "";

    auto* newNode = new Node(newToken);

    for (const auto& term: RHS){

    }
}

bool SyntaxAnalyzer::implementAction(string& action){
    char firstChar = action.front();

    if (isalpha(firstChar)){
        int ruleNumber =  stoi(action.substr(1));

        // shift
        if (firstChar == 's'){
            this->shift();
        }
        // reduce
        else if (firstChar == 'r'){
            this->reduce(ruleNumber);
        }
        // accept
        else if (firstChar == 'a'){
            return true;
        }
    }
    // goto
    else if (isdigit(firstChar)){
        int nextState =  stoi(action);
        this->goTo(nextState);
    }
    return false;

}

Node* SyntaxAnalyzer::analyze(){


    int currentState;
    bool isAccepted = false;
    this->stateStack.push(0);


    while (true){
        currentState = stateStack.top();
        string action = this->getAction(currentState, this->currentToken->value);
        isAccepted = this->implementAction(action);

        if (isAccepted){
            return this->syntaxTree;
        }
    }
    return nullptr;
}
