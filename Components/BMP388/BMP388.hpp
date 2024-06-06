// ======================================================================
// \title  BMP388.hpp
// \author zhasieshmoist
// \brief  hpp file for BMP388 component implementation class
// ======================================================================

#ifndef BMP388Module_BMP388_HPP
#define BMP388Module_BMP388_HPP

#include "Components/BMP388/BMP388ComponentAc.hpp"

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

      //! Handler implementation for mathResultIn
      void mathResultIn_handler(
          NATIVE_INT_TYPE portNum, //!< The port number
          F32 result //!< random number i guess
      ) override;

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for commands
      // ----------------------------------------------------------------------

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
