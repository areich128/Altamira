// ======================================================================
// \title  BMP388.cpp
// \author zhasieshmoist
// \brief  cpp file for BMP388 component implementation class
// ======================================================================

#include "Components/BMP388/BMP388.hpp"
#include "FpConfig.hpp"

#include "Fw/Types/BasicTypes.hpp"
#include <Fw/Logger/Logger.hpp>

namespace BMP388Module {

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  BMP388 ::
    BMP388(const char* const compName) :
      BMP388ComponentBase(compName)
  {

  }

  BMP388 ::
    ~BMP388()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

 void BMP388 ::
    SchedIn_handler(
        NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    Drv::I2cStatus status;
    
    // TODO
    Fw::Buffer dataGet = this->allocate_out(0, sizeof(U8));
    Fw::Buffer dataSend = this->allocate_out(0, sizeof(U8));

    if (dataGet.getSize() < sizeof(U8))
    {
      log_WARNING_LO_MemoryAllocationFailed();
      return;
    }

    if (dataSend.getSize() < sizeof(U8))
    {
      log_WARNING_LO_MemoryAllocationFailed();
      return;
    }
    // THIS IS WHERE ALL THE ACTUAL IMPLEMENTATION CODE GOES (according to the SRL repo)

    //TEMPERATURE
    //reading temperature calibration coefficients
    U8 temp_cal_coeffs[5];
    U8 temp_cal_coeff_reg[] = {NVM_PAR_T3, //ALERT! THIS IS AN I8 not a U8, HOW TO DEAL WITH THIS?
                              NVM_PAR_T2_2, 
                              NVM_PAR_T2_1, 
                              NVM_PAR_T1_2, 
                              NVM_PAR_T1_1};
    
    for (NATIVE_INT_TYPE buffer = 0; buffer < sizeof(temp_cal_coeff_reg); buffer++) {
      dataSend.getSerializeRepr().resetSer();
      dataSend.getSerializeRepr().serialize(temp_cal_coeff_reg[buffer]);
      status = this->I2C_WriteRead_out(0, SLAVE_ADDR, dataSend, dataGet);
      if(status!=Drv::I2cStatus::I2C_OK){
        Fw::Logger::logMsg("I2cWriteRead Failed\n");
      }
      temp_cal_coeffs[buffer]=*dataGet.getData();
    }
    U16 NVM_PAR_T2 = (temp_cal_coeffs[1] * 2^8) + temp_cal_coeffs[2];
    U16 NVM_PAR_T1 = (temp_cal_coeffs[3] * 2^8) + temp_cal_coeffs[4];

    float PAR_T1, PAR_T2, PAR_T3, cal_temp;
    PAR_T1 = NVM_PAR_T1 / (2^(-8));
    PAR_T2 = NVM_PAR_T2 / (2^30);
    PAR_T3 = float(temp_cal_coeffs[0]) / (2^48); //will this typecast work?

    float partial_data1, partial_data2;

    //reading un-calibrated temp data from the sensor
    U8 temp_data[3];
    U8 temp_data_reg[] = {TDATA_0, TDATA_1, TDATA_2};
    for (NATIVE_INT_TYPE buffer = 0; buffer < sizeof(temp_data_reg); buffer++) {
      dataSend.getSerializeRepr().resetSer();
      dataSend.getSerializeRepr().serialize(temp_data_reg[buffer]);
      status = this->I2C_WriteRead_out(0, SLAVE_ADDR, dataSend, dataGet);
      if(status!=Drv::I2cStatus::I2C_OK){
        Fw::Logger::logMsg("I2cWriteRead Failed\n");
      }
      temp_data[buffer]=*dataGet.getData();
    }

    float uncal_temp = (temp_data[2] * 2^16) + (temp_data[1] * 2^8) + temp_data[0];

    partial_data1 = uncal_temp - PAR_T1;
    partial_data2 = partial_data1 * PAR_T2;
    
    float temp = partial_data2 + (partial_data1 * partial_data1) * PAR_T3;
    //writing temp data to telemetry channel
    tlmWrite_TEMP(temp);

    //PRESSURE
    //reading coefficients
    U8 pres_cal_coeffs[16];
    U8 pres_cal_coeff_reg[] = {NVM_PAR_P11,
                              NVM_PAR_P10, 
                              NVM_PAR_P9_1,
                              NVM_PAR_P9_2,
                              NVM_PAR_P8,
                              NVM_PAR_P7,
                              NVM_PAR_P6_1,
                              NVM_PAR_P6_2,
                              NVM_PAR_P5_1,
                              NVM_PAR_P5_2,
                              NVM_PAR_P4,
                              NVM_PAR_P3,
                              NVM_PAR_P2_1,
                              NVM_PAR_P2_2,
                              NVM_PAR_P1_1,
                              NVM_PAR_P1_2};

    for (NATIVE_INT_TYPE buffer = 0; buffer < sizeof(pres_cal_coeff_reg); buffer++) {
      dataSend.getSerializeRepr().resetSer();
      dataSend.getSerializeRepr().serialize(pres_cal_coeff_reg[buffer]);
      status = this->I2C_WriteRead_out(0, SLAVE_ADDR, dataSend, dataGet);
      if(status!=Drv::I2cStatus::I2C_OK){
        Fw::Logger::logMsg("I2cWriteRead Failed\n");
      }
      pres_cal_coeffs[buffer]=*dataGet.getData();
    }
    float NVM_PAR_P9, NVM_PAR_P6, NVM_PAR_P5, NVM_PAR_P2, NVM_PAR_P1;
    NVM_PAR_P9 = I16((pres_cal_coeffs[3] * 2^8) + pres_cal_coeffs[2]);
    NVM_PAR_P6 = (pres_cal_coeffs[7] * 2^8) + pres_cal_coeffs[6];
    NVM_PAR_P5 = (pres_cal_coeffs[9] * 2^8) + pres_cal_coeffs[8];
    NVM_PAR_P2 = I16((pres_cal_coeffs[13] * 2^8) + pres_cal_coeffs[12]);
    NVM_PAR_P1 = (pres_cal_coeffs[15] * 2^8) + pres_cal_coeffs[14];

    float PAR_P1, PAR_P2, PAR_P3, PAR_P4, PAR_P5, PAR_P6, PAR_P7, PAR_P8, PAR_P9, PAR_P10, PAR_P11;
    PAR_P1 = float(NVM_PAR_P1 / (2^(-8)));
    PAR_P2 = float((NVM_PAR_P2 - (2^14))/ (2^29));
    PAR_P3 = float(pres_cal_coeffs[11] / (2^32));
    PAR_P4 = float(pres_cal_coeffs[10] / (2^37));
    PAR_P5 = NVM_PAR_P5 / (2^(-3));
    PAR_P6 = NVM_PAR_P6 / (2^6);
    PAR_P7 = float(pres_cal_coeffs[5] / (2^8));
    PAR_P8 = float(pres_cal_coeffs[4] / (2^15));
    PAR_P9 = float(NVM_PAR_P9 / (2^48));
    PAR_P10 = float(pres_cal_coeffs[1] / (2^48));
    PAR_P11 = float(pres_cal_coeffs[0] / (2^65));

    // crazy calibration formulas courtesy of the datasheet
    float pressure, partiald1, partiald2, partiald3, partiald4, partialo1, partialo2;
    partiald1 = PAR_P6 * temp;
    partiald2 = PAR_P7 * (temp * temp);
    partiald3 = PAR_P8 * (temp * temp * temp);
    partialo1 = PAR_P5 + partiald1 + partiald2 + partiald3;

    partiald1 = PAR_P2 * temp;
    partiald2 = PAR_P3 * (temp * temp);
    partiald3 = PAR_P4 * (temp * temp * temp);

    U8 pres_data[3];
    U8 pres_data_reg[] = {PDATA_0, PDATA_1, PDATA_2};
    for (NATIVE_INT_TYPE buffer = 0; buffer < sizeof(pres_data_reg); buffer++) {
      dataSend.getSerializeRepr().resetSer();
      dataSend.getSerializeRepr().serialize(pres_data_reg[buffer]);
      status = this->I2C_WriteRead_out(0, SLAVE_ADDR, dataSend, dataGet);
      if(status!=Drv::I2cStatus::I2C_OK){
        Fw::Logger::logMsg("I2cWriteRead Failed\n");
      }
      pres_data[buffer]=*dataGet.getData();
    }
    U32 uncal_pres = (pres_data[2] * (2^16)) + (pres_data[1] * (2^8)) + pres_data[0];

    partialo2 = (float)uncal_pres * (PAR_P1 + partiald1 + partiald2 + partiald3);

    partiald1 = (float)uncal_pres * (float)uncal_pres;
    partiald2 = PAR_P9 + PAR_P10 * temp;
    partiald3 = partiald1 * partiald2;

    pressure = partialo1 + partialo2 + partiald3 + partiald4;
    //writing pressure to telemetry channel
    tlmWrite_PRESSURE(pressure);

    //ALTITUDE
    //formula obtained from the arduino sample code here: https://github.com/adafruit/Adafruit_BMP3XX/blob/master/Adafruit_BMP3XX.cpp 
    float seaLevel = 1013.25;
    float atmos = pressure / 100.0;
    float altitude = 44330.0 * (1.0 - pow(atmos / seaLevel, 0.1903f));
    //writing altitude estimate to telemetry channel
    tlmWrite_ALTITUDE(altitude);

    // need to do some refactoring here:
      // 1. this calibration may need to go in the startup to prevent unneccessary load
      // 2. need to figure out which calibration coeffs need to be typecast to I8s

    // AFTER ALL THE CALIBRATION CODE ETC. WE DO
    // tlmWrite_ALTITUDE(altitude);
    // tlmWrite_PRESSURE(pressure);

    this->deallocate_out(portNum,dataGet);
    this->deallocate_out(portNum,dataSend);
  }

