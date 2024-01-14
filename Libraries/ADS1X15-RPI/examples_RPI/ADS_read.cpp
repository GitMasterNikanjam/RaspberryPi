// sudo g++ -o ADS_read ADS_read.cpp ../ADS1X15.cpp
// sudo ./ADS_read

#include <iostream>
#include "../ADS1X15.h"
#include <thread>

using namespace std;

#define ADS_ADDRESS         0X48
#define I2C_DEVICE_PATH     (const char*)"/dev/i2c-1"

ADS1115 ADS(ADS_ADDRESS, I2C_DEVICE_PATH);

int main()
{
    ADS.setGain(1);

    if (ADS.begin() != 1)
    {
        cout<< "ADS not recognized!"<< endl;
        return 1;
    }
        

    while(1)
    {
        int16_t val_0 = ADS.readADC(0);  
        int16_t val_1 = ADS.readADC(1);  
        int16_t val_2 = ADS.readADC(2);  
        int16_t val_3 = ADS.readADC(3);  

        float f = ADS.toVoltage(1);  // voltage factor

        cout<< val_0<< ", ";
        cout<< val_1<< ", ";
        cout<< val_2<< ", ";
        cout<< val_3<< endl;

        //std::this_thread::sleep_for(1000ms);
    }
    

    return 0;
}