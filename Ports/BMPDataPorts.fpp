module BMPDataPorts {
    @ Port for requesting data from the BMP
    port BMPDataRequest(
        pressure: F32 @< Pressure data
        temp: F32 @< Temperature data
        altitude: F32 @< Altitude estimation
    )

    @ Port just so that i can add an async input
    port MathResult(
        result: F32 @< random number i guess
    )
}