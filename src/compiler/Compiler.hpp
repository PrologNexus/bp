#ifndef COMPILER_H
#define COMPILER_H

#include <iostream>
#include <string>

#include "lexer/Lexer.hpp"
#include "parser/Parser.hpp"
#include "CompilationContext.hpp"
#include "../wam_code/WAMCode.hpp"

class Compiler
{
public:
    Compiler(std::istream &is);

    void compile(void);
    void dump(std::ostream &os);

private:
    CompilationContext m_CCtx;
    Parser m_Parser = Parser(Lexer(std::cin));
    std::string m_Code = "";
};

#endif