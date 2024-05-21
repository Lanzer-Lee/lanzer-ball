#ifndef __IMU_H
#define __IMU_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "REG.h"
#include "I2C.h"
#include "Serial.h"
#include "Delay.h"
#include "GAME.h"

#define WIT_HAL_OK      (0)     /**< There is no error */
#define WIT_HAL_BUSY    (-1)    /**< Busy */
#define WIT_HAL_TIMEOUT (-2)    /**< Timed out */
#define WIT_HAL_ERROR   (-3)    /**< A generic error happens */
#define WIT_HAL_NOMEM   (-4)    /**< No memory */
#define WIT_HAL_EMPTY   (-5)    /**< The resource is empty */
#define WIT_HAL_INVAL   (-6)    /**< Invalid argument */

#define WIT_DATA_BUFF_SIZE  256

#define WIT_PROTOCOL_NORMAL 0
#define WIT_PROTOCOL_MODBUS 1
#define WIT_PROTOCOL_CAN    2
#define WIT_PROTOCOL_I2C    3

#define FuncW 0x06
#define FuncR 0x03

#define ACC_UPDATE   0x01
#define GYRO_UPDATE  0x02
#define ANGLE_UPDATE 0x04
#define MAG_UPDATE   0x08
#define READ_UPDATE  0x80

typedef struct{
    __IO float Accelerate[3];
    __IO float Gyro[3];
    __IO float Angle[3];
    __IO float Azimuth;
    float InitAzimuth;
}IMU_TypeDef;

typedef void (*SerialWrite)(uint8_t *p_ucData, uint32_t uiLen);
typedef int32_t (*WitI2cWrite)(uint8_t ucAddr, uint8_t ucReg, uint8_t *p_ucVal, uint32_t uiLen);
typedef int32_t (*WitI2cRead)(uint8_t ucAddr, uint8_t ucReg, uint8_t *p_ucVal, uint32_t uiLen);
typedef void (*CanWrite)(uint8_t ucStdId, uint8_t *p_ucData, uint32_t uiLen);
typedef void (*DelaymsCb)(uint16_t ucMs);
typedef void (*RegUpdateCb)(uint32_t uiReg, uint32_t uiRegNum);

extern IMU_TypeDef imu;
extern int16_t sReg[REGSIZE];

void IMU_Init(IMU_TypeDef *IMU);
void IMU_Data_Process(IMU_TypeDef *IMU);
int32_t WitSerialWriteRegister(SerialWrite write_func);
void WitSerialDataIn(uint8_t ucData);
int32_t WitI2cFuncRegister(WitI2cWrite write_func, WitI2cRead read_func);
int32_t WitCanWriteRegister(CanWrite write_func);
int32_t WitDelayMsRegister(DelaymsCb delayms_func);
void WitCanDataIn(uint8_t ucData[8], uint8_t ucLen);
int32_t WitRegisterCallBack(RegUpdateCb update_func);
int32_t WitWriteReg(uint32_t uiReg, uint16_t usData);
int32_t WitReadReg(uint32_t uiReg, uint32_t uiReadNum);
int32_t WitInit(uint32_t uiProtocol, uint8_t ucAddr);
void WitDeInit(void);
int32_t WitStartAccCali(void);
int32_t WitStopAccCali(void);
int32_t WitStartMagCali(void);
int32_t WitStopMagCali(void);
int32_t WitSetUartBaud(int32_t uiBaudIndex);
int32_t WitSetBandwidth(int32_t uiBaudWidth);
int32_t WitSetOutputRate(int32_t uiRate);
int32_t WitSetContent(int32_t uiRsw);
int32_t WitSetCanBaud(int32_t uiBaudIndex);
char CheckRange(short sTemp,short sMin,short sMax);

#ifdef __cplusplus
}
#endif

#endif 
