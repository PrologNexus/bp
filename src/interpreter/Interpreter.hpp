#pragma once

#include "../Renderer.hpp"
#include "WAMState.hpp"
#include "../wam_code/WAMCode.hpp"
#include "../wam_code/Instruction.hpp"

#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <string>
#include <map>

using Label = std::string;
using Result = std::pair<bool, std::map<std::string, std::string>>;

class Interpreter
{
public:
    Interpreter(const WAMCode &wamCode, const Renderer &renderer = Renderer());

    bool run(void);
    WAMCode compileQuery(const std::string &query);
    Result evaluateQuery(void);

    void setQuery(const WAMCode &query);
    void clearQuery(void);

private:
    std::shared_ptr<Instruction> fetch(void);
    void execute(std::shared_ptr<Instruction> instr);

    WAMState m_State;
    WAMCode m_Program;
    Renderer m_Renderer;

    WAMCode m_CurrentQuery;

    const Label m_QueryLabel = "__query";
};