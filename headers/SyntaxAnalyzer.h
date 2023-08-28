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
#include "LexicalAnalyzer.h"
#include <stack>
#include <queue>
#include <sstream>
#include "Node.h"
#include <exception>
#include <algorithm>
using namespace std;
class SyntaxAnalyzer {

private:
    unordered_set<string> terminalList = {"lbrace", "rparen", "rbrace", "return", "vtype", "id", "if", "num", "addsub",
                                          "comp", "character", "multdiv", "boolstr", "or", "else", "and", "while",
                                          "comma", "lparen", "string", "semi", "assign"};
//    unordered_set<string> nonTerminalList =

    LexicalAnalyzer lexicalAnalyzer;
    Node *syntaxTree;
    stack<int> stateStack;
    stack<Node *> leftSubstring;
    Token *currentToken;

    vector<string> LHSList = {"S", "CODE", "CODE", "CODE", "VDECL", "VDECL", "ASSIGN", "RHS", "RHS", "RHS", "RHS", "EXPR", "EXPR", "EXPR", "TERM", "TERM", "FACT", "FACT", "FACT", "FDECL", "ARG", "ARG", "MOREARGS", "MOREARGS", "BLOCK", "BLOCK", "STMT", "STMT", "STMT", "STMT", "STMT", "CALL", "ARGVAL", "ARGVAL", "MOREARGVAL", "MOREARGVAL", "COND", "COND_EXPR", "COND_EXPR", "LOGIC_EXPR", "LOGIC_EXPR", "LOGIC_OP", "LOGIC_OP", "ELSE", "ELSE", "RETURN"};

    vector<vector<string>> RHSList = {
            {"CODE"},
            {"VDECL", "CODE"},
            {"FDECL", "CODE"},
            {},
            {"vtype", "id", "semi"},
            {"vtype", "ASSIGN", "semi"},
            {"id", "assign", "RHS"},
            {"EXPR"},
            {"char"},
            {"string"},
            {"boolstr"},
            {"CALL"},
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
            {"LOGIC_OP", "COND"},
            {"and"},
            {"or"},
            {"else", "lbrace", "BLOCK", "rbrace"},
            {},
            {"return", "RHS", "semi"}
    };



