module BNO085Module {
    @ Accel, Mag, Gyro and Orientation sensor for Altamira sensor suite.
    active component BNO085 {

    # One async command/port is required for active components
    # This should be overridden by the developers with a useful command/port
    @ TODO
    async command TODO opcode 0
    # FW buffer allocation and deallocaiton ports

    @ output port used to allocate a buffer
    output port allocate: Fw.BufferGet
    @ output port used to deallocate a buffer
    output port deallocate: Fw.BufferSend

    @I2C Ports
    output port I2C_Write: Drv.I2c
    output port I2C_Read: Drv.I2c
    output port I2C_WriteRead: Drv.I2cWriteRead

    @ input port to run repeated actions, connected to ActiveRateGroup component output port
    sync input port SchedIn: [1] Svc.Sched

    @ Device is set to active, define operation mode, return WHO_AM_I read, and report device status
    async command startup_BNO085() #need to add a input here so we can set the SLP from the gds/from init but talk about rf and/or pad access

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

    # @ Do a math operation
    # async command SEND_DATA(
    #                        pressure: F32 @< pressure
    #                        temp: F32 @< temp
    #                        altitude: F32 @< altitude
    #                      )

    # ----------------------------------------------------------------------
    # Events
    # ----------------------------------------------------------------------

    # @ Data command received
    # event COMMAND_RECV(
    #                     pressure: F32 @< pressure data
    #                     temp: F32 @< temp data
    #                     altitude: F32 @< altitude data
    #                   ) \
    #   severity activity low \
    #   id 5 \
    #   format "Math command received: {f} {f} {f}"

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

    @ Accel X
    telemetry ACCEL_X: F32

    @ Accel Y
    telemetry ACCEL_Y: F32

    @ Accel Z
    telemetry ACCEL_Z: F32

    @ Mag X
    telemetry MAG_X: F32

    @ Mag Y
    telemetry MAG_Y: F32

    @ Mag Z
    telemetry MAG_Z: F32

    @ HEADING W
    telemetry HEAD_W: F32

    @ HEADING X
    telemetry HEAD_X: F32

    @ HEADING Y
    telemetry HEAD_Y: F32

    @ HEADING Z
    telemetry HEAD_Z: F32

  }

}