  void BMP388 ::
    mathResultIn_handler(
        NATIVE_INT_TYPE portNum,
        F32 result
    )
  {
    // TODO
  }

  // ----------------------------------------------------------------------
  // Handler implementations for commands
  // ----------------------------------------------------------------------

  void BMP388 ::
    startup_BMP388_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq
    )
  {
    // TODO

    // ACCORDING TO SRL REPO, STARTUP/INITIALIZATION CODE GOES HERE

    /*
    NOTES:
      - when WRITING data in I2C, your first bit should be the register address, followed by the rest of the data
      - when READING data in I2C, your input buffer should just be the address, and the output will be the data read
      **to my understanding**
    */
    
    // initializing read/write buffers
    // we use these whenever reading or writing
    Fw::Buffer dataGet = this->allocate_out(0, sizeof(U8));
    Fw::Buffer dataSend = this->allocate_out(0, sizeof(U8));

    // checking that memory has been properly allocated, else sending error
    if (dataGet.getSize() < sizeof(U8))
    {
      log_WARNING_LO_MemoryAllocationFailed();
      return;
    }

    if (dataSend.getSize() < sizeof(U8))
    {
      log_WARNING_LO_MemoryAllocationFailed();
      return;
    }

    //might want to check for WHOAMI first

    // step 1: check for errors
    Drv::I2cStatus status;
    //setting tempdata to the address of the status register
    //serializing to ensure correct data type
    dataSend.getSerializeRepr().resetSer();
    dataSend.getSerializeRepr().serialize(ERR_REG);
    //writereading to shorten the steps. must 1. write desired register, then 2. read
    status = this->I2C_WriteRead_out(0, SLAVE_ADDR, dataSend, dataGet);
    if (status != Drv::I2cStatus::I2C_OK)
    {
      Fw::Logger::logMsg("I2cWriteRead Failed\n");
    }
    U8 errstatus = *dataGet.getData();

    // checking if errors are detected on bits 0 1 or 2 of the error register
    if ((errstatus & 2^7) || (errstatus & 2^6) || (errstatus & 2^5)){
      Fw::Logger::logMsg("Error initializing sensor\n");
      log_WARNING_HI_FailedToStart();
      this->deallocate_out(0, dataGet);
      this->deallocate_out(0, dataSend);
      this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::EXECUTION_ERROR);
      return;
    }

    // step 2: check if data ready
    dataSend.getSerializeRepr().resetSer();
    dataSend.getSerializeRepr().serialize(STATUS);
    status = this->I2C_WriteRead_out(0, SLAVE_ADDR, dataSend, dataGet);
    if (status != Drv::I2cStatus::I2C_OK)
    {
      Fw::Logger::logMsg("I2cWriteRead Failed\n");
    }
    U8 sensorstatus = *dataGet.getData();
    //checking that bits 4 5 and 6 are true indicating ready for command, pressure data ready, and temp data ready respectively
    if (sensorstatus & 2^1){
      Fw::Logger::logMsg("Temperature data ready\n");
    } else {
      log_WARNING_HI_FailedToStart();
      Fw::Logger::logMsg("Error initializing BMP388");
      this->deallocate_out(0, dataGet);
      this->deallocate_out(0, dataSend);
      this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::EXECUTION_ERROR);
      return;
    }
    if (sensorstatus & 2^2){
      Fw::Logger::logMsg("Pressure data ready\n");
    } else {
      log_WARNING_HI_FailedToStart();
      Fw::Logger::logMsg("Error initializing BMP388");
      this->deallocate_out(0, dataGet);
      this->deallocate_out(0, dataSend);
      this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::EXECUTION_ERROR);
      return;
    }
    if (sensorstatus & 2^3){
      Fw::Logger::logMsg("Sensor ready to recieve commands\n");
    } else {
      log_WARNING_HI_FailedToStart();
      Fw::Logger::logMsg("Error initializing BMP388");
      this->deallocate_out(0, dataGet);
      this->deallocate_out(0, dataSend);
      this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::EXECUTION_ERROR);
      return;
    }

    // step 3: setting the PWR_CTRL register to turn on pressure and temp sensing, and put in normal mode
    dataSend.getSerializeRepr().resetSer();
    dataSend.getSerializeRepr().serialize(PWR_CTRL);
    status = this->I2C_WriteRead_out(0, SLAVE_ADDR, dataSend, dataGet);
    if (status != Drv::I2cStatus::I2C_OK)
    {
      Fw::Logger::logMsg("I2cWriteRead Failed\n");
    }
    U8 power_state = *dataGet.getData();

    dataSend.getSerializeRepr().resetSer();
    dataSend.getSerializeRepr().serialize(power_state | 0x33);
    status = this->I2C_Write_out(0, SLAVE_ADDR, dataSend);
    if (status != Drv::I2cStatus::I2C_OK)
    {
      Fw::Logger::logMsg("I2cWrite Failed\n");
    }

    this->deallocate_out(0, dataGet);
    this->deallocate_out(0, dataSend);
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

  void BMP388 ::
    SEND_DATA_cmdHandler(
        FwOpcodeType opCode,
        U32 cmdSeq,
        F32 pressure,
        F32 temp,
        F32 altitude
    )
  {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
  }

}
