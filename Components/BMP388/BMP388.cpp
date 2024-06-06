// ======================================================================
// \title  BMP388.cpp
// \author zhasieshmoist
// \brief  cpp file for BMP388 component implementation class
// ======================================================================

#include "Components/BMP388/BMP388.hpp"
#include "FpConfig.hpp"

namespace BMP388Module {

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
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void BMP388 ::
    mathResultIn_handler(
        NATIVE_INT_TYPE portNum,
        F32 result
    )
  {
    // TODO
  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void BMP388 ::
    SEND_DATA_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        F32 pressure,
        F32 temp,
        F32 altitude
    )
  {
    // TODO
    this->tlmWrite_PRESSURE(pressure);
    this->tlmWrite_TEMP(temp);
    this->tlmWrite_ALTITUDE(altitude);
    this->log_ACTIVITY_LO_COMMAND_RECV(pressure, temp, altitude);
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
