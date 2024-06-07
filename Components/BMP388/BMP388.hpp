// ======================================================================
// \title  BMP388.hpp
// \author zhasieshmoist
// \brief  hpp file for BMP388 component implementation class
// ======================================================================

#ifndef BMP388Module_BMP388_HPP
#define BMP388Module_BMP388_HPP

#include "Components/BMP388/BMP388ComponentAc.hpp"

// REGISTERS SPECIFIED HERE
const U8 SLAVE_ADDR = 0x77;

const U8 CHIP_ID = 0x00;

// SENSOR ERROR CONDITIONS
const U8 ERR_REG = 0x02; //bit 0: fatal error, 1: command execution error, 2: configuration error

// SENSOR STATUS
const U8 STATUS = 0x03; //bit 4: ready to recieve command, 5: pressure data ready, 6: temp data ready

// DATA REGISTERS
const U8 PDATA_0 = 0x04; //bits 0-7 of pressure reading
const U8 PDATA_1 = 0x05; //bits 8-15 of pressure reading
const U8 PDATA_2 = 0x06; //bits 16-23 of pressure reading

const U8 TDATA_0 = 0x07; //bits 0-7 of temp reading
const U8 TDATA_1 = 0x08; //bits 8-15 of temp reading
const U8 TDATA_2 = 0x09; //bits 16-23 of temp reading
  //ALTITUDE NEEDS TO BE CALCULATED BY HAND :(

// MODE/POWER CONTROL
const U8 PWR_CTRL = 0x1B; //bit 0: pressure sensor on/off, 1: temp on/off, 4/5: sleep(00)/normal(11)/forced(10 || 01)

#include <unistd.h> // required for I2C device access
#include <fcntl.h>  // required for I2C device configuration
#include <cerrno>
#include <unistd.h>

namespace BMP388Module {

  class BMP388 :
    public BMP388ComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Component construction and destruction
      // ----------------------------------------------------------------------

      //! Construct BMP388 object
      BMP388(
          const char* const compName //!< The component name
      );

      //! Destroy BMP388 object
      ~BMP388();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for SchedIn
      //!
      //! input port to run repeated actions, connected to ActiveRateGroup component output port
      void SchedIn_handler(
          NATIVE_INT_TYPE portNum, //!< The port number
          NATIVE_UINT_TYPE context //!< The call order
      ) override;

      //! Handler implementation for mathResultIn
      void mathResultIn_handler(
          NATIVE_INT_TYPE portNum, //!< The port number
          F32 result //!< random number i guess
      ) override;

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for commands
      // ----------------------------------------------------------------------

      //! Handler implementation for command startup_BMP388
      //!
      //! Device is set to active, define operation mode, return WHO_AM_I read, and report device status
      void startup_BMP388_cmdHandler(
          FwOpcodeType opCode, //!< The opcode
          U32 cmdSeq //!< The command sequence number
      ) override;

      //! Handler implementation for command SEND_DATA
      //!
      //! Do a math operation
      void SEND_DATA_cmdHandler(
          FwOpcodeType opCode, //!< The opcode
          U32 cmdSeq, //!< The command sequence number
          F32 pressure, //!< pressure
          F32 temp, //!< temp
          F32 altitude //!< altitude
      ) override;

  };

}

#endif
