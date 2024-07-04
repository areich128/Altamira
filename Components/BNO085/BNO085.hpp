// ======================================================================
// \title  BNO085.hpp
// \author zhasieshmoist
// \brief  hpp file for BNO085 component implementation class
// ======================================================================

#ifndef BNO085Module_BNO085_HPP
#define BNO085Module_BNO085_HPP

#include "Components/BNO085/BNO085ComponentAc.hpp"
#include "Fw/Types/BasicTypes.hpp"
#include <Fw/Logger/Logger.hpp>

#include <unistd.h> // required for I2C device access
#include <fcntl.h>  // required for I2C device configuration
#include <cerrno>
#include <unistd.h>
#include <cmath>

namespace BNO085Module {

  class BNO085 :
    public BNO085ComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Component construction and destruction
      // ----------------------------------------------------------------------

      //! Construct BNO085 object
      BNO085(
          const char* const compName //!< The component name
      );

      //! Destroy BNO085 object
      ~BNO085();

      //Create SHTP Packet
      Fw::Buffer createSHTP();

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

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for commands
      // ----------------------------------------------------------------------

      //! Handler implementation for command TODO
      //!
      //! TODO
      void TODO_cmdHandler(
          FwOpcodeType opCode, //!< The opcode
          U32 cmdSeq //!< The command sequence number
      ) override;

      //! Handler implementation for command startup_BNO085
      //!
      //! Device is set to active, define operation mode, return WHO_AM_I read, and report device status
      void startup_BNO085_cmdHandler(
          FwOpcodeType opCode, //!< The opcode
          U32 cmdSeq //!< The command sequence number
      ) override;

  };

}

#endif
