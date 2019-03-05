/*
 * I2C_BME280_LIB.c
 *
 * Created: 04.03.2019 16:30:04
 * Author: Daniel Schäfer
 * Contact: code@schaeferservices.de
 */ 
#include "I2C_LIB.h"

void BME280_init(unsigned char address);
void BME280_soft_reset();
double BME280_get_temperature();
double BME280_get_pressure();
double BME280_get_humidity();
void BME280_calibrate_temperature();
void BME280_calibrate_pressure();
void BME280_calibrate_humidity();
boolean BME280_set_mode(unsigned char mode);
boolean BME280_set_sleep_mode();
boolean BME280_set_forced_mode();
boolean BME280_set_normal_mode();
unsigned char BME280_get_mode();
boolean BME280_set_standby_time(unsigned char standby_time);
boolean BME280_set_standby_time_0_5();
boolean BME280_set_standby_time_62_5();
boolean BME280_set_standby_time_125();
boolean BME280_set_standby_time_250();
boolean BME280_set_standby_time_500();
boolean BME280_set_standby_time_1000();
boolean BME280_set_standby_time_10();
boolean BME280_set_standby_time_20();
unsigned char BME280_get_standby_time();
boolean BME280_set_filter_coefficient(unsigned char filter_coefficient);
boolean BME280_set_filter_coefficient_off();
boolean BME280_set_filter_coefficient_2();
boolean BME280_set_filter_coefficient_4();
boolean BME280_set_filter_coefficient_8();
boolean BME280_set_filter_coefficient_16();
unsigned char BME280_get_filter_coefficient();
boolean BME280_set_temperature_oversampling(unsigned char temperature_oversampling);
boolean BME280_set_temperature_oversampling_off();
boolean BME280_set_temperature_oversampling_1();
boolean BME280_set_temperature_oversampling_2();
boolean BME280_set_temperature_oversampling_4();
boolean BME280_set_temperature_oversampling_8();
boolean BME280_set_temperature_oversampling_16();
unsigned char BME280_get_temperature_oversampling();
boolean BME280_set_pressure_oversampling(unsigned char pressure_oversampling);
boolean BME280_set_pressure_oversampling_off();
boolean BME280_set_pressure_oversampling_1();
boolean BME280_set_pressure_oversampling_2();
boolean BME280_set_pressure_oversampling_4();
boolean BME280_set_pressure_oversampling_8();
boolean BME280_set_pressure_oversampling_16();
unsigned char BME280_get_pressure_oversampling();
boolean BME280_set_humidity_oversampling(unsigned char humidity_oversampling);
boolean BME280_set_humidity_oversampling_off();
boolean BME280_set_humidity_oversampling_1();
boolean BME280_set_humidity_oversampling_2();
boolean BME280_set_humidity_oversampling_4();
boolean BME280_set_humidity_oversampling_8();
boolean BME280_set_humidity_oversampling_16();
unsigned char BME280_get_humidity_oversampling();

// data register for humidity
#define REG_HUM_LSB 0xFE
#define REG_HUM_MSB 0xFD

// data register for temperature
#define REG_TEMP_XLSB 0xFC
#define REG_TEMP_LSB 0xFB
#define REG_TEMP_MSB 0xFA

// data register for pressure
#define REG_PRESS_XLSB 0xF9
#define REG_PRESS_LSB 0xF8
#define REG_PRESS_MSB 0xF7

// configuration register for temperature and pressure
#define REG_CTRL_MEAS 0xF4

// configuration register for humidity
#define REG_CTRL_HUM 0xF2

// calibration register for temperature
#define REG_CALIB_00 0x88
#define REG_CALIB_01 0x89
#define REG_CALIB_02 0x8A
#define REG_CALIB_03 0x8B
#define REG_CALIB_04 0x8C
#define REG_CALIB_05 0x8D

// calibration register for pressure
#define REG_CALIB_06 0x8E
#define REG_CALIB_07 0x8F
#define REG_CALIB_08 0x90
#define REG_CALIB_09 0x91
#define REG_CALIB_10 0x92
#define REG_CALIB_11 0x93
#define REG_CALIB_12 0x94
#define REG_CALIB_13 0x95
#define REG_CALIB_14 0x96
#define REG_CALIB_15 0x97
#define REG_CALIB_16 0x98
#define REG_CALIB_17 0x99
#define REG_CALIB_18 0x9A
#define REG_CALIB_19 0x9B
#define REG_CALIB_20 0x9C
#define REG_CALIB_21 0x9D
#define REG_CALIB_22 0x9E
#define REG_CALIB_23 0x9F

