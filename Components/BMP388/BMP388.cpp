// ======================================================================
// \title  BMP388.cpp
// \author zhasieshmoist
// \brief  cpp file for BMP388 component implementation class
// ======================================================================

#include "Components/BMP388/BMP388.hpp"
#include "FpConfig.hpp"
#include "Fw/Types/BasicTypes.hpp"
#include <Fw/Logger/Logger.hpp>

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
    SchedIn_handler(
        NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    // TODO
    // THIS IS WHERE ALL THE ACTUAL IMPLEMENTATION CODE GOES (according to the SRL repo)


    // AFTER ALL THE CALIBRATION CODE ETC. WE DO
    // tlmWrite_ALTITUDE(altitude);
    // tlmWrite_PRESSURE(pressure);
    // tlmWrite_TEMP(temp);
  }

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
    startup_BMP388_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    // TODO

    // ACCORDING TO SRL REPO, STARTUP/INITIALIZATION CODE GOES HERE

    /*
    NOTES:
      - when WRITING data in I2C, your first bit should be the register address, followed by the rest of the data
      - when READING data in I2C, your input buffer should just be the address, and the output will be the data read
      **to my understanding**
    */
    
    // initializing read/write buffers
    Fw::Buffer dataGet = this->allocate_out(0, sizeof(U8));
    Fw::Buffer dataSend = this->allocate_out(0, sizeof(U8));

    // checking that memory has been properly allocated, else sending error
    if (dataGet.getSize() < sizeof(U8))
    {
      log_WARNING_LO_MemoryAllocationFailed();
      return;
    }

    if (dataSend.getSize() < sizeof(U8))
    {
      log_WARNING_LO_MemoryAllocationFailed();
      return;
    }

    // step 1: check for errors
    Drv::I2cStatus status;
    U8 tmpdata = ERR_REG;
    status = this->I2C_Read_out(0, SLAVE_ADDR, tmpdata);
    if (status != Drv::I2cStatus::I2C_OK)
    {
      Fw::Logger::logMsg("I2cWriteRead Failed\n");
    }



    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

  void BMP388 ::
    SEND_DATA_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq,
        F32 pressure,
        F32 temp,
        F32 altitude
    )
  {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
