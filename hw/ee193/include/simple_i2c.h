#ifndef SIMPLE_I2C_H
#define SIMPLE_I2C_H

#include <stdio.h>
#include "driver/i2c.h"

#define CONFIG_I2C_MASTER_SCL       1
#define CONFIG_I2C_MASTER_SDA       2
#define I2C_MASTER_SCL_IO           CONFIG_I2C_MASTER_SCL      /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           CONFIG_I2C_MASTER_SDA      /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              0                          /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ          400000                     /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000

// https://www.nxp.com/docs/en/data-sheet/PCT2075.pdf
#define PCT2075_SENSOR_ADDR                 0x37        /*!< Target address of the PCT2075 sensor, Table 5, all floating */
/*!< PCT2075 does not have a "who am I" function */

#define MPU9250_PWR_MGMT_1_REG_ADDR         0x6B        /*!< Register addresses of the power managment register */
#define MPU9250_RESET_BIT                   7

esp_err_t pct2075_register_read(uint8_t reg_addr, uint8_t *data, size_t len);
esp_err_t pct2075_register_write_byte(uint8_t reg_addr, uint8_t data); // unused...
esp_err_t i2c_master_init(void);

#endif