// calibration register for humidity
#define REG_CALIB_24 0xA1
#define REG_CALIB_25 0xE1
#define REG_CALIB_26 0xE2
#define REG_CALIB_27 0xE3
#define REG_CALIB_28 0xE4
#define REG_CALIB_29 0xE5
#define REG_CALIB_30 0xE6
#define REG_CALIB_31 0xE7

// global control register
#define REG_CONFIG 0xF5
#define REG_STATUS 0xF3
#define REG_RESET 0xE0
#define REG_ID 0xD0

double BME280_compensate_T_double(int32_t adc_T);
double BME280_compensate_P_double(int32_t adc_P);
double BME280_compensate_H_double(int32_t adc_H);
boolean writeToRegister(unsigned char registerAddress, unsigned char data);
unsigned char readFromRegister(unsigned char registerAddress);

unsigned char slaveAddressR = 0x00;
unsigned char slaveAddressW = 0x00;
uint16_t dig_T1;
int16_t dig_T2;
int16_t dig_T3;
uint16_t dig_P1;
int16_t dig_P2;
int16_t dig_P3;
int16_t dig_P4;
int16_t dig_P5;
int16_t dig_P6;
int16_t dig_P7;
int16_t dig_P8;
int16_t dig_P9;

unsigned char dig_H1;
int16_t dig_H2;
unsigned char dig_H3;
int16_t dig_H4;
int16_t dig_H5;
char dig_H6;

int32_t t_fine;

void BME280_init(unsigned char address)
{
	slaveAddressR = address | 0b00000001;
	slaveAddressW = address & 0b11111110;
}

/*
+------+------------+
| data |  time [ms] |
+------+------------+
| 0x00 |     0.5    |
+------+------------+
| 0x20 |    62.5    |
+------+------------+
| 0x40 |     125    |
+------+------------+
| 0x60 |     250    |
+------+------------+
| 0x80 |     500    |
+------+------------+
| 0xA0 |    1000    |
+------+------------+
| 0xC0 |     10     |
+------+------------+
| 0xE0 |     20     |
+------+------------+
*/
boolean BME280_set_standby_time(unsigned char standby_time)
{
	unsigned char mode = BME280_get_mode();
	unsigned char reg_config = readFromRegister(REG_CONFIG);
	
	BME280_set_sleep_mode();

	boolean state = writeToRegister(REG_CONFIG, ((reg_config & 0b00011111) | standby_time));
	
	BME280_set_mode(mode);
	
	return state;
}

boolean BME280_set_standby_time_0_5()
{
	return BME280_set_standby_time(0x00);
}

boolean BME280_set_standby_time_62_5()
{
	return BME280_set_standby_time(0x20);
}

boolean BME280_set_standby_time_125()
{
	return BME280_set_standby_time(0x40);
}

boolean BME280_set_standby_time_250()
{
	return BME280_set_standby_time(0x60);
}

boolean BME280_set_standby_time_500()
{
	return BME280_set_standby_time(0x80);
}

boolean BME280_set_standby_time_1000()
{
	return BME280_set_standby_time(0xA0);
}

boolean BME280_set_standby_time_10()
{
	return BME280_set_standby_time(0xC0);
}

boolean BME280_set_standby_time_20()
{
	return BME280_set_standby_time(0xE0);
}

unsigned char BME280_get_standby_time()
{
	return (readFromRegister(REG_CONFIG) & 0b11100000);
}

/*
+------+----------------------+
| data |     oversampling     |
+------+----------------------+
| 0x00 | off (output 0x80000) |
+------+----------------------+
| 0x20 |    oversampling ×1   |
+------+----------------------+
| 0x40 |    oversampling ×2   |
+------+----------------------+
| 0x60 |    oversampling ×4   |
+------+----------------------+
| 0x80 |    oversampling ×8   |
+------+----------------------+
| 0xA0 |   oversampling ×16   |
+------+----------------------+
*/
boolean BME280_set_temperature_oversampling(unsigned char temperature_oversampling)
{
	unsigned char reg_ctrl_meas = readFromRegister(REG_CTRL_MEAS);
	
	return writeToRegister(REG_CTRL_MEAS, ((reg_ctrl_meas & 0b00011111) | temperature_oversampling));
}

boolean BME280_set_temperature_oversampling_off()
{
	return BME280_set_temperature_oversampling(0x00);
}

boolean BME280_set_temperature_oversampling_1()
{
	return BME280_set_temperature_oversampling(0x20);
}

