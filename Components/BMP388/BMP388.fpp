module BMP388Module {

  @ Component for sending a math operation
  active component BMP388 {

    # ----------------------------------------------------------------------
    # General ports
    # ----------------------------------------------------------------------

    @ Port for sending the operation request
    output port BMPRequest: BMPDataPorts.BMPDataRequest

    async input port mathResultIn: BMPDataPorts.MathResult

    output port I2C_Write: Drv.I2c
    output port I2C_Read: Drv.I2c
    output port I2C_ReadWrite: Drv.I2cWriteRead

    # @ Port for receiving the result
    # async input port mathResultIn: MathResult

    # ----------------------------------------------------------------------
    # Special ports
    # ----------------------------------------------------------------------

    @ Command receive port
    command recv port cmdIn

    @ Command registration port
    command reg port cmdRegOut

    @ Command response port
    command resp port cmdResponseOut

    @ Event port
    event port eventOut

    @ Telemetry port
    telemetry port tlmOut

    @ Text event port
    text event port textEventOut

    @ Time get port
    time get port timeGetOut

    # ----------------------------------------------------------------------
    # Commands
    # ----------------------------------------------------------------------

    @ Do a math operation
    async command SEND_DATA(
                           pressure: F32 @< pressure
                           temp: F32 @< temp
                           altitude: F32 @< altitude
                         )

    # ----------------------------------------------------------------------
    # Events
    # ----------------------------------------------------------------------

    @ Data command received
    event COMMAND_RECV(
                        pressure: F32 @< pressure data
                        temp: F32 @< temp data
                        altitude: F32 @< altitude data
                      ) \
      severity activity low \
      format "Math command received: {f} {f} {f}"

    # @ Received math result
    # event RESULT(
    #               result: F32 @< The math result
    #             ) \
    #   severity activity high \
    #   format "Math result is {f}"

    # ----------------------------------------------------------------------
    # Telemetry
    # ----------------------------------------------------------------------

    @ The pressure
    telemetry PRESSURE: F32

    @ The temp
    telemetry TEMP: F32

    @ The altitude
    telemetry ALTITUDE: F32

  }

}