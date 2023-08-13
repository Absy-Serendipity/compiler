//
// Created by 박영재 on 2023/08/10.
//

#ifndef COMPILERPRJ_SYNTAXANALYZER_H
#define COMPILERPRJ_SYNTAXANALYZER_H

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <cctype>
#include "headers/LexicalAnalyzer.h"
#include <stack>
#include <queue>
#include <sstream>
#include "Node.h"
#include <exception>

using namespace std;
class SyntaxAnalyzer {

private:
        unordered_set<string> terminalList = {"assign", "comma", "boolstr", "semi", "num", "comp", "string", "else",
                                          "character", "lparen", "rbrace", "while", "lbrace", "if", "multdiv", "addsub",
                                          "return", "rparen", "id", "vtype"};
//    unordered_set<string> nonTerminalList = {"COND", "EXPR", "ARG", "MOREARGS", "STMT", "ASSIGN", "RHS", "COND_EXPR",
//                                             "TERM", "BLOCK", "CODE", "RETURN", "S", "FACT", "ELSE", "VDECL", "FDECL"};

    LexicalAnalyzer lexicalAnalyzer;
    Node* syntaxTree;
    stack<int> stateStack;
    stack<Node*> leftSubstring;
    Token* currentToken;

    vector<string> LHSList = {"S", "CODE", "CODE", "CODE", "VDECL", "VDECL", "ASSIGN", "RHS", "RHS", "RHS", "RHS", "EXPR", "EXPR", "TERM", "TERM", "TERM", "FACT", "FACT", "FDECL", "ARG", "ARG", "MOREARGS", "MOREARGS", "BLOCK", "BLOCK", "STMT", "STMT", "STMT", "STMT", "COND", "COND_EXPR", "COND_EXPR", "ELSE", "ELSE", "RETURN"};
    vector<vector<string>> RHSList = {{"CODE"},
                                      {"VDECL", "CODE"},
                                      {"FDECL", "CODE"},
                                      {},
                                      {"vtype", "id", "semi"},
                                      {"vtype", "ASSIGN", "semi"},
                                      {"id", "assign", "RHS"},
                                      {"EXPR"},
                                      {"character"},
                                      {"string"},
                                      {"boolstr"},
                                      {"TERM", "addsub", "EXPR"},
                                      {"TERM"},
                                      {"FACT", "multdiv", "TERM"},
                                      {"FACT"},
                                      {"num"},
                                      {"lparen", "EXPR", "rparen"},
                                      {"id"},
                                      {"vtype", "id", "lparen", "ARG", "rparen", "lbrace", "BLOCK", "RETURN", "rbrace"},
                                      {"vtype", "id", "MOREARGS"},
                                      {},
                                      {"comma", "vtype", "id", "MOREARGS"},
                                      {},
                                      {"STMT", "BLOCK"},
                                      {},
                                      {"VDECL"},
                                      {"ASSIGN", "semi"},
                                      {"if", "lparen", "COND", "rparen", "lbrace", "BLOCK", "rbrace", "ELSE"},
                                      {"while", "lparen", "COND", "rparen", "lbrace", "BLOCK", "rbrace"},
                                      {"boolstr", "COND_EXPR"},
                                      {"comp", "COND"},
                                      {},
                                      {"else", "lbrace", "BLOCK", "rbrace"},
                                      {},
                                      {"return", "RHS", "semi"}};