boolean BME280_set_temperature_oversampling_2()
{
	return BME280_set_temperature_oversampling(0x40);
}

boolean BME280_set_temperature_oversampling_4()
{
	return BME280_set_temperature_oversampling(0x60);
}

boolean BME280_set_temperature_oversampling_8()
{
	return BME280_set_temperature_oversampling(0x80);
}

boolean BME280_set_temperature_oversampling_16()
{
	return BME280_set_temperature_oversampling(0xA0);
}

unsigned char BME280_get_temperature_oversampling()
{
	return (readFromRegister(REG_CTRL_MEAS) & 0b11100000);
}

/*
+------+----------------------+
| data |     oversampling     |
+------+----------------------+
| 0x00 | off (output 0x80000) |
+------+----------------------+
| 0x04 |    oversampling ×1   |
+------+----------------------+
| 0x08 |    oversampling ×2   |
+------+----------------------+
| 0x0C |    oversampling ×4   |
+------+----------------------+
| 0x10 |    oversampling ×8   |
+------+----------------------+
| 0x14 |   oversampling ×16   |
+------+----------------------+
*/
boolean BME280_set_pressure_oversampling(unsigned char pressure_oversampling)
{
	unsigned char reg_ctrl_meas = readFromRegister(REG_CTRL_MEAS);
	
	return writeToRegister(REG_CTRL_MEAS, ((reg_ctrl_meas & 0b11100011) | pressure_oversampling));
}

boolean BME280_set_pressure_oversampling_off()
{
	return BME280_set_pressure_oversampling(0x00);
}

boolean BME280_set_pressure_oversampling_1()
{
	return BME280_set_pressure_oversampling(0x04);
}

boolean BME280_set_pressure_oversampling_2()
{
	return BME280_set_pressure_oversampling(0x08);
}

boolean BME280_set_pressure_oversampling_4()
{
	return BME280_set_pressure_oversampling(0x0C);
}

boolean BME280_set_pressure_oversampling_8()
{
	return BME280_set_pressure_oversampling(0x10);
}

boolean BME280_set_pressure_oversampling_16()
{
	return BME280_set_pressure_oversampling(0x14);
}

unsigned char BME280_get_pressure_oversampling()
{
	return (readFromRegister(REG_CTRL_MEAS) & 0b00011100);
}

/*
+------+----------------------+
| data |     oversampling     |
+------+----------------------+
| 0x00 | off (output 0x80000) |
+------+----------------------+
| 0x01 |    oversampling ×1   |
+------+----------------------+
| 0x02 |    oversampling ×2   |
+------+----------------------+
| 0x03 |    oversampling ×4   |
+------+----------------------+
| 0x04 |    oversampling ×8   |
+------+----------------------+
| 0x05 |   oversampling ×16   |
+------+----------------------+
*/
boolean BME280_set_humidity_oversampling(unsigned char humidity_oversampling)
{
	unsigned char reg_ctrl_hum = readFromRegister(REG_CTRL_HUM);
	
	return writeToRegister(REG_CTRL_HUM, ((reg_ctrl_hum & 0b11111000) | humidity_oversampling));
}

boolean BME280_set_humidity_oversampling_off()
{
	return BME280_set_humidity_oversampling(0x00);
}

boolean BME280_set_humidity_oversampling_1()
{
	return BME280_set_humidity_oversampling(0x01);
}

boolean BME280_set_humidity_oversampling_2()
{
	return BME280_set_humidity_oversampling(0x02);
}

boolean BME280_set_humidity_oversampling_4()
{
	return BME280_set_humidity_oversampling(0x03);
}

boolean BME280_set_humidity_oversampling_8()
{
	return BME280_set_humidity_oversampling(0x04);
}

boolean BME280_set_humidity_oversampling_16()
{
	return BME280_set_humidity_oversampling(0x05);
}

unsigned char BME280_get_humidity_oversampling()
{
	return (readFromRegister(REG_CTRL_HUM) & 0b00000111);
}

/*
+------+--------------------+
| data | filter coefficient |
+------+--------------------+
| 0x00 |         off        |
+------+--------------------+
| 0x04 |          2         |
+------+--------------------+
| 0x08 |          4         |
+------+--------------------+
| 0x0C |          8         |
+------+--------------------+
| 0x10 |         16         |
+------+--------------------+
*/
boolean BME280_set_filter_coefficient(unsigned char filter_coefficient)
{
	unsigned char mode = BME280_get_mode();
	unsigned char reg_config = readFromRegister(REG_CONFIG);
	
	BME280_set_sleep_mode();

	boolean state = writeToRegister(REG_CONFIG, ((reg_config & 0b11100011) | filter_coefficient));
	
	BME280_set_mode(mode);
	
	return state;
}

