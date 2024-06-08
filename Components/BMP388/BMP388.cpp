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
  // Handler implementations for commands
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
    // we use these whenever reading or writing
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

    //might want to check for WHOAMI first

    // step 1: check for errors
    Drv::I2cStatus status;
    //setting tempdata to the address of the status register
    //serializing to ensure correct data type
    dataSend.getSerializeRepr().resetSer();
    dataSend.getSerializeRepr().serialize(ERR_REG);
    //writereading to shorten the steps. must 1. write desired register, then 2. read
    status = this->I2C_WriteRead_out(0, SLAVE_ADDR, dataSend, dataGet);
    if (status != Drv::I2cStatus::I2C_OK)
    {
      Fw::Logger::logMsg("I2cWriteRead Failed\n");
    }
    U8 errstatus = *dataGet.getData();

    // checking if errors are detected on bits 0 1 or 2 of the error register
    if ((errstatus & 2^7) || (errstatus & 2^6) || (errstatus & 2^5)){
      Fw::Logger::logMsg("Error initializing sensor\n");
    }

    // step 2: check if data ready
    dataSend.getSerializeRepr().resetSer();
    dataSend.getSerializeRepr().serialize(STATUS);
    status = this->I2C_WriteRead_out(0, SLAVE_ADDR, dataSend, dataGet);
    if (status != Drv::I2cStatus::I2C_OK)
    {
      Fw::Logger::logMsg("I2cWriteRead Failed\n");
    }
    U8 sensorstatus = *dataGet.getData();
    //checking that bits 4 5 and 6 are true indicating ready for command, pressure data ready, and temp data ready respectively
    if (sensorstatus & 2^1){
      Fw::Logger::logMsg("Temperature data ready\n");
    }
    if (sensorstatus & 2^2){
      Fw::Logger::logMsg("Pressure data ready\n");
    }
    if (sensorstatus & 2^3){
      Fw::Logger::logMsg("Sensor ready to recieve commands\n");
    }



    this->deallocate_out(dataGet);
    this->deallocate_out(dataSend);
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
