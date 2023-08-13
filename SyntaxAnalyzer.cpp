//
// Created by 박영재 on 2023/08/10.
//

#include "SyntaxAnalyzer.h"

// constructor
SyntaxAnalyzer::SyntaxAnalyzer(const LexicalAnalyzer& lexicalAnalyzer): lexicalAnalyzer(lexicalAnalyzer){};


string SyntaxAnalyzer::getExpectedToken(int currentState, const string& inputToken){
    string expectedTokenList;
    for (const auto& entry : this->SLRTable[currentState]) {
        for (const auto& terminal: this->terminalList){
            if (entry.first == terminal){
                expectedTokenList += entry.first + ", ";
                break;
            }
        }
    }
    return expectedTokenList;
}

// getters and subroutines
string SyntaxAnalyzer::getAction(int currentState, const string& inputToken){
//    cout << currentState << "    " << inputToken << "      '" << this->SLRTable[currentState][inputToken] <<"'"<< endl;
    if (this->SLRTable[currentState].find(inputToken) == this->SLRTable[currentState].end()){

        string errorMsg = "After " +  this->leftSubstring.top()->getTokenName() + ", expected token(s): " + this->getExpectedToken(currentState, inputToken) + " but input token: " + inputToken;
        cout << errorMsg << endl;
        throw SyntaxErrorException(errorMsg);
    }

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

void SyntaxAnalyzer::shift(int stateNumber){
    auto* newNode = new Node(this->currentToken);
    this->currentToken = this->nextToken();
    this->leftSubstring.push(newNode);
    this->stateStack.push(stateNumber);
}


void SyntaxAnalyzer::reduce(int ruleNumber){

    string LHS = this->getLHS(ruleNumber);
    vector<string> RHS = this->getRHS(ruleNumber);

//    cout << ruleNumber << " " << this->getLHS(ruleNumber) << " " << RHS.size() << endl;
    auto* newNode = new Node(new Token{LHS, ""});

    Node* rightMostTerm;


    for (int RHSIdx = (int) RHS.size() - 1; RHSIdx >= 0; RHSIdx--){
        rightMostTerm = this->leftSubstring.top();
        if (RHS.at(RHSIdx) == rightMostTerm->getTokenName()){
            newNode->addChild((rightMostTerm));
            this->leftSubstring.pop();
            this->stateStack.pop();
        }
        else{
            cout << "stack unmatched error" << endl;
        }
    }

    this->leftSubstring.push(newNode);
    this->implementAction(this->getAction(this->stateStack.top(), newNode->getTokenName()));
}

bool SyntaxAnalyzer::implementAction(const string& action){
    char actionType = action.front();
// shift
    if (actionType == 's'){
        this->shift(stoi(action.substr(1)));
    }
        // reduce
    else if (actionType == 'r'){
        this->reduce(stoi(action.substr(1)));

    }
        // accept
    else if (actionType == 'a'){
        return true;
    }
    // goto
    if (isdigit(actionType)){
        int stateNumber =  stoi(action);
        this->goTo(stateNumber);
    }

    return false;

}

Node* SyntaxAnalyzer::analyze(){

    int currentState;
    bool accepted = false;
    this->stateStack.push(0);
    this->currentToken = this->nextToken();
    string action;

    while (!accepted){


        if (this->currentToken->name != "whitespace"){
            action = this->getAction(stateStack.top(), this->currentToken->name);
            accepted = this->implementAction(action);
        }
        else{
            this->currentToken = this->nextToken();
        }
    }
    return this->leftSubstring.top();

}
