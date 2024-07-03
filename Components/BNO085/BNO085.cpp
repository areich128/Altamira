// ======================================================================
// \title  BNO085.cpp
// \author zhasieshmoist
// \brief  cpp file for BNO085 component implementation class
// ======================================================================

#include "BNO085/BNO085.hpp"
#include "FpConfig.hpp"

namespace BNO085Module {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  BNO085 ::
    BNO085(const char* const compName) :
      BNO085ComponentBase(compName)
  {

  }

  BNO085 ::
    ~BNO085()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void BNO085 ::
    TODO_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
