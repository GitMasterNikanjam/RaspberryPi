// Example Information:
// For compile and build: sudo g++ -o I2C_LM75A_test I2C_LM75A_test.cpp
// For fun: sudo ./I2C_LM75A_test
// linux/i2c-dev library used for i2c driver.
// Slave device: LM75A Temprature sensor.
// Set LM75A address pin for use address 0x4a.

/*
Temperature Register (Read-Only):
D15 D14     D13     D12     D11     D10     D9      D8      D7      D6  D5  D4  D3  D2  D1  D0
MSB Bit7    Bit6    Bit5    Bit4    Bit3    Bit2    Bit1    LSB     X   X   X   X   X   X   X
D0–D6: Undefined. D7–D15: Temperature Data. One LSB = 0.5°C. Two's complement format.
*/

/*
Configuration Register (Read/Write):
D7  D6  D5  D4-D3   D2      D1      D0
0   0   0   Fault   Queue   O.S.    Polarity Cmp/Int Shutdown
Power up default is with all bits “0” (zero).
D0: Shutdown: When set to 1 the LM75A goes to low power shutdown mode.
D1: Comparator/Interrupt mode: 0 is Comparator mode, 1 is Interrupt mode.
D2: O.S. Polarity: 0 is active low, 1 is active high. O.S. is an open-drain output under all conditions.
D3–D4: Fault Queue: Number of faults necessary to detect before setting O.S. output to avoid false tripping due
to noise. Faults are determine at the end of a conversion. See specified temperature conversion time in the
electrical tables.
*/

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <iostream>

#define LM75A_ADDRESS               0X4A
#define LM75A_REGISTER_DATA         0X00
#define LM75A_REGISTER_CONFIG       0X01
#define LM75A_REGISTER_ID           0X07

using namespace std;

uint8_t bufRead[2];
uint8_t bufWrite[2]; 
int id;
float temp;             // temperature in celcius.

int main() {

    const char *devicePath = "/dev/i2c-1";  // Adjust the device path based on your Raspberry Pi configuration
    int deviceAddress = LM75A_ADDRESS;  // Replace with your actual device address
    
    // Open the I2C device
    int LM75_H = open(devicePath, O_RDWR);      // i2c device handler

    if (LM75_H == -1) {
        std::cerr << "Failed to open I2C device" << std::endl;
        return 1;
    }

    // Set the I2C slave address
    if (ioctl(LM75_H, I2C_SLAVE, deviceAddress) == -1) {
        std::cerr << "Failed to set I2C slave address" << std::endl;
        close(LM75_H);
        return 1;
    }
    
    // Set Config register to 0x00 value.
    bufWrite[0] = LM75A_REGISTER_CONFIG;
    bufWrite[1] = 0x00;
    
    if (write(LM75_H, &bufWrite, 2) != 2) {
        std::cerr << "Failed to write to I2C device" << std::endl;
        close(LM75_H);
        return 1;
    }

    // Read ID Register:
    bufWrite[0] = LM75A_REGISTER_ID;
    write(LM75_H, &bufWrite, 1);

    if (read(LM75_H, &bufRead, 1) != 1) {
        std::cerr << "Failed to read from I2C device" << std::endl;
        close(LM75_H);
        id = bufRead[0];
        return 1;
    }

    // Read Temperature:
    bufWrite[0] = LM75A_REGISTER_DATA;
    write(LM75_H, &bufWrite, 1);
    read(LM75_H, &bufRead, 2);
    temp = (((int)bufRead[0] << 8 | (int)bufRead[1]) >> 7);
    temp = temp/2.0;

    std::cout << "Read Temp: " << temp << std::endl;

    // Close I2C device
    close(LM75_H);

    return 0;
}