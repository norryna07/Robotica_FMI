/**
 *  mpl3115a2.c - MPL3115A2 library for ATMega324P
 *  Datasheet: https://www.nxp.com/docs/en/data-sheet/MPL3115A2.pdf
 */

#include "mpl3115a2.h"
#include <util/delay.h>

void mpl3115a2_init(void)
{
    // Initialize MPL3115A2 with altimetry and wait for data to be ready
    twi_start();
    twi_write(MPL3115A2_ADDRESS << 1);
    twi_write(MPL3115A2_PT_DATA_CFG);
    twi_write(0x07);

    twi_start();
    twi_write(MPL3115A2_ADDRESS << 1);
    twi_write(MPL3115A2_CTRL_REG1);
    twi_write(0x39);

    twi_start();
    twi_write(MPL3115A2_ADDRESS << 1);
    twi_write(MPL3115A2_STATUS);

    twi_start();
    twi_write((MPL3115A2_ADDRESS << 1) | 0x01);

    // Wait for data ready.
    uint8_t sta = 0x00;
    while (!(sta & 0x08))
    {
        twi_read_ack(&sta);
    }
    twi_read_nack(&sta);

	// TODO 3.1: stop I2C transaction
    twi_stop();

}

void mpl3115a2_read_temperature(uint8_t *temperature)
{
    // TODO 3.2: Read the temperature from the sensor

    *temperature = mpl3115a2_read_byte(MPL3115A2_T_MSB);
    
}
void mpl3115a2_read_pressure(uint32_t *pressure)
{
    // TODO 3.2: Read the pressure from the sensor
    uint8_t msb = mpl3115a2_read_byte(MPL3115A2_P_MSB);
    uint8_t csb = mpl3115a2_read_byte(MPL3115A2_P_CSB);
    uint8_t lsb = mpl3115a2_read_byte(MPL3115A2_P_LSB);
    *pressure = ((msb << 12) | (csb << 4) | (lsb >> 4)) >> 2;
}

uint8_t mpl3115a2_read_byte(uint8_t reg) {
    twi_start();
    twi_write(MPL3115A2_ADDRESS << 1);
    twi_write(MPL3115A2_STATUS);

    twi_start();
    twi_write((MPL3115A2_ADDRESS << 1) | 0x01);

    // Wait for data ready.
    uint8_t sta = 0x00;
    while (!(sta & 0x08))
    {
        twi_read_ack(&sta);
    }
    twi_read_nack(&sta);

	// TODO 3.1: stop I2C transaction
    twi_stop();

    twi_start();
    
    /* Write SLA_W on the I2C bus because we're going to send the register address next */
    twi_write(MPL3115A2_ADDRESS << 1);
    
    /* Write the register address */
    twi_write(reg);
    
    /* Send REPEATING START condition */
    twi_start();
    
    /* Write SLA_R on the I2C bus because we're going to read */
    twi_write((MPL3115A2_ADDRESS << 1) | 1);
    
    /* Read from the sensor. The last read must be sent with NACK */
    uint8_t data = 0x00;
    twi_read_nack(&data);
    
    /* If we're not going to do anything next, send STOP condition */
    twi_stop();  

    return data;
}