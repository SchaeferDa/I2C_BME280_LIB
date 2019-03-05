/*
 * I2C_LIB.h
 *
 * Created: 14.02.2019 16:19:06
 * Author:  Daniel Schäfer
 * Contact: code@schaeferservices.de
 */

#ifndef I2C_LIB_H_
#define I2C_LIB_H_

#define F_CPU 16000000UL
#include <util/delay.h>

typedef enum{FALSE, TRUE} boolean;

/************************************************************************/
/* prototypes of I2C-functions                                          */
/************************************************************************/
void initI2C(double time, char unit);
void sendStartCondition();
void sendStopCondition();
boolean sendByte(unsigned char byte);
unsigned char readSlave(unsigned char slaveAddress);
unsigned char readRegister(unsigned char slaveAddress, unsigned char registerAddress);


#endif /* I2C_LIB_H_ */