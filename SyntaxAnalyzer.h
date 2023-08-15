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
            { "STMT", "CODE" },
            { "FDECL", "CODE" },
            {},
            { "vtype", "id", "semi" },
            { "vtype", "ASSIGN", "semi" },
            { "id", "assign", "RHS" },
            { "EXPR" },
            { "character" },
            { "string" },
            { "boolstr" },
            { "CALL" },
            { "TERM", "addsub", "EXPR" },
            { "TERM" },
            { "FACT", "multdiv", "TERM" },
            { "FACT" },
            { "num" },
            { "lparen", "EXPR", "rparen" },
            { "id" },
            { "vtype", "id", "lparen", "ARG", "rparen", "lbrace", "BLOCK", "RETURN", "rbrace" },
            { "vtype", "id", "MOREARGS" },
            {},
            { "comma", "vtype", "id", "MOREARGS" },
            {},
            { "STMT", "BLOCK" },
            {},
            { "VDECL" },
            { "ASSIGN", "semi" },
            { "CALL", "semi" },
            { "if", "lparen", "COND", "rparen", "lbrace", "BLOCK", "rbrace", "ELSE" },
            { "while", "lparen", "COND", "rparen", "lbrace", "BLOCK", "rbrace" },
            { "id", "lparen", "ARGVAL", "rparen" },
            { "EXPR", "MOREARGVAL" },
            {},
            { "comma", "EXPR", "MOREARGVAL" },
            {},
            { "COND_EXPR", "LOGIC_EXPR" },
            { "boolstr" },
            { "FACT", "comp", "FACT" },
            {},
            { "LOGIC_OP", "COND" },
            { "and" },
            { "or" },
            { "else", "lbrace", "BLOCK", "rbrace" },
            {},
            { "return", "RHS", "semi" }
    };



    std::vector<std::unordered_map<string, string>> SLRTable = {
            {{"vtype", "s9"},  {"id", "s10"},  {"if", "s7"},  {"while", "s8"},  {"$", "r3"},  {"CODE", "1"},  {"VDECL", "4"},  {"ASSIGN", "5"},  {"FDECL", "3"},  {"STMT", "2"},  {"CALL", "6"}},
            {{"$", "acc"}},
            {{"vtype", "s9"},  {"id", "s10"},  {"if", "s7"},  {"while", "s8"},  {"$", "r3"},  {"CODE", "11"},  {"VDECL", "4"},  {"ASSIGN", "5"},  {"FDECL", "3"},  {"STMT", "2"},  {"CALL", "6"}},
            {{"vtype", "s9"},  {"id", "s10"},  {"if", "s7"},  {"while", "s8"},  {"$", "r3"},  {"CODE", "12"},  {"VDECL", "4"},  {"ASSIGN", "5"},  {"FDECL", "3"},  {"STMT", "2"},  {"CALL", "6"}},
            {{"vtype", "r26"},  {"id", "r26"},  {"rbrace", "r26"},  {"if", "r26"},  {"while", "r26"},  {"return", "r26"},  {"$", "r26"}},
            {{"semi", "s13"}},
            {{"semi", "s14"}},
            {{"lparen", "s15"}},
            {{"lparen", "s16"}},
            {{"id", "s17"},  {"ASSIGN", "18"}},
            {{"assign", "s19"},  {"lparen", "s20"}},
            {{"$", "r1"}},
            {{"$", "r2"}},
            {{"vtype", "r27"},  {"id", "r27"},  {"rbrace", "r27"},  {"if", "r27"},  {"while", "r27"},  {"return", "r27"},  {"$", "r27"}},
            {{"vtype", "r28"},  {"id", "r28"},  {"rbrace", "r28"},  {"if", "r28"},  {"while", "r28"},  {"return", "r28"},  {"$", "r28"}},
            {{"id", "s27"},  {"boolstr", "s23"},  {"num", "s25"},  {"lparen", "s26"},  {"FACT", "24"},  {"COND", "21"},  {"COND_EXPR", "22"}},
            {{"id", "s27"},  {"boolstr", "s23"},  {"num", "s25"},  {"lparen", "s26"},  {"FACT", "24"},  {"COND", "28"},  {"COND_EXPR", "22"}},
            {{"semi", "s30"},  {"assign", "s19"},  {"lparen", "s29"}},
            {{"semi", "s31"}},
            {{"id", "s39"},  {"character", "s34"},  {"string", "s35"},  {"boolstr", "s36"},  {"num", "s25"},  {"lparen", "s26"},  {"RHS", "32"},  {"EXPR", "33"},  {"TERM", "38"},  {"FACT", "40"},  {"CALL", "37"}},
            {{"id", "s39"},  {"num", "s25"},  {"lparen", "s26"},  {"rparen", "r33"},  {"EXPR", "42"},  {"TERM", "38"},  {"FACT", "40"},  {"CALL", "37"},  {"ARGVAL", "41"}},
            {{"rparen", "s43"}},
            {{"rparen", "r39"},  {"and", "s46"},  {"or", "s47"},  {"LOGIC_EXPR", "44"},  {"LOGIC_OP", "45"}},
            {{"rparen", "r37"},  {"and", "r37"},  {"or", "r37"}},
            {{"comp", "s48"}},
            {{"semi", "r16"},  {"addsub", "r16"},  {"multdiv", "r16"},  {"rparen", "r16"},  {"comma", "r16"},  {"comp", "r16"},  {"and", "r16"},  {"or", "r16"}},
            {{"id", "s39"},  {"num", "s25"},  {"lparen", "s26"},  {"EXPR", "49"},  {"TERM", "38"},  {"FACT", "40"},  {"CALL", "37"}},
            {{"semi", "r18"},  {"addsub", "r18"},  {"multdiv", "r18"},  {"rparen", "r18"},  {"comma", "r18"},  {"comp", "r18"},  {"and", "r18"},  {"or", "r18"}},
            {{"rparen", "s50"}},
            {{"vtype", "s52"},  {"rparen", "r21"},  {"ARG", "51"}},
            {{"vtype", "r4"},  {"id", "r4"},  {"rbrace", "r4"},  {"if", "r4"},  {"while", "r4"},  {"return", "r4"},  {"$", "r4"}},
            {{"vtype", "r5"},  {"id", "r5"},  {"rbrace", "r5"},  {"if", "r5"},  {"while", "r5"},  {"return", "r5"},  {"$", "r5"}},
            {{"semi", "r6"}},
            {{"semi", "r7"}},
            {{"semi", "r8"}},
            {{"semi", "r9"}},
            {{"semi", "r10"}},
            {{"semi", "r11"},  {"rparen", "r11"},  {"comma", "r11"}},
            {{"semi", "r13"},  {"addsub", "s53"},  {"rparen", "r13"},  {"comma", "r13"}},
            {{"semi", "r18"},  {"addsub", "r18"},  {"multdiv", "r18"},  {"lparen", "s20"},  {"rparen", "r18"},  {"comma", "r18"},  {"comp", "r18"},  {"and", "r18"},  {"or", "r18"}},
            {{"semi", "r15"},  {"addsub", "r15"},  {"multdiv", "s54"},  {"rparen", "r15"},  {"comma", "r15"}},
            {{"rparen", "s55"}},
            {{"rparen", "r35"},  {"comma", "s57"},  {"MOREARGVAL", "56"}},
            {{"lbrace", "s58"}},
            {{"rparen", "r36"}},
            {{"id", "s27"},  {"boolstr", "s23"},  {"num", "s25"},  {"lparen", "s26"},  {"FACT", "24"},  {"COND", "59"},  {"COND_EXPR", "22"}},
            {{"id", "r41"},  {"boolstr", "r41"},  {"num", "r41"},  {"lparen", "r41"}},
            {{"id", "r42"},  {"boolstr", "r42"},  {"num", "r42"},  {"lparen", "r42"}},
            {{"id", "s27"},  {"num", "s25"},  {"lparen", "s26"},  {"FACT", "60"}},
            {{"rparen", "s61"}},
            {{"lbrace", "s62"}},
            {{"rparen", "s63"}},
            {{"id", "s64"}},
            {{"id", "s39"},  {"num", "s25"},  {"lparen", "s26"},  {"EXPR", "65"},  {"TERM", "38"},  {"FACT", "40"},  {"CALL", "37"}},
            {{"id", "s27"},  {"num", "s25"},  {"lparen", "s26"},  {"TERM", "66"},  {"FACT", "40"}},
            {{"semi", "r31"},  {"rparen", "r31"},  {"comma", "r31"}},
            {{"rparen", "r32"}},
            {{"id", "s39"},  {"num", "s25"},  {"lparen", "s26"},  {"EXPR", "67"},  {"TERM", "38"},  {"FACT", "40"},  {"CALL", "37"}},
            {{"vtype", "s70"},  {"id", "s10"},  {"rbrace", "r25"},  {"if", "s7"},  {"while", "s8"},  {"return", "r25"},  {"VDECL", "4"},  {"ASSIGN", "5"},  {"BLOCK", "68"},  {"STMT", "69"},  {"CALL", "6"}},
            {{"rparen", "r40"}},
            {{"rparen", "r38"},  {"and", "r38"},  {"or", "r38"}},
            {{"semi", "r17"},  {"addsub", "r17"},  {"multdiv", "r17"},  {"rparen", "r17"},  {"comma", "r17"},  {"comp", "r17"},  {"and", "r17"},  {"or", "r17"}},
            {{"vtype", "s70"},  {"id", "s10"},  {"rbrace", "r25"},  {"if", "s7"},  {"while", "s8"},  {"return", "r25"},  {"VDECL", "4"},  {"ASSIGN", "5"},  {"BLOCK", "71"},  {"STMT", "69"},  {"CALL", "6"}},
            {{"lbrace", "s72"}},
            {{"rparen", "r23"},  {"comma", "s74"},  {"MOREARGS", "73"}},
            {{"semi", "r12"},  {"rparen", "r12"},  {"comma", "r12"}},
            {{"semi", "r14"},  {"addsub", "r14"},  {"rparen", "r14"},  {"comma", "r14"}},
            {{"rparen", "r35"},  {"comma", "s57"},  {"MOREARGVAL", "75"}},
            {{"rbrace", "s76"}},
            {{"vtype", "s70"},  {"id", "s10"},  {"rbrace", "r25"},  {"if", "s7"},  {"while", "s8"},  {"return", "r25"},  {"VDECL", "4"},  {"ASSIGN", "5"},  {"BLOCK", "77"},  {"STMT", "69"},  {"CALL", "6"}},
            {{"id", "s78"},  {"ASSIGN", "18"}},
            {{"rbrace", "s79"}},
            {{"vtype", "s70"},  {"id", "s10"},  {"rbrace", "r25"},  {"if", "s7"},  {"while", "s8"},  {"return", "r25"},  {"VDECL", "4"},  {"ASSIGN", "5"},  {"BLOCK", "80"},  {"STMT", "69"},  {"CALL", "6"}},
            {{"rparen", "r20"}},
            {{"vtype", "s81"}},
            {{"rparen", "r34"}},
            {{"vtype", "r44"},  {"id", "r44"},  {"rbrace", "r44"},  {"if", "r44"},  {"while", "r44"},  {"else", "s83"},  {"return", "r44"},  {"$", "r44"},  {"ELSE", "82"}},
            {{"rbrace", "r24"},  {"return", "r24"}},
            {{"semi", "s30"},  {"assign", "s19"}},
            {{"vtype", "r30"},  {"id", "r30"},  {"rbrace", "r30"},  {"if", "r30"},  {"while", "r30"},  {"return", "r30"},  {"$", "r30"}},
            {{"return", "s85"},  {"RETURN", "84"}},
            {{"id", "s86"}},
            {{"vtype", "r29"},  {"id", "r29"},  {"rbrace", "r29"},  {"if", "r29"},  {"while", "r29"},  {"return", "r29"},  {"$", "r29"}},
            {{"lbrace", "s87"}},
            {{"rbrace", "s88"}},
            {{"id", "s39"},  {"character", "s34"},  {"string", "s35"},  {"boolstr", "s36"},  {"num", "s25"},  {"lparen", "s26"},  {"RHS", "89"},  {"EXPR", "33"},  {"TERM", "38"},  {"FACT", "40"},  {"CALL", "37"}},
            {{"rparen", "r23"},  {"comma", "s74"},  {"MOREARGS", "90"}},
            {{"vtype", "s70"},  {"id", "s10"},  {"rbrace", "r25"},  {"if", "s7"},  {"while", "s8"},  {"return", "r25"},  {"VDECL", "4"},  {"ASSIGN", "5"},  {"BLOCK", "91"},  {"STMT", "69"},  {"CALL", "6"}},
            {{"vtype", "r19"},  {"id", "r19"},  {"if", "r19"},  {"while", "r19"},  {"$", "r19"}},
            {{"semi", "s92"}},
            {{"rparen", "r22"}},
            {{"rbrace", "s93"}},
            {{"rbrace", "r45"}},
            {{"vtype", "r43"},  {"id", "r43"},  {"rbrace", "r43"},  {"if", "r43"},  {"while", "r43"},  {"return", "r43"},  {"$", "r43"}},
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
