// ======================================================================
// \title  BNO085.hpp
// \author zhasieshmoist
// \brief  hpp file for BNO085 component implementation class
// ======================================================================

#ifndef BNO085Module_BNO085_HPP
#define BNO085Module_BNO085_HPP

#include "BNO085/BNO085ComponentAc.hpp"

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

  };

}

#endif
