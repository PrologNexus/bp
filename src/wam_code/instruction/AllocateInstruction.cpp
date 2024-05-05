#include "AllocateInstruction.hpp"

AllocateInstruction::AllocateInstruction(size_t n)
    : m_N(n)
{
}

std::shared_ptr<Instruction> AllocateInstruction::clone(void)
{
    return std::make_shared<AllocateInstruction>(m_N);
}

void AllocateInstruction::execute(WAMState &state)
{
    std::shared_ptr<ChoicePoint> cp = state.stackTop();
    // Allocate new environment to current choice point (Initialize all variables).
    cp->m_Variables.resize(m_N, nullptr);
    for (size_t i = 0; i < m_N; i++)
    {
        if (state.m_QueryVariables.count(i))
        {
            cp->m_Variables[i] = std::make_shared<VariableWord>(&cp->m_Variables[i], state.m_QueryVariables[i]);
        }
        else
        {
            cp->m_Variables[i] = std::make_shared<VariableWord>(&cp->m_Variables[i]);
        }
    }
    // Set E to this choice point
    state.m_EnvironmentRegister = state.BReg();
}

void AllocateInstruction::print(std::ostream &os) const
{
    os << "allocate " << m_N;
}