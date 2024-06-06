module I2C {

  @ I2C operations for reading and writing data
  port I2cReadWrite(
                    addr: U32 @< I2C slave device address
                    op: I2C.I2cOperation @< Operation to perform (READ, WRITE, or BOTH)
                    ref writeBuffer: Types.buffer @< Array of bytes for data to write or to store read data
                    length: U32 @< Number of bytes to write or read
                   )

  enum I2cOperation {
    READ = 0 @< Perform a read operation
    WRITE = 1 @< Perform a write operation
    BOTH = 2 @< Perform both read and write in a single operation
  }

  enum I2cStatus {
    I2C_OK = 0 @< Transaction okay
    I2C_ADDRESS_ERR = 1 @< I2C address invalid
    I2C_WRITE_ERR = 2 @< I2C write failed
    I2C_READ_ERR = 3 @< I2C read failed
    I2C_OTHER_ERR = 4 @< Other errors that don't fit
  }

}
