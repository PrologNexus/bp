#pragma once

#include "../lexer/Lexer.hpp"
#include "../ast/ListNode.hpp"
#include "../ast/StructNode.hpp"
#include "../ast/ProgramNode.hpp"

class Parser
{
public:
    Parser(Lexer lex)
        : m_Lex(lex)
    {
    }

    bool parse(void);

    std::shared_ptr<ProgramNode> getAST(void);

    void printAST(void);

private:
    //--------RECURSIVE DESCENT METHODS--------//
    void Start(void);
    void Next(void);
    std::shared_ptr<ClauseNode> Predicates(void);
    std::shared_ptr<ClauseNode> Pred(const std::string &head);
    std::vector<GoalNode *> Predicate(void);
    std::vector<GoalNode *> Body(void);
    StructNode *BodyLower(void);
    std::vector<GoalNode *> BodyCont(void);
    TermNode *BodyTerm(void);
    TermNode *Term(void);
    ListNode *ListInner(void);
    TermNode *ListCons(void);
    std::vector<TermNode *> Terms(void);
    std::vector<TermNode *> TermsCont(void);
    TermNode *TermLower(void);
    //-------------CLASS VARIABLES-------------//
    Lexer m_Lex;
    std::shared_ptr<ProgramNode> m_ASTRoot;
};