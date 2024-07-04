// ======================================================================
// \title  BNO085.cpp
// \author zhasieshmoist
// \brief  cpp file for BNO085 component implementation class
// ======================================================================

#include "Components/BNO085/BNO085.hpp"
#include "FpConfig.hpp"

#include "Fw/Types/BasicTypes.hpp"
#include <Fw/Logger/Logger.hpp>

namespace BNO085Module {

  //SHTP Packet Creation function
  Fw::Buffer BNO085::createSHTP(){
    Fw::Buffer packet = this->allocate_out(0, sizeof(U8));
    
  }

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
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void BNO085 ::
    SchedIn_handler(
        NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    // TODO
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

  void BNO085 ::
    startup_BNO085_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    // TODO

    //WHOAMI check, error code checking, and calibration?

    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
