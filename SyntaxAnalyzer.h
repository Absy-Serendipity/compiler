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
        unordered_set<string> terminalList = {"lbrace", "rparen", "rbrace", "return", "vtype", "id", "if", "num", "addsub", "comp", "character", "multdiv", "boolstr", "or", "else", "and", "while", "comma", "lparen", "string", "semi", "assign"};
//    unordered_set<string> nonTerminalList =

    LexicalAnalyzer lexicalAnalyzer;
    Node* syntaxTree;
    stack<int> stateStack;
    stack<Node*> leftSubstring;
    Token* currentToken;

    vector<string> LHSList = {"S", "CODE", "CODE", "CODE", "VDECL", "VDECL", "ASSIGN", "RHS", "RHS", "RHS", "RHS", "EXPR", "EXPR", "TERM", "TERM", "FACT", "FACT", "FACT", "FDECL", "ARG", "ARG", "MOREARGS", "MOREARGS", "BLOCK", "BLOCK", "STMT", "STMT", "STMT", "STMT", "STMT", "CALL", "ARGVAL", "ARGVAL", "MOREARGVAL", "MOREARGVAL", "COND", "COND_EXPR", "COND_EXPR", "LOGIC_EXPR", "LOGIC_EXPR", "LOGIC_OP", "LOGIC_OP", "ELSE", "ELSE", "RETURN"};

    vector<vector<string>> RHSList = {
        {"CODE"},
        {"STMT", "CODE"},
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
        {"CALL", "semi"},
        {"if", "lparen", "COND", "rparen", "lbrace", "BLOCK", "rbrace", "ELSE"},
        {"while", "lparen", "COND", "rparen", "lbrace", "BLOCK", "rbrace"},
        {"id", "lparen", "ARGVAL", "rparen"},
        {"EXPR", "MOREARGVAL"},
        {},
        {"comma", "EXPR", "MOREARGVAL"},
        {},
        {"COND_EXPR", "LOGIC_EXPR"},
        {"boolstr"},
        {"FACT", "comp", "FACT"},
        {},
        {"LOGIC_OP", "COND_EXPR"},
        {"and"},
        {"or"},
        {"else", "lbrace", "BLOCK", "rbrace"},
        {},
        {"return", "RHS", "semi"}
    };



    std::vector<std::unordered_map<string, string>> SLRTable = {
        {{"vtype", "s9"}, { "id", "s10"}, { "if", "s7"}, { "while", "s8"}, { "$", "r3"}, { "CODE", "1"}, { "VDECL", "4"}, { "ASSIGN", "5"}, { "FDECL", "3"}, { "STMT", "2"}, { "CALL", "6"}},
        {{"$", "acc"}},
        {{"vtype", "s9"}, { "id", "s10"}, { "if", "s7"}, { "while", "s8"}, { "$", "r3"}, { "CODE", "11"}, { "VDECL", "4"}, { "ASSIGN", "5"}, { "FDECL", "3"}, { "STMT", "2"}, { "CALL", "6"}},
        {{"vtype", "s9"}, { "id", "s10"}, { "if", "s7"}, { "while", "s8"}, { "$", "r3"}, { "CODE", "12"}, { "VDECL", "4"}, { "ASSIGN", "5"}, { "FDECL", "3"}, { "STMT", "2"}, { "CALL", "6"}},
        {{"vtype", "r25"}, { "id", "r25"}, { "rbrace", "r25"}, { "if", "r25"}, { "while", "r25"}, { "return", "r25"}, { "$", "r25"}},
        {{"semi", "s13"}},
        {{"semi", "s14"}},
        {{"lparen", "s15"}},
        {{"lparen", "s16"}},
        {{"id", "s17"}, { "ASSIGN", "18"}},
        {{"assign", "s19"}, { "lparen", "s20"}},
        {{"$", "r1"}},
        {{"$", "r2"}},
        {{"vtype", "r26"}, { "id", "r26"}, { "rbrace", "r26"}, { "if", "r26"}, { "while", "r26"}, { "return", "r26"}, { "$", "r26"}},
        {{"vtype", "r27"}, { "id", "r27"}, { "rbrace", "r27"}, { "if", "r27"}, { "while", "r27"}, { "return", "r27"}, { "$", "r27"}},
        {{"id", "s27"}, { "boolstr", "s23"}, { "num", "s25"}, { "lparen", "s26"}, { "FACT", "24"}, { "COND", "21"}, { "COND_EXPR", "22"}},
        {{"id", "s27"}, { "boolstr", "s23"}, { "num", "s25"}, { "lparen", "s26"}, { "FACT", "24"}, { "COND", "28"}, { "COND_EXPR", "22"}},
        {{"semi", "s30"}, { "assign", "s19"}, { "lparen", "s29"}},
        {{"semi", "s31"}},
        {{"id", "s27"}, { "character", "s34"}, { "string", "s35"}, { "boolstr", "s36"}, { "num", "s25"}, { "lparen", "s26"}, { "RHS", "32"}, { "EXPR", "33"}, { "TERM", "37"}, { "FACT", "38"}},
        {{"id", "s27"}, { "num", "s25"}, { "lparen", "s26"}, { "rparen", "r32"}, { "EXPR", "40"}, { "TERM", "37"}, { "FACT", "38"}, { "ARGVAL", "39"}},
        {{"rparen", "s41"}},
        {{"rparen", "r38"}, { "and", "s44"}, { "or", "s45"}, { "LOGIC_EXPR", "42"}, { "LOGIC_OP", "43"}},
        {{"rparen", "r36"}, { "and", "r36"}, { "or", "r36"}},
        {{"comp", "s46"}},
        {{"semi", "r15"}, { "addsub", "r15"}, { "multdiv", "r15"}, { "rparen", "r15"}, { "comma", "r15"}, { "comp", "r15"}, { "and", "r15"}, { "or", "r15"}},
        {{"id", "s27"}, { "num", "s25"}, { "lparen", "s26"}, { "EXPR", "47"}, { "TERM", "37"}, { "FACT", "38"}},
        {{"semi", "r17"}, { "addsub", "r17"}, { "multdiv", "r17"}, { "rparen", "r17"}, { "comma", "r17"}, { "comp", "r17"}, { "and", "r17"}, { "or", "r17"}},
        {{"rparen", "s48"}},
        {{"vtype", "s50"}, { "rparen", "r20"}, { "ARG", "49"}},
        {{"vtype", "r4"}, { "id", "r4"}, { "rbrace", "r4"}, { "if", "r4"}, { "while", "r4"}, { "return", "r4"}, { "$", "r4"}},
        {{"vtype", "r5"}, { "id", "r5"}, { "rbrace", "r5"}, { "if", "r5"}, { "while", "r5"}, { "return", "r5"}, { "$", "r5"}},
        {{"semi", "r6"}},
        {{"semi", "r7"}},
        {{"semi", "r8"}},
        {{"semi", "r9"}},
        {{"semi", "r10"}},
        {{"semi", "r12"}, { "addsub", "s51"}, { "rparen", "r12"}, { "comma", "r12"}},
        {{"semi", "r14"}, { "addsub", "r14"}, { "multdiv", "s52"}, { "rparen", "r14"}, { "comma", "r14"}},
        {{"rparen", "s53"}},
        {{"rparen", "r34"}, { "comma", "s55"}, { "MOREARGVAL", "54"}},
        {{"lbrace", "s56"}},
        {{"rparen", "r35"}},
        {{"id", "s27"}, { "boolstr", "s23"}, { "num", "s25"}, { "lparen", "s26"}, { "FACT", "24"}, { "COND_EXPR", "57"}},
        {{"id", "r40"}, { "boolstr", "r40"}, { "num", "r40"}, { "lparen", "r40"}},
        {{"id", "r41"}, { "boolstr", "r41"}, { "num", "r41"}, { "lparen", "r41"}},
        {{"id", "s27"}, { "num", "s25"}, { "lparen", "s26"}, { "FACT", "58"}},
        {{"rparen", "s59"}},
        {{"lbrace", "s60"}},
        {{"rparen", "s61"}},
        {{"id", "s62"}},
        {{"id", "s27"}, { "num", "s25"}, { "lparen", "s26"}, { "EXPR", "63"}, { "TERM", "37"}, { "FACT", "38"}},
        {{"id", "s27"}, { "num", "s25"}, { "lparen", "s26"}, { "TERM", "64"}, { "FACT", "38"}},
        {{"semi", "r30"}},
        {{"rparen", "r31"}},
        {{"id", "s27"}, { "num", "s25"}, { "lparen", "s26"}, { "EXPR", "65"}, { "TERM", "37"}, { "FACT", "38"}},
        {{"vtype", "s68"}, { "id", "s10"}, { "rbrace", "r24"}, { "if", "s7"}, { "while", "s8"}, { "return", "r24"}, { "VDECL", "4"}, { "ASSIGN", "5"}, { "BLOCK", "66"}, { "STMT", "67"}, { "CALL", "6"}},
        {{"rparen", "r39"}},
        {{"rparen", "r37"}, { "and", "r37"}, { "or", "r37"}},
        {{"semi", "r16"}, { "addsub", "r16"}, { "multdiv", "r16"}, { "rparen", "r16"}, { "comma", "r16"}, { "comp", "r16"}, { "and", "r16"}, { "or", "r16"}},
        {{"vtype", "s68"}, { "id", "s10"}, { "rbrace", "r24"}, { "if", "s7"}, { "while", "s8"}, { "return", "r24"}, { "VDECL", "4"}, { "ASSIGN", "5"}, { "BLOCK", "69"}, { "STMT", "67"}, { "CALL", "6"}},
        {{"lbrace", "s70"}},
        {{"rparen", "r22"}, { "comma", "s72"}, { "MOREARGS", "71"}},
        {{"semi", "r11"}, { "rparen", "r11"}, { "comma", "r11"}},
        {{"semi", "r13"}, { "addsub", "r13"}, { "rparen", "r13"}, { "comma", "r13"}},
        {{"rparen", "r34"}, { "comma", "s55"}, { "MOREARGVAL", "73"}},
        {{"rbrace", "s74"}},
        {{"vtype", "s68"}, { "id", "s10"}, { "rbrace", "r24"}, { "if", "s7"}, { "while", "s8"}, { "return", "r24"}, { "VDECL", "4"}, { "ASSIGN", "5"}, { "BLOCK", "75"}, { "STMT", "67"}, { "CALL", "6"}},
        {{"id", "s76"}, { "ASSIGN", "18"}},
        {{"rbrace", "s77"}},
        {{"vtype", "s68"}, { "id", "s10"}, { "rbrace", "r24"}, { "if", "s7"}, { "while", "s8"}, { "return", "r24"}, { "VDECL", "4"}, { "ASSIGN", "5"}, { "BLOCK", "78"}, { "STMT", "67"}, { "CALL", "6"}},
        {{"rparen", "r19"}},
        {{"vtype", "s79"}},
        {{"rparen", "r33"}},
        {{"vtype", "r43"}, { "id", "r43"}, { "rbrace", "r43"}, { "if", "r43"}, { "while", "r43"}, { "else", "s81"}, { "return", "r43"}, { "$", "r43"}, { "ELSE", "80"}},
        {{"rbrace", "r23"}, { "return", "r23"}},
        {{"semi", "s30"}, { "assign", "s19"}},
        {{"vtype", "r29"}, { "id", "r29"}, { "rbrace", "r29"}, { "if", "r29"}, { "while", "r29"}, { "return", "r29"}, { "$", "r29"}},
        {{"return", "s83"}, { "RETURN", "82"}},
        {{"id", "s84"}},
        {{"vtype", "r28"}, { "id", "r28"}, { "rbrace", "r28"}, { "if", "r28"}, { "while", "r28"}, { "return", "r28"}, { "$", "r28"}},
        {{"lbrace", "s85"}},
        {{"rbrace", "s86"}},
        {{"id", "s27"}, { "character", "s34"}, { "string", "s35"}, { "boolstr", "s36"}, { "num", "s25"}, { "lparen", "s26"}, { "RHS", "87"}, { "EXPR", "33"}, { "TERM", "37"}, { "FACT", "38"}},
        {{"rparen", "r22"}, { "comma", "s72"}, { "MOREARGS", "88"}},
        {{"vtype", "s68"}, { "id", "s10"}, { "rbrace", "r24"}, { "if", "s7"}, { "while", "s8"}, { "return", "r24"}, { "VDECL", "4"}, { "ASSIGN", "5"}, { "BLOCK", "89"}, { "STMT", "67"}, { "CALL", "6"}},
        {{"vtype", "r18"}, { "id", "r18"}, { "if", "r18"}, { "while", "r18"}, { "$", "r18"}},
        {{"semi", "s90"}},
        {{"rparen", "r21"}},
        {{"rbrace", "s91"}},
        {{"rbrace", "r44"}},
        {{"vtype", "r42"}, { "id", "r42"}, { "rbrace", "r42"}, { "if", "r42"}, { "while", "r42"}, { "return", "r42"}, { "$", "r42"}}
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
