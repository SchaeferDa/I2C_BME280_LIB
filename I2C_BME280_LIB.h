/*
 * I2C_BME280_LIB.h
 *
 * Created: 04.03.2019 17:29:54
 * Author: Daniel Schäfer
 * Contact: code@schaeferservices.de
 */ 
#ifndef BME280_H_
#define BME280_H_

void BME280_init(unsigned char address);
void BME280_soft_reset();
double BME280_get_temperature();
double BME280_get_pressure();
double BME280_get_humidity();
void BME280_calibrate_temperature();
void BME280_calibrate_pressure();
void BME280_calibrate_humidity();

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
boolean BME280_set_mode(unsigned char mode);
boolean BME280_set_sleep_mode();
boolean BME280_set_forced_mode();
boolean BME280_set_normal_mode();
unsigned char BME280_get_mode();

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
boolean BME280_set_filter_coefficient(unsigned char filter_coefficient);
boolean BME280_set_filter_coefficient_off();
boolean BME280_set_filter_coefficient_2();
boolean BME280_set_filter_coefficient_4();
boolean BME280_set_filter_coefficient_8();
boolean BME280_set_filter_coefficient_16();
unsigned char BME280_get_filter_coefficient();

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
boolean BME280_set_temperature_oversampling(unsigned char temperature_oversampling);
boolean BME280_set_temperature_oversampling_off();
boolean BME280_set_temperature_oversampling_1();
boolean BME280_set_temperature_oversampling_2();
boolean BME280_set_temperature_oversampling_4();
boolean BME280_set_temperature_oversampling_8();
boolean BME280_set_temperature_oversampling_16();
unsigned char BME280_get_temperature_oversampling();

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
boolean BME280_set_pressure_oversampling(unsigned char pressure_oversampling);
boolean BME280_set_pressure_oversampling_off();
boolean BME280_set_pressure_oversampling_1();
boolean BME280_set_pressure_oversampling_2();
boolean BME280_set_pressure_oversampling_4();
boolean BME280_set_pressure_oversampling_8();
boolean BME280_set_pressure_oversampling_16();
unsigned char BME280_get_pressure_oversampling();

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
boolean BME280_set_humidity_oversampling(unsigned char humidity_oversampling);
boolean BME280_set_humidity_oversampling_off();
boolean BME280_set_humidity_oversampling_1();
boolean BME280_set_humidity_oversampling_2();
boolean BME280_set_humidity_oversampling_4();
boolean BME280_set_humidity_oversampling_8();
boolean BME280_set_humidity_oversampling_16();
unsigned char BME280_get_humidity_oversampling();

#endif /* BME280_H_ */