//
// Created by 박영재 on 2023/08/07.
//
// rejected, end of inputString, not in the alphabet list
#include "LexicalAnalyzer.h"


LexicalAnalyzer::LexicalAnalyzer(const string& inputString){
    this->inputString = inputString;
    this->symbolTracer.line = 1;
    this->symbolTracer.offset = 0;

    if (!this->isValidInputString()){
        exit(0);
    }

    this->symbolTracer.line = 1;
    this->symbolTracer.offset = 0;
    this->currentInputStringIdx = 0;
}

bool LexicalAnalyzer::isValidInputString(){
    bool validationFlag = true;
    for (const auto& inputSymbol: this->inputString){
        this->updateSymbolTracer(inputSymbol);

        if (this->alphabetList.find(inputSymbol) == this->alphabetList.end()){
            cout << "invalid symbol '" << inputSymbol << "' line: " << this->symbolTracer.line << ", at: " << this->symbolTracer.offset << endl;

            validationFlag = false;
        }
    }
    return validationFlag;
}

bool LexicalAnalyzer::isKeyword(const string& tokenValue){
    if (this->keywordList.find(tokenValue) != this->keywordList.end()){
        return true;
    }
    return false;
}
bool LexicalAnalyzer::isBool(const string& tokenValue){
    if (this->boolList.find(tokenValue) != this->boolList.end()){
        return true;
    }
    return false;
}

bool LexicalAnalyzer::isVtype(const string& tokenValue){
    if (this->vtypeList.find(tokenValue) != this->boolList.end()){
        return true;
    }
    return false;
}

int LexicalAnalyzer::getNextState(int currentState, char inputSymbol){
    return this->transitions.at(currentState)[inputSymbol];
}

Token* LexicalAnalyzer::createToken(stack<char> symbolStack, int currentState){
    auto* token = new Token();
    if (this->finalStateMap.find(currentState) == this->finalStateMap.end()){
        string currentSymbols = getTokenValue(symbolStack);
        char nextSymbol = this->inputString[this->currentInputStringIdx];


        if (currentSymbols.at(0) == '\''){
            if (currentSymbols.length() == 1){
                cout << "letter, digit, or blank expected";
            }
            else{
                cout << "\' expected";
            }
        }

        if (currentSymbols.at(0) == '"'){
            cout << "letter, digit, blank, or \" expected";
        }
        if (currentSymbols.at(0) == '!'){
            cout << "= expected";
        }
        cout <<" but the input symbol is '" << nextSymbol << "' (";
        cout << "line: " << this->symbolTracer.line << ", at: " << this->symbolTracer.offset << ")" <<endl;
        cout << currentSymbols << endl;
        cout << this->inputString[this->currentInputStringIdx] << endl;
        return nullptr;
    }
    token->name = this->finalStateMap[currentState];
    token->value = this->getTokenValue(symbolStack);



    if (token->name == "ID"){
        if (this->isBool(token->value)){
            token->name = "BOOL";

        }
        else if (this->isKeyword(token->value)){
            token->name = "KEYWORD";

        }
        else if (this->isVtype(token->value)){
            token->name = "VTYPE";

        }
    }
    return token;
}

string LexicalAnalyzer::getTokenValue(stack<char>& symbolStack){
    string tokenValue;

    while (! symbolStack.empty()){
        tokenValue += symbolStack.top();
        symbolStack.pop();
    }
    reverse(tokenValue.begin(), tokenValue.end());

    return tokenValue;
}

bool LexicalAnalyzer::isSubOp(char currentInputSymbol){
    if (currentInputSymbol == '-'){
        int currentInputSymbolIdx = this->currentInputStringIdx - 1;
        while(currentInputSymbolIdx > 0){
            if (!isspace(this->inputString[currentInputSymbolIdx])){

                if (isalnum(this->inputString[currentInputSymbolIdx])){
                    cout << this->inputString[currentInputSymbolIdx] << endl;
                    return true;
                }
                else{
                    return false;
                }
            }
            currentInputSymbolIdx--;
        }
    }
    return false;
}
Token* LexicalAnalyzer::getToken(){
    if (this->currentInputStringIdx >= this->inputString.length()){
        cout << "No more token exists" << endl;
        return nullptr;
    }


    stack<char> inputSymbolStack;
    int currentState = 0;
    int nextState;


    string tokenValue, tokenName;
    char currentInputSymbol;

    for (; this->currentInputStringIdx < this->inputString.length(); this->currentInputStringIdx++){
        currentInputSymbol = this->inputString[this->currentInputStringIdx];
        if (isSubOp(currentInputSymbol)){
            auto* tk = new Token();
            tk->name = "ARITHMETIC";
            tk->value = currentInputSymbol;
            this->currentInputStringIdx++;
            return tk;
        }
        this->updateSymbolTracer(currentInputSymbol);
        nextState = this->getNextState(currentState, currentInputSymbol);
        if (nextState == -1){

            if (inputSymbolStack.empty()){
                cout << "Can't start with '" << currentInputSymbol << "'";
                return nullptr;
            }

            return this->createToken(inputSymbolStack, currentState);
        }

        else{

            inputSymbolStack.push(currentInputSymbol);

            currentState = nextState;
        }
    }


    this->currentInputStringIdx++;
    return this->createToken(inputSymbolStack, currentState);
}

void LexicalAnalyzer::updateSymbolTracer(char currentInputSymbol){
    if (currentInputSymbol == '\n'){
        this->symbolTracer.line++;
        this->symbolTracer.offset = 0;
    }
    else{
        this->symbolTracer.offset++;
    }
}