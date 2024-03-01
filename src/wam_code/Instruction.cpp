#include "Instruction.hpp"

#include <iostream>

// Indexing Instructions

Instruction *MarkInstruction::clone(void)
{
    return new MarkInstruction();
}

void MarkInstruction::execute(WAMState &state)
{
    ChoicePoint *cp = state.stackTop();
    ChoicePoint *ncp;
    if (cp)
    {
        ncp = new ChoicePoint(cp->m_ArgumentRegisters, cp->m_BCP, 0, 0, 0);
    }
    else
        ncp = new ChoicePoint(state.m_ArgumentRegisters, 0, 0, 0, 0);
    state.stackPush(ncp);
    std::cout << state << std::endl;
}

void MarkInstruction::print(std::ostream &os)
{
    os << "mark";
}

RetryMeElseInstruction::RetryMeElseInstruction(const std::string &label, size_t address)
    : m_Label(label),
      m_Address(address)
{
}

Instruction *RetryMeElseInstruction::clone(void)
{
    return new RetryMeElseInstruction(m_Label, m_Address);
}

void RetryMeElseInstruction::execute(WAMState &state)
{
    ChoicePoint *cp = state.stackTop();
    if (cp)
    {
        cp->m_FA = m_Address;
    }
}

void RetryMeElseInstruction::print(std::ostream &os)
{
    os << "retry-me-else " << m_Label;
}

Instruction *BacktrackInstruction::clone(void)
{
    return new BacktrackInstruction();
}

void BacktrackInstruction::execute(WAMState &state)
{
}

void BacktrackInstruction::print(std::ostream &os)
{
    os << "backtrack";
}

Instruction *FailInstruction::clone(void)
{
    return new FailInstruction();
}

void FailInstruction::execute(WAMState &state)
{
}

void FailInstruction::print(std::ostream &os)
{
    os << "__fail__";
}

// Procedural Instructions
CallInstruction::CallInstruction(const std::string &label, size_t address)
    : m_Label(label),
      m_Address(address)
{
}

Instruction *CallInstruction::clone(void)
{
    return new CallInstruction(m_Label, m_Address);
}

void CallInstruction::execute(WAMState &state)
{
    ChoicePoint *cp = state.stackTop();
    // Program counter already points to another instruction
    cp->m_BCP = state.m_ProgramCounter;
    state.m_ProgramCounter = m_Address;
}

void CallInstruction::print(std::ostream &os)
{
    os << "call " + m_Label;
}

Instruction *ReturnInstruction::clone(void)
{
    return new ReturnInstruction();
}

void ReturnInstruction::execute(WAMState &state)
{
    ChoicePoint *cp = state.stackTop();
    if (cp)
    {
        state.stackPop();
        if (!state.stackEmpty())
            state.m_ProgramCounter = cp->m_BCP;
        delete cp;
    }
    std::cout << state << std::endl;
}

void ReturnInstruction::print(std::ostream &os)
{
    os << "return";
}

// Get Instructions

GetInstruction::GetInstruction(const std::string &name, size_t argumentRegister)
    : m_Name(name),
      m_ArgumentRegister(argumentRegister)
{
}

GetConstantInstruction::GetConstantInstruction(const std::string &name, size_t argumentRegister)
    : GetInstruction(name, argumentRegister)
{
}

Instruction *GetConstantInstruction::clone(void)
{
    return new GetConstantInstruction(m_Name, m_ArgumentRegister);
}

void GetConstantInstruction::execute(WAMState &state)
{
    ChoicePoint *cp = state.stackTop();
    Word *reg = cp->m_ArgumentRegisters.dereferenceRegister(m_ArgumentRegister);
    ConstantWord *cword = new ConstantWord(m_Name);
    if (!reg || !reg->compareToConst(cword))
    {
        // TODO: Make a singleton object maybe?
        Instruction *fail = new FailInstruction();
        fail->execute(state);
        delete fail;
    }
    delete cword;
}

void GetConstantInstruction::print(std::ostream &os)
{
    os << "get-constant " << m_Name << " A" << m_ArgumentRegister;
}

GetStructureInstruction::GetStructureInstruction(const std::string &name, size_t argumentRegister)
    : GetInstruction(name, argumentRegister)
{
}

Instruction *GetStructureInstruction::clone(void)
{
    return new GetStructureInstruction(m_Name, m_ArgumentRegister);
}

void GetStructureInstruction::execute(WAMState &state)
{
}

void GetStructureInstruction::print(std::ostream &os)
{
    os << "get-structure " << m_Name << " A" << m_ArgumentRegister;
}

GetVariableInstruction::GetVariableInstruction(const std::string &name, size_t argumentRegister)
    : GetInstruction(name, argumentRegister)
{
}

Instruction *GetVariableInstruction::clone(void)
{
    return new GetVariableInstruction(m_Name, m_ArgumentRegister);
}

void GetVariableInstruction::execute(WAMState &state)
{
}

void GetVariableInstruction::print(std::ostream &os)
{
    os << "getv " << m_Name << " A" << m_ArgumentRegister;
}

// Put Instructions

PutInstruction::PutInstruction(const std::string &name, size_t argumentRegister)
    : m_Name(name),
      m_ArgumentRegister(argumentRegister)
{
}

PutConstantInstruction::PutConstantInstruction(const std::string &name, size_t argumentRegister)
    : PutInstruction(name, argumentRegister)
{
}

Instruction *PutConstantInstruction::clone(void)
{
    return new PutConstantInstruction(m_Name, m_ArgumentRegister);
}

void PutConstantInstruction::execute(WAMState &state)
{
    ChoicePoint *cp = state.stackTop();
    cp->m_ArgumentRegisters.fillRegister(new ConstantWord(m_Name), m_ArgumentRegister);
}

void PutConstantInstruction::print(std::ostream &os)
{
    os << "put-constant " << m_Name << " A" << m_ArgumentRegister;
}

PutVariableInstruction::PutVariableInstruction(const std::string &name, size_t argumentRegister)
    : PutInstruction(name, argumentRegister)
{
}

Instruction *PutVariableInstruction::clone(void)
{
    return new PutVariableInstruction(m_Name, m_ArgumentRegister);
}

void PutVariableInstruction::execute(WAMState &state)
{
}

void PutVariableInstruction::print(std::ostream &os)
{
    os << "putv " << m_Name << " A" << m_ArgumentRegister;
}

// Unify Instructions

UnifyInstruction::UnifyInstruction(const std::string &name)
    : m_Name(name)
{
}

UnifyConstantInstruction::UnifyConstantInstruction(const std::string &name)
    : UnifyInstruction(name)
{
}

Instruction *UnifyConstantInstruction::clone(void)
{
    return new UnifyConstantInstruction(m_Name);
}

void UnifyConstantInstruction::execute(WAMState &state)
{
}

void UnifyConstantInstruction::print(std::ostream &os)
{
    os << "unify-constant " << m_Name;
}

UnifyVariableInstruction::UnifyVariableInstruction(const std::string &name)
    : UnifyInstruction(name)
{
}

Instruction *UnifyVariableInstruction::clone(void)
{
    return new UnifyVariableInstruction(m_Name);
}

void UnifyVariableInstruction::execute(WAMState &state)
{
}

void UnifyVariableInstruction::print(std::ostream &os)
{
    os << "unifyv " << m_Name;
}