boolean BME280_set_filter_coefficient_off()
{
	return BME280_set_filter_coefficient(0x00);
}

boolean BME280_set_filter_coefficient_2()
{
	return BME280_set_filter_coefficient(0x04);
}

boolean BME280_set_filter_coefficient_4()
{
	return BME280_set_filter_coefficient(0x08);
}

boolean BME280_set_filter_coefficient_8()
{
	return BME280_set_filter_coefficient(0x0C);
}

boolean BME280_set_filter_coefficient_16()
{
	return BME280_set_filter_coefficient(0x10);
}

unsigned char BME280_get_filter_coefficient()
{
	return (readFromRegister(REG_CONFIG) & 0b00011100);
}

/*
+--------------+-------------+
|     data     |     mode    |
+--------------+-------------+
|     0x00     |  sleep mode |
+--------------+-------------+
| 0x01 or 0x02 | forced mode |
+--------------+-------------+
|     0x03     | normal mode |
+--------------+-------------+
*/
boolean BME280_set_mode(unsigned char mode)
{
	unsigned char reg_ctrl_meas = readFromRegister(REG_CTRL_MEAS);
	
	return writeToRegister(REG_CTRL_MEAS, ((reg_ctrl_meas & 0b11111100) | mode));
}

boolean BME280_set_sleep_mode()
{
	return BME280_set_mode(0x00);
}

boolean BME280_set_forced_mode()
{
	return BME280_set_mode(0x01);
}

boolean BME280_set_normal_mode()
{
	return BME280_set_mode(0x03);
}

unsigned char BME280_get_mode()
{
	return (readFromRegister(REG_CTRL_MEAS) & 0b00000011);
}

void BME280_calibrate_temperature()
{
	dig_T1 = 0;
	dig_T2 = 0;
	dig_T3 = 0;
	
	dig_T1 |= readFromRegister(REG_CALIB_00);
	dig_T1 |= (readFromRegister(REG_CALIB_01) << 8);
	
	dig_T2 |= readFromRegister(REG_CALIB_02);
	dig_T2 |= (readFromRegister(REG_CALIB_03) << 8);
	
	dig_T3 |= readFromRegister(REG_CALIB_04);
	dig_T3 |= (readFromRegister(REG_CALIB_05) << 8);
}

void BME280_calibrate_pressure()
{
	dig_P1 = 0;
	dig_P2 = 0;
	dig_P3 = 0;
	dig_P4 = 0;
	dig_P5 = 0;
	dig_P6 = 0;
	dig_P7 = 0;
	dig_P8 = 0;
	dig_P9 = 0;
	
	dig_P1 |= readFromRegister(REG_CALIB_06);
	dig_P1 |= (readFromRegister(REG_CALIB_07) << 8);
	
	dig_P2 |= readFromRegister(REG_CALIB_08);
	dig_P2 |= (readFromRegister(REG_CALIB_09) << 8);
	
	dig_P3 |= readFromRegister(REG_CALIB_10);
	dig_P3 |= (readFromRegister(REG_CALIB_11) << 8);
	
	dig_P4 |= readFromRegister(REG_CALIB_12);
	dig_P4 |= (readFromRegister(REG_CALIB_13) << 8);
	
	dig_P5 |= readFromRegister(REG_CALIB_14);
	dig_P5 |= (readFromRegister(REG_CALIB_15) << 8);
	
	dig_P6 |= readFromRegister(REG_CALIB_16);
	dig_P6 |= (readFromRegister(REG_CALIB_17) << 8);
	
	dig_P7 |= readFromRegister(REG_CALIB_18);
	dig_P7 |= (readFromRegister(REG_CALIB_19) << 8);
	
	dig_P8 |= readFromRegister(REG_CALIB_20);
	dig_P8 |= (readFromRegister(REG_CALIB_21) << 8);
	
	dig_P9 |= readFromRegister(REG_CALIB_22);
	dig_P9 |= (readFromRegister(REG_CALIB_23) << 8);
}

