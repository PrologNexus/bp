#include "GetConstantInstruction.hpp"

GetConstantInstruction::GetConstantInstruction(const std::string &name, size_t argumentRegister)
    : m_Name(name),
      m_ArgumentRegister(argumentRegister)
{
}

std::shared_ptr<Instruction> GetConstantInstruction::clone(void)
{
    return std::make_shared<GetConstantInstruction>(m_Name, m_ArgumentRegister);
}

void GetConstantInstruction::execute(WAMState &state)
{
    std::shared_ptr<Word> reg = state.m_ArgumentRegisters.dereferenceRegister(m_ArgumentRegister);
    std::shared_ptr<ConstantWord> cword = std::make_shared<ConstantWord>(m_Name);
    if (reg && reg->tag() == TAG::VARIABLE)
    {
        std::shared_ptr<VariableWord> vw = std::static_pointer_cast<VariableWord>(reg);
        state.trailPush(vw); // Trail
        vw->bind(cword);
    }
    else if (!reg || !reg->compareToConst(cword))
    {
        fail(state);
    }
}

void GetConstantInstruction::print(std::ostream &os) const
{
    os << "get-constant " << m_Name << " A" << m_ArgumentRegister;
}