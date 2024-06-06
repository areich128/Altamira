// ======================================================================
// \title  BMP388.hpp
// \author zhasieshmoist
// \brief  hpp file for BMP388 component implementation class
// ======================================================================

#ifndef BMP388_BMP388_HPP
#define BMP388_BMP388_HPP

#include "Components/BMP388/BMP388ComponentAc.hpp"

namespace BMP388 {

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
