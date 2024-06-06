// ======================================================================
// \title  BMP388.cpp
// \author zhasieshmoist
// \brief  cpp file for BMP388 component implementation class
// ======================================================================

#include "Components/BMP388/BMP388.hpp"
#include "FpConfig.hpp"

namespace BMP388 {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  BMP388 ::
    BMP388(const char* const compName) :
      BMP388ComponentBase(compName)
  {

  }

  BMP388 ::
    ~BMP388()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void BMP388 ::
    TODO_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
