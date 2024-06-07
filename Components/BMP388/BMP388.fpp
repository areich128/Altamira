module BMP388Module {

  @ Component for sending a math operation
  active component BMP388 {

    # ----------------------------------------------------------------------
    # General ports
    # ----------------------------------------------------------------------

    @ Port for sending the operation request
    output port BMPRequest: BMPDataPorts.BMPDataRequest

    async input port mathResultIn: BMPDataPorts.MathResult

    # FW buffer allocation and deallocaiton ports
    @ output port used to allocate a buffer
    output port allocate: Fw.BufferGet
    @ output port used to deallocate a buffer
    output port deallocate: Fw.BufferSend

    @I2C Ports
    output port I2C_Write: Drv.I2c
    output port I2C_Read: Drv.I2c
    output port I2C_ReadWrite: Drv.I2cWriteRead

    @ input port to run repeated actions, connected to ActiveRateGroup component output port
    sync input port SchedIn: [1] Svc.Sched

    @ Device is set to active, define operation mode, return WHO_AM_I read, and report device status
    async command startup_BMP388() #need to add a input here so we can set the SLP from the gds/from init but talk about rf and/or pad access

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
      id 5 \
      format "Math command received: {f} {f} {f}"

    event I2CBusOpenFailure() \ 
      severity warning high \
      id 0 \ 
      format "I2C bus failed to open correctly"
    
    @ I2C slave behavior setting failure
    event I2CSlaveBehaviorFailure() \
      severity warning high \
      id 1 \
      format "I2C slave behavior setting failure"

    @ A confirmation that device initialized successfully
    event DeviceInitialized() \
      severity activity high \
      id 2 \
      format "Init_MPL3115A2 command received, device WHO_AM_I, STATUS, and MODE registers output correctly"

    @ A warning that after initialization, status reads empty
    event FailedToStart() \
      severity warning high \
      id 3 \
      format "Device failed to initialize correctly"

    @ A warning that the buffer failed to allocate
    event MemoryAllocationFailed() \
      severity warning low \
      id 4 \
      format "Failed to allocate memory"

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