void BME280_calibrate_humidity()
{
	dig_H1 = 0;
	dig_H2 = 0;
	dig_H3 = 0;
	dig_H4 = 0;
	dig_H5 = 0;
	dig_H6 = 0;
	
	dig_H1 |= readFromRegister(REG_CALIB_24);
	
	dig_H2 |= readFromRegister(REG_CALIB_25);
	dig_H2 |= (readFromRegister(REG_CALIB_26) << 8);
	
	dig_H3 |= readFromRegister(REG_CALIB_27);
	
	dig_H4 |= (int16_t)readFromRegister(REG_CALIB_28) << 4;
	dig_H4 |= ((int16_t)readFromRegister(REG_CALIB_29) & 0b00001111);
	
	dig_H5 |= ((int16_t)readFromRegister(REG_CALIB_29) & 0b11110000) >> 4;
	dig_H5 |= (readFromRegister(REG_CALIB_30) << 8);
	
	dig_H6 |= readFromRegister(REG_CALIB_31);
}

void BME280_soft_reset()
{
	writeToRegister(0xE0, 0xB6);
}

double BME280_get_temperature()
{
	int32_t temp = 0;
	
	temp |= ((int32_t)readFromRegister(REG_TEMP_MSB) << 12);
	temp |= ((int32_t)readFromRegister(REG_TEMP_LSB) <<  4);
	temp |= ((int32_t)readFromRegister(REG_TEMP_XLSB) >>  4);
	
	return BME280_compensate_T_double(temp);
}

double BME280_get_pressure()
{
	int32_t press = 0;
	
	press |= ((int32_t)readFromRegister(REG_PRESS_MSB) << 12);
	press |= ((int32_t)readFromRegister(REG_PRESS_LSB) <<  4);
	press |= ((int32_t)readFromRegister(REG_PRESS_XLSB) >>  4);
	
	return BME280_compensate_P_double(press);
}

double BME280_get_humidity()
{
	int32_t hum = 0;
	
	hum |= ((int32_t)readFromRegister(REG_HUM_MSB) << 8);
	hum |= (int32_t)readFromRegister(REG_HUM_LSB);
	
	return BME280_compensate_H_double(hum);
}

// from Bosch Sensortec [datasheet]
double BME280_compensate_T_double(int32_t adc_T)
{
	double var1, var2, T;
	var1 = (((double)adc_T)/16384.0 - ((double)dig_T1)/1024.0) * ((double)dig_T2);
	var2 = ((((double)adc_T)/131072.0 - ((double)dig_T1)/8192.0) * (((double)adc_T)/131072.0 - ((double) dig_T1)/8192.0)) * ((double)dig_T3);
	t_fine = (int32_t)(var1 + var2);
	T = (var1 + var2) / 5120.0;
	return T;
}

double BME280_compensate_P_double(int32_t adc_P)
{
	double var1, var2, p;
	var1 = ((double)t_fine/2.0) - 64000.0;
	var2 = var1 * var1 * ((double)dig_P6) / 32768.0;
	var2 = var2 + var1 * ((double)dig_P5) * 2.0;
	var2 = (var2/4.0)+(((double)dig_P4) * 65536.0);
	var1 = (((double)dig_P3) * var1 * var1 / 524288.0 + ((double)dig_P2) * var1) / 524288.0;
	var1 = (1.0 + var1 / 32768.0)*((double)dig_P1);
	if (var1 == 0.0)
	{
		return 0; // avoid exception caused by division by zero
	}
	p = 1048576.0 - (double)adc_P;
	p = (p - (var2 / 4096.0)) * 6250.0 / var1;
	var1 = ((double)dig_P9) * p * p / 2147483648.0;
	var2 = p * ((double)dig_P8) / 32768.0;
	p = p + (var1 + var2 + ((double)dig_P7)) / 16.0;
	return p;
}
double BME280_compensate_H_double(int32_t adc_H)
{
	double var_H;
	var_H = (((double)t_fine) - 76800.0);
	var_H = (adc_H - (((double)dig_H4) * 64.0 + ((double)dig_H5) / 16384.0 * var_H)) * (((double)dig_H2) / 65536.0 * (1.0 + ((double)dig_H6) / 67108864.0 * var_H * (1.0 + ((double)dig_H3) / 67108864.0 * var_H)));
	var_H = var_H * (1.0 - ((double)dig_H1) * var_H / 524288.0);
	if (var_H > 100.0)
	var_H = 100.0;
	else if (var_H < 0.0)
	var_H = 0.0;
	return var_H;
}

// util functions
boolean writeToRegister(unsigned char registerAddress, unsigned char data)
{
	boolean state = FALSE;
	
	sendStartCondition();
	
	if(sendByte(slaveAddressW) && sendByte(registerAddress) && sendByte(data))
		state = TRUE;
	
	sendStopCondition();
	
	return state;
}

unsigned char readFromRegister(unsigned char registerAddress)
{
	return readRegister(slaveAddressR, registerAddress);
}