    std::vector<std::unordered_map<string, string>> SLRTable = {
            {{"vtype", "s4"},  {"$", "r3"},  {"CODE", "1"},  {"VDECL", "2"},  {"FDECL", "3"}},
            {{"$", "acc"}},
            {{"vtype", "s4"},  {"$", "r3"},  {"CODE", "5"},  {"VDECL", "2"},  {"FDECL", "3"}},
            {{"vtype", "s4"},  {"$", "r3"},  {"CODE", "6"},  {"VDECL", "2"},  {"FDECL", "3"}},
            {{"id", "s7"},  {"ASSIGN", "8"}},
            {{"$", "r1"}},
            {{"$", "r2"}},
            {{"semi", "s9"},  {"assign", "s11"},  {"lparen", "s10"}},
            {{"semi", "s12"}},
            {{"vtype", "r4"},  {"id", "r4"},  {"rbrace", "r4"},  {"if", "r4"},  {"while", "r4"},  {"return", "r4"},  {"$", "r4"}},
            {{"vtype", "s14"},  {"rparen", "r21"},  {"ARG", "13"}},
            {{"id", "s22"},  {"char", "s17"},  {"string", "s18"},  {"boolstr", "s19"},  {"num", "s24"},  {"lparen", "s25"},  {"RHS", "15"},  {"EXPR", "16"},  {"TERM", "21"},  {"FACT", "23"},  {"CALL", "20"}},
            {{"vtype", "r5"},  {"id", "r5"},  {"rbrace", "r5"},  {"if", "r5"},  {"while", "r5"},  {"return", "r5"},  {"$", "r5"}},
            {{"rparen", "s26"}},
            {{"id", "s27"}},
            {{"semi", "r6"}},
            {{"semi", "r7"}},
            {{"semi", "r8"}},
            {{"semi", "r9"}},
            {{"semi", "r10"}},
            {{"semi", "r11"},  {"rparen", "r11"},  {"comma", "r11"}},
            {{"semi", "r13"},  {"addsub", "s28"},  {"rparen", "r13"},  {"comma", "r13"}},
            {{"semi", "r18"},  {"addsub", "r18"},  {"multdiv", "r18"},  {"lparen", "s29"},  {"rparen", "r18"},  {"comma", "r18"},  {"comp", "r18"},  {"and", "r18"},  {"or", "r18"}},
            {{"semi", "r15"},  {"addsub", "r15"},  {"multdiv", "s30"},  {"rparen", "r15"},  {"comma", "r15"}},
            {{"semi", "r16"},  {"addsub", "r16"},  {"multdiv", "r16"},  {"rparen", "r16"},  {"comma", "r16"},  {"comp", "r16"},  {"and", "r16"},  {"or", "r16"}},
            {{"id", "s22"},  {"num", "s24"},  {"lparen", "s25"},  {"EXPR", "31"},  {"TERM", "21"},  {"FACT", "23"},  {"CALL", "20"}},
            {{"lbrace", "s32"}},
            {{"rparen", "r23"},  {"comma", "s34"},  {"MOREARGS", "33"}},
            {{"id", "s22"},  {"num", "s24"},  {"lparen", "s25"},  {"EXPR", "35"},  {"TERM", "21"},  {"FACT", "23"},  {"CALL", "20"}},
            {{"id", "s22"},  {"num", "s24"},  {"lparen", "s25"},  {"rparen", "r33"},  {"EXPR", "37"},  {"TERM", "21"},  {"FACT", "23"},  {"CALL", "20"},  {"ARGVAL", "36"}},
            {{"id", "s39"},  {"num", "s24"},  {"lparen", "s25"},  {"TERM", "38"},  {"FACT", "23"}},
            {{"rparen", "s40"}},
            {{"vtype", "s48"},  {"id", "s49"},  {"rbrace", "r25"},  {"if", "s46"},  {"while", "s47"},  {"return", "r25"},  {"VDECL", "43"},  {"ASSIGN", "44"},  {"BLOCK", "41"},  {"STMT", "42"},  {"CALL", "45"}},
            {{"rparen", "r20"}},
            {{"vtype", "s50"}},
            {{"semi", "r12"},  {"rparen", "r12"},  {"comma", "r12"}},
            {{"rparen", "s51"}},
            {{"rparen", "r35"},  {"comma", "s53"},  {"MOREARGVAL", "52"}},
            {{"semi", "r14"},  {"addsub", "r14"},  {"rparen", "r14"},  {"comma", "r14"}},
            {{"semi", "r18"},  {"addsub", "r18"},  {"multdiv", "r18"},  {"rparen", "r18"},  {"comma", "r18"},  {"comp", "r18"},  {"and", "r18"},  {"or", "r18"}},
            {{"semi", "r17"},  {"addsub", "r17"},  {"multdiv", "r17"},  {"rparen", "r17"},  {"comma", "r17"},  {"comp", "r17"},  {"and", "r17"},  {"or", "r17"}},
            {{"return", "s55"},  {"RETURN", "54"}},
            {{"vtype", "s48"},  {"id", "s49"},  {"rbrace", "r25"},  {"if", "s46"},  {"while", "s47"},  {"return", "r25"},  {"VDECL", "43"},  {"ASSIGN", "44"},  {"BLOCK", "56"},  {"STMT", "42"},  {"CALL", "45"}},
            {{"vtype", "r26"},  {"id", "r26"},  {"rbrace", "r26"},  {"if", "r26"},  {"while", "r26"},  {"return", "r26"}},
            {{"semi", "s57"}},
            {{"semi", "s58"}},
            {{"lparen", "s59"}},
            {{"lparen", "s60"}},
            {{"id", "s61"},  {"ASSIGN", "8"}},
            {{"assign", "s11"},  {"lparen", "s29"}},
            {{"id", "s62"}},
            {{"semi", "r31"},  {"rparen", "r31"},  {"comma", "r31"}},
            {{"rparen", "r32"}},
            {{"id", "s22"},  {"num", "s24"},  {"lparen", "s25"},  {"EXPR", "63"},  {"TERM", "21"},  {"FACT", "23"},  {"CALL", "20"}},
            {{"rbrace", "s64"}},
            {{"id", "s22"},  {"char", "s17"},  {"string", "s18"},  {"boolstr", "s19"},  {"num", "s24"},  {"lparen", "s25"},  {"RHS", "65"},  {"EXPR", "16"},  {"TERM", "21"},  {"FACT", "23"},  {"CALL", "20"}},
            {{"rbrace", "r24"},  {"return", "r24"}},
            {{"vtype", "r27"},  {"id", "r27"},  {"rbrace", "r27"},  {"if", "r27"},  {"while", "r27"},  {"return", "r27"}},
            {{"vtype", "r28"},  {"id", "r28"},  {"rbrace", "r28"},  {"if", "r28"},  {"while", "r28"},  {"return", "r28"}},
            {{"id", "s39"},  {"boolstr", "s68"},  {"num", "s24"},  {"lparen", "s25"},  {"FACT", "69"},  {"COND", "66"},  {"COND_EXPR", "67"}},
            {{"id", "s39"},  {"boolstr", "s68"},  {"num", "s24"},  {"lparen", "s25"},  {"FACT", "69"},  {"COND", "70"},  {"COND_EXPR", "67"}},
            {{"semi", "s9"},  {"assign", "s11"}},
            {{"rparen", "r23"},  {"comma", "s34"},  {"MOREARGS", "71"}},
            {{"rparen", "r35"},  {"comma", "s53"},  {"MOREARGVAL", "72"}},
            {{"vtype", "r19"},  {"$", "r19"}},
            {{"semi", "s73"}},
            {{"rparen", "s74"}},
            {{"rparen", "r39"},  {"and", "s77"},  {"or", "s78"},  {"LOGIC_EXPR", "75"},  {"LOGIC_OP", "76"}},
            {{"rparen", "r37"},  {"and", "r37"},  {"or", "r37"}},
            {{"comp", "s79"}},
            {{"rparen", "s80"}},
            {{"rparen", "r22"}},
            {{"rparen", "r34"}},
            {{"rbrace", "r45"}},
            {{"lbrace", "s81"}},
            {{"rparen", "r36"}},
            {{"id", "s39"},  {"boolstr", "s68"},  {"num", "s24"},  {"lparen", "s25"},  {"FACT", "69"},  {"COND", "82"},  {"COND_EXPR", "67"}},
            {{"id", "r41"},  {"boolstr", "r41"},  {"num", "r41"},  {"lparen", "r41"}},
            {{"id", "r42"},  {"boolstr", "r42"},  {"num", "r42"},  {"lparen", "r42"}},
            {{"id", "s39"},  {"num", "s24"},  {"lparen", "s25"},  {"FACT", "83"}},
            {{"lbrace", "s84"}},
            {{"vtype", "s48"},  {"id", "s49"},  {"rbrace", "r25"},  {"if", "s46"},  {"while", "s47"},  {"return", "r25"},  {"VDECL", "43"},  {"ASSIGN", "44"},  {"BLOCK", "85"},  {"STMT", "42"},  {"CALL", "45"}},
            {{"rparen", "r40"}},
            {{"rparen", "r38"},  {"and", "r38"},  {"or", "r38"}},
            {{"vtype", "s48"},  {"id", "s49"},  {"rbrace", "r25"},  {"if", "s46"},  {"while", "s47"},  {"return", "r25"},  {"VDECL", "43"},  {"ASSIGN", "44"},  {"BLOCK", "86"},  {"STMT", "42"},  {"CALL", "45"}},
            {{"rbrace", "s87"}},
            {{"rbrace", "s88"}},
            {{"vtype", "r44"},  {"id", "r44"},  {"rbrace", "r44"},  {"if", "r44"},  {"while", "r44"},  {"else", "s90"},  {"return", "r44"},  {"ELSE", "89"}},
            {{"vtype", "r30"},  {"id", "r30"},  {"rbrace", "r30"},  {"if", "r30"},  {"while", "r30"},  {"return", "r30"}},
            {{"vtype", "r29"},  {"id", "r29"},  {"rbrace", "r29"},  {"if", "r29"},  {"while", "r29"},  {"return", "r29"}},
            {{"lbrace", "s91"}},
            {{"vtype", "s48"},  {"id", "s49"},  {"rbrace", "r25"},  {"if", "s46"},  {"while", "s47"},  {"return", "r25"},  {"VDECL", "43"},  {"ASSIGN", "44"},  {"BLOCK", "92"},  {"STMT", "42"},  {"CALL", "45"}},
            {{"rbrace", "s93"}},
            {{"vtype", "r43"},  {"id", "r43"},  {"rbrace", "r43"},  {"if", "r43"},  {"while", "r43"},  {"return", "r43"}}
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