    std::vector<std::unordered_map<string, string>> SLRTable = {
            {{"vtype", "s4"}, {"$", "r3"}, {"CODE", "1"}, {"VDECL", "2"}, {"FDECL", "3"}},
            {{"$", "a"}},
            {{"vtype", "s4"}, {"$", "r3"}, {"CODE", "5"}, {"VDECL", "2"}, {"FDECL", "3"}},
            {{"vtype", "s4"}, {"$", "r3"}, {"CODE", "6"}, {"VDECL", "2"}, {"FDECL", "3"}},
            {{"id", "s7"}, {"ASSIGN", "8"}},
            {{"$", "r1"}},
            {{"$", "r2"}},
            {{"semi", "s9"}, {"assign", "s11"}, {"lparen", "s10"}},
            {{"semi", "s12"}},
            {{"vtype", "r4"}, {"id", "r4"}, {"rbrace", "r4"}, {"if", "r4"}, {"while", "r4"}, {"return", "r4"}, {"$", "r4"}},
            {{"vtype", "s14"}, {"rparen", "r20"}, {"ARG", "13"}},
            {{"id", "s24"}, {"character", "s17"}, {"string", "s18"}, {"boolstr", "s19"}, {"num", "s22"}, {"lparen", "s23"}, {"RHS", "15"}, {"EXPR", "16"}, {"TERM", "20"}, {"FACT", "21"}},
            {{"vtype", "r5"}, {"id", "r5"}, {"rbrace", "r5"}, {"if", "r5"}, {"while", "r5"}, {"return", "r5"}, {"$", "r5"}},
            {{"rparen", "s25"}},
            {{"id", "s26"}},
            {{"semi", "r6"}},
            {{"semi", "r7"}},
            {{"semi", "r8"}},
            {{"semi", "r9"}},
            {{"semi", "r10"}},
            {{"semi", "r12"}, {"addsub", "s27"}, {"rparen", "r12"}},
            {{"semi", "r14"}, {"addsub", "r14"}, {"multdiv", "s28"}, {"rparen", "r14"}},
            {{"semi", "r15"}, {"addsub", "r15"}, {"multdiv", "r15"}, {"rparen", "r15"}},
            {{"id", "s24"}, {"num", "s22"}, {"lparen", "s23"}, {"EXPR", "29"}, {"TERM", "20"}, {"FACT", "21"}},
            {{"semi", "r17"}, {"addsub", "r17"}, {"multdiv", "r17"}, {"rparen", "r17"}},
            {{"lbrace", "s30"}},
            {{"rparen", "r22"}, {"comma", "s32"}, {"MOREARGS", "31"}},
            {{"id", "s24"}, {"num", "s22"}, {"lparen", "s23"}, {"EXPR", "33"}, {"TERM", "20"}, {"FACT", "21"}},
            {{"id", "s24"}, {"num", "s22"}, {"lparen", "s23"}, {"TERM", "34"}, {"FACT", "21"}},
            {{"rparen", "s35"}},
            {{"vtype", "s42"}, {"id", "s43"}, {"rbrace", "r24"}, {"if", "s40"}, {"while", "s41"}, {"return", "r24"}, {"VDECL", "38"}, {"ASSIGN", "39"}, {"BLOCK", "36"}, {"STMT", "37"}},
            {{"rparen", "r19"}},
            {{"vtype", "s44"}},
            {{"semi", "r11"}, {"rparen", "r11"}},
            {{"semi", "r13"}, {"addsub", "r13"}, {"rparen", "r13"}},
            {{"semi", "r16"}, {"addsub", "r16"}, {"multdiv", "r16"}, {"rparen", "r16"}},
            {{"return", "s46"}, {"RETURN", "45"}},
            {{"vtype", "s42"}, {"id", "s43"}, {"rbrace", "r24"}, {"if", "s40"}, {"while", "s41"}, {"return", "r24"}, {"VDECL", "38"}, {"ASSIGN", "39"}, {"BLOCK", "47"}, {"STMT", "37"}},
            {{"vtype", "r25"}, {"id", "r25"}, {"rbrace", "r25"}, {"if", "r25"}, {"while", "r25"}, {"return", "r25"}},
            {{"semi", "s48"}},
            {{"lparen", "s49"}},
            {{"lparen", "s50"}},
            {{"id", "s51"}, {"ASSIGN", "8"}},
            {{"assign", "s11"}},
            {{"id", "s52"}},
            {{"rbrace", "s53"}},
            {{"id", "s24"}, {"character", "s17"}, {"string", "s18"}, {"boolstr", "s19"}, {"num", "s22"}, {"lparen", "s23"}, {"RHS", "54"}, {"EXPR", "16"}, {"TERM", "20"}, {"FACT", "21"}},
            {{"rbrace", "r23"}, {"return", "r23"}},
            {{"vtype", "r26"}, {"id", "r26"}, {"rbrace", "r26"}, {"if", "r26"}, {"while", "r26"}, {"return", "r26"}},
            {{"boolstr", "s56"}, {"COND", "55"}},
            {{"boolstr", "s56"}, {"COND", "57"}},
            {{"semi", "s9"}, {"assign", "s11"}},
            {{"rparen", "r22"}, {"comma", "s32"}, {"MOREARGS", "58"}},
            {{"vtype", "r18"}, {"$", "r18"}},
            {{"semi", "s59"}},
            {{"rparen", "s60"}},
            {{"rparen", "r31"}, {"comp", "s62"}, {"COND_EXPR", "61"}},
            {{"rparen", "s63"}},
            {{"rparen", "r21"}},
            {{"rbrace", "r34"}},
            {{"lbrace", "s64"}},
            {{"rparen", "r29"}},
            {{"boolstr", "s56"}, {"COND", "65"}},
            {{"lbrace", "s66"}},
            {{"vtype", "s42"}, {"id", "s43"}, {"rbrace", "r24"}, {"if", "s40"}, {"while", "s41"}, {"return", "r24"}, {"VDECL", "38"}, {"ASSIGN", "39"}, {"BLOCK", "67"}, {"STMT", "37"}},
            {{"rparen", "r30"}},
            {{"vtype", "s42"}, {"id", "s43"}, {"rbrace", "r24"}, {"if", "s40"}, {"while", "s41"}, {"return", "r24"}, {"VDECL", "38"}, {"ASSIGN", "39"}, {"BLOCK", "68"}, {"STMT", "37"}},
            {{"rbrace", "s69"}},
            {{"rbrace", "s70"}},
            {{"vtype", "r33"}, {"id", "r33"}, {"rbrace", "r33"}, {"if", "r33"}, {"while", "r33"}, {"else", "s72"}, {"return", "r33"}, {"ELSE", "71"}},
            {{"vtype", "r28"}, {"id", "r28"}, {"rbrace", "r28"}, {"if", "r28"}, {"while", "r28"}, {"return", "r28"}},
            {{"vtype", "r27"}, {"id", "r27"}, {"rbrace", "r27"}, {"if", "r27"}, {"while", "r27"}, {"return", "r27"}},
            {{"lbrace", "s73"}},
            {{"vtype", "s42"}, {"id", "s43"}, {"rbrace", "r24"}, {"if", "s40"}, {"while", "s41"}, {"return", "r24"}, {"VDECL", "38"}, {"ASSIGN", "39"}, {"BLOCK", "74"}, {"STMT", "37"}},
            {{"rbrace", "s75"}},
            {{"vtype", "r32"}, {"id", "r32"}, {"rbrace", "r32"}, {"if", "r32"}, {"while", "r32"}, {"return", "r32"}}
    };

    string getAction(int currentState, const string& inputToken);
    bool implementAction(const string& action);
    void goTo(int stateNumber);
    void shift(int stateNumber);
    void reduce(int ruleNumber);
    Token* nextToken();
    vector<string> getRHS(int ruleNumber);
    string getLHS(int ruleNumber);
    string getExpectedToken(int currentState, const string& inputToken);
public:


    SyntaxAnalyzer(const LexicalAnalyzer& lexicalAnalyzer);
    Node* analyze();


    class SyntaxErrorException : public exception {
    private:
        std::string message;

    public:
        SyntaxErrorException(const std::string& msg) : message(msg) {}

        const char* what() const noexcept override {
            return message.c_str();
        }
    };
};


#endif //COMPILERPRJ_SYNTAXANALYZER_H
