#pragma once

#include <set>
#include <string>
#include <memory>
#include <unordered_map>

#include "../wam_code/instruction/Instructions.hpp"

#include "../wam_code/WAMCode.hpp"

using Label = std::string;

struct TableEntry
{
    TableEntry(const std::string &name)
        : m_Name(name)
    {
    }

    std::string m_Name;

    std::shared_ptr<Mark> m_InitialMark = nullptr;
    std::shared_ptr<RetryMeElse> m_LastRetryMeElse = nullptr;
    std::vector<std::shared_ptr<Call>> m_CallReferences;

    size_t m_Generated = 0;
    size_t m_Clauses = 1;
};

enum CodeGenerationMode
{
    HEAD,
    BODY
};

class CompilationContext
{
public:
    void add(const std::string &symbol,
             std::shared_ptr<TableEntry> entry);
    std::shared_ptr<TableEntry> get(const std::string &symbol);

    void addInstruction(std::shared_ptr<Instruction> instr);
    void addInstructions(const std::vector<std::shared_ptr<Instruction>> &instructions);

    void addLabel(const Label &label);
    size_t getLabelAddress(const Label &label);

    WAMCode code(void);
    WAMCode &getCode(void);

    std::string generateTempVar(void);
    size_t allocate(void);
    void addVariable(const std::string &variable);
    void noteVariable(const std::string &variable);
    size_t getVarOffset(const std::string &variable);
    void resetVariables(void);

    size_t availableReg(void);
    void setAvailableReg(size_t reg);

    std::string getAvailableArithmeticVariable(void);
    void resetAvailableArithmeticVariable(void);
    void incrementAvailableArithmeticVariable(void);
    
    CodeGenerationMode mode(void);
    void setHeadGenerationMode(void);
    void setBodyGenerationMode(void);

private:
    size_t m_AvailableArithmeticVariable = 0;
    size_t m_AvailableRegister = 1;
    std::unordered_map<std::string, std::shared_ptr<TableEntry>> m_SymbolTable;
    WAMCode m_GeneratedCode;

    // Used in Clause-Level compilation
    std::map<std::string, size_t> m_Variables;

    CodeGenerationMode m_CGMode = HEAD;
};