> **Content**  
>**[1 Overview](#1-Overview)**  
>**[2 Features](#2-Features)**  
>**[3 How to measure](#3-How-to-measure)**  
>**[4 Usage](#4-Usage)**  
>**[5 Used Libraries](#5-Used-Libraries)**  
>**[6 Used Literature](#6-Used-Literature)**  

## 1 Overview
This is a static library for Bosch Sensortec BME280 with I²C for Atmel ATmega328P.

This is an education project.

This project was developed with Atmel Studio 7.0 IDE.


> **Notice**  
> This library was tested on an ATmega328P with Bosch Sensortec BMP280.  
> Only measurement of temperature and pressure was tested.  
>   
> **Use this library at your own risk.**  

> **Important**  
> The I²C-Library [[Section 5.1]](#51-I2C_LIB) must be connected/enclosed!  

## 2 Features
- Measurement of current temperature in *°C*
    - accurancy of a tenth
    - variable oversampling

- Measurement of current pressure in *Pa*
    - accurancy of a third
    - variable oversampling

- Measurement of current humidity in *%rh*
    - accurancy of a tenth
    - variable oversampling

- all data transmissons through I²C (given I²C-library)

## 3 How to measure
### 3.1 How to measure temperature
1. Initialize BME280 with I²C-Address [[Section 4.01]](#401-initialize-bme280-with-ic-address)
2. Activate operating mode [[Section 4.09]](#409-set-operating-mode-on-BME280)
3. Set standby time [[Section 4.10]](#410-set-standby-time-on-BME280)
4. Set filter coefficient [[Section 4.11]](#411-set-filter-coefficient-on-BME280)
5. Set temperature oversampling [[Section 4.12]](#412-set-temperature-oversampling-on-BME280)
6. Calibrate temperature [[Section 4.06]](#406-calibrate-temperatur-on-BME280)

### 3.2 How to measure pressure
1. Initialize BME280 with I²C-Address [[Section 4.01]](#401-initialize-bme280-with-ic-address)
2. Activate operating mode [[Section 4.09]](#409-set-operating-mode-on-BME280)
3. Set standby time [[Section 4.10]](#410-set-standby-time-on-BME280)
4. Set filter coefficient [[Section 4.11]](#411-set-filter-coefficient-on-BME280)
5. Set pressure oversampling [[Section 4.13]](#413-set-pressure-oversampling-on-BME280)
6. Calibrate pressure [[Section 4.07]](#407-calibrate-pressure-on-BME280)

### 3.3 How to measure humidity
1. Initialize BME280 with I²C-Address [[Section 4.01]](#401-initialize-bme280-with-ic-address)
2. Activate operating mode [[Section 4.09]](#409-set-operating-mode-on-BME280)
3. Set standby time [[Section 4.10]](#410-set-standby-time-on-BME280)
4. Set filter coefficient [[Section 4.11]](#411-set-filter-coefficient-on-BME280)
5. Set humidity oversampling [[Section 4.14]](#414-set-humidity-oversampling-on-BME280)
6. Calibrate humidity [[Section 4.08]](#408-calibrate-humidity-on-BME280)

> **Notice**  
> Configuration values depend on operation of BME280.  
> ⇾ Datasheet BME280 [[Section 6.1]](#61-Datasheet-Bosch-Sensortec-BME280) 

## 4 Usage

### 4.01 initialize BME280 with I²C-Address
```c
void BME280_init(unsigned char address);
```

### 4.02 soft reset BME280
```c
void BME280_soft_reset();
```

### 4.03 get stored temperature as *double* [14.02 is equal to 14.02°C]
```c
double BME280_get_temperature();
```

### 4.04 get stored pressure as *double* [123.45 is equal to 123.45 pa]
```c
double BME280_get_pressure();
```

### 4.05 get stored humidity as *double* [12.34 is equal to 12.34 %rh]
```c
double BME280_get_humidity();
```

### 4.06 calibrate temperatur on BME280
```c
void BME280_calibrate_temperature();
```

### 4.07 calibrate pressure on BME280
```c
void BME280_calibrate_pressure();
```

### 4.08 calibrate humidity on BME280
```c
void BME280_calibrate_humidity();
```

### 4.09 set operating mode on BME280
```c
+--------------+-------------+
|     data     |     mode    |
+--------------+-------------+
|     0x00     |  sleep mode |
+--------------+-------------+
| 0x01 or 0x02 | forced mode |
+--------------+-------------+
|     0x03     | normal mode |
+--------------+-------------+

boolean BME280_set_mode(unsigned char mode);
```

#### 4.09.1 activate sleep mode on BME280
```c
boolean BME280_set_sleep_mode();
```

#### 4.09.2 activate forced mode on BME280
```c
boolean BME280_set_forced_mode();
```

#### 4.09.3 activate normal mode on BME280
```c
boolean BME280_set_normal_mode();
```

#### 4.09.4 get mode as *unsigned char* from BME280
```c
unsigned char BME280_get_mode();
```

### 4.10 set standby time on BME280
```c
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

boolean BME280_set_standby_time(unsigned char standby_time);
```
#### 4.10.1 set standby time to 0.5ms
```c
boolean BME280_set_standby_time_0_5();
```

#### 4.10.2 set standby time to 10ms
```c
boolean BME280_set_standby_time_10();
```

#### 4.10.3 set standby time to 20ms
```c
boolean BME280_set_standby_time_20();
```

#### 4.10.4 set standby time to 62.5ms
```c
boolean BME280_set_standby_time_62_5();
```

#### 4.10.5 set standby time to 125ms
```c
boolean BME280_set_standby_time_125();
```

#### 4.10.6 set standby time to 250ms
```c
boolean BME280_set_standby_time_250();
```

#### 4.10.7 set standby time to 500ms
```c
boolean BME280_set_standby_time_500();
```

#### 4.10.8 set standby time to 1000ms
```c
boolean BME280_set_standby_time_1000();
```

#### 4.10.9 get standby time as *unsigned char* rom BME280
```c
unsigned char BME280_get_standby_time();
```

### 4.11 set filter coefficient on BME280
```c
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

boolean BME280_set_filter_coefficient(unsigned char filter_coefficient);
```

#### 4.11.1 set filter coefficient to off
```c
boolean BME280_set_filter_coefficient_off();
```

#### 4.11.2 set filter coefficient to 2
```c
boolean BME280_set_filter_coefficient_2();
```

#### 4.11.3 set filter coefficient to 4
```c
boolean BME280_set_filter_coefficient_4();
```

#### 4.11.4 set filter coefficient to 8
```c
boolean BME280_set_filter_coefficient_8();
```

#### 4.11.5 set filter coefficient to 16
```c
boolean BME280_set_filter_coefficient_16();
```

#### 4.11.6 get filter coefficient as *unsigned char* from BME280
```c
unsigned char BME280_get_filter_coefficient();
```

### 4.12 set temperature oversampling on BME280
```c
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

boolean BME280_set_temperature_oversampling(unsigned char temperature_oversampling);
```

#### 4.12.1 set temperature oversampling to off [output 0x80000]
```c
boolean BME280_set_temperature_oversampling_off();
boolean BME280_set_temperature_oversampling_1();
boolean BME280_set_temperature_oversampling_2();
boolean BME280_set_temperature_oversampling_4();
boolean BME280_set_temperature_oversampling_8();
boolean BME280_set_temperature_oversampling_16();
unsigned char BME280_get_temperature_oversampling();
```

#### 4.12.2 set temperature oversampling to 1
```c
boolean BME280_set_temperature_oversampling_1();
```

#### 4.12.3 set temperature oversampling to 2
```c
boolean BME280_set_temperature_oversampling_2();
```

#### 4.12.4 set temperature oversampling to 4
```c
boolean BME280_set_temperature_oversampling_4();
```

#### 4.12.5 set temperature oversampling to 8
```c
boolean BME280_set_temperature_oversampling_8();
```

#### 4.12.6 set temperature oversampling to 16
```c
boolean BME280_set_temperature_oversampling_16();
```

#### 4.12.7 get temperature oversampling as *unsigned char* from BME280
```c
unsigned char BME280_get_temperature_oversampling();
```

### 4.13 set pressure oversampling on BME280
```c
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

boolean BME280_set_pressure_oversampling(unsigned char pressure_oversampling);
```

#### 4.13.1 set pressure oversampling to off [output 0x80000]
```c
boolean BME280_set_pressure_oversampling_off();
boolean BME280_set_pressure_oversampling_1();
boolean BME280_set_pressure_oversampling_2();
boolean BME280_set_pressure_oversampling_4();
boolean BME280_set_pressure_oversampling_8();
boolean BME280_set_pressure_oversampling_16();
unsigned char BME280_get_pressure_oversampling();
```

#### 4.13.2 set pressure oversampling to 1
```c
boolean BME280_set_pressure_oversampling_1();
```

#### 4.13.3 set pressure oversampling to 2
```c
boolean BME280_set_pressure_oversampling_2();
```

#### 4.13.4 set pressure oversampling to 4
```c
boolean BME280_set_pressure_oversampling_4();
```

#### 4.13.5 set pressure oversampling to 8
```c
boolean BME280_set_pressure_oversampling_8();
```

#### 4.13.6 set pressure oversampling to 16
```c
boolean BME280_set_pressure_oversampling_16();
```

#### 4.13.7 get pressure oversampling as *unsigned char* from BME280
```c
unsigned char BME280_get_pressure_oversampling();
```

### 4.14 set humidity oversampling on BME280
```c
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

boolean BME280_set_humidity_oversampling(unsigned char humidity_oversampling);
```

#### 4.14.1 set humidity oversampling to off [output 0x80000]
```c
boolean BME280_set_humidity_oversampling_off();
boolean BME280_set_humidity_oversampling_1();
boolean BME280_set_humidity_oversampling_2();
boolean BME280_set_humidity_oversampling_4();
boolean BME280_set_humidity_oversampling_8();
boolean BME280_set_humidity_oversampling_16();
unsigned char BME280_get_humidity_oversampling();
```

#### 4.14.2 set humidity oversampling to 1
```c
boolean BME280_set_humidity_oversampling_1();
```

#### 4.14.3 set humidity oversampling to 2
```c
boolean BME280_set_humidity_oversampling_2();
```

#### 4.14.4 set humidity oversampling to 4
```c
boolean BME280_set_humidity_oversampling_4();
```

#### 4.14.5 set humidity oversampling to 8
```c
boolean BME280_set_humidity_oversampling_8();
```

#### 4.14.6 set humidity oversampling to 16
```c
boolean BME280_set_humidity_oversampling_16();
```

#### 4.14.7 get humidity oversampling as *unsigned char* from BME280
```c
unsigned char BME280_get_humidity_oversampling();
```

## 5 Used Libraries
### 5.1 I2C_LIB
- [I2C_LIB [v1.0]](https://github.com/schaeferservices/I2C_LIB/releases)

## 6 Used Literature
### 6.1 Datasheet Bosch Sensortec BME280
- [Datasheet Bosch Sensortec BME280](https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BME280-DS002.pdf)

### 6.2 Datasheet Atmel ATmega328P
- [Datasheet Atmel ATmega328P](https://cdn-shop.adafruit.com/datasheets/ATMEGA328P.pdf)
