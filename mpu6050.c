#include <mpu6050.h>
#include <main.h>
#include <stdio.h>

extern I2C_HandleTypeDef hi2c1;

void mpu6050_init(){
    HAL_StatusTypeDef ret =  HAL_I2C_IsDeviceReady(&hi2c1,(DEVICE_ADDRESS << 1) + 0, 1, 100 );
    if (ret == HAL_OK)
    {
        printf("The device is ready \n");
    }
    else{
        printf("The device is not ready. Check cables \n");
    }
    uint8_t temp_data = FS_GYRO_500;
    ret = HAL_I2C_Mem_Write(&hi2c1, (DEVICE_ADDRESS << 1) + 0, REG_CONFIG_GYRO, 1, &temp_data, 1, 100);
    if (ret == HAL_OK)
    {
        printf("Writing to register 27 \n");
    }
    else{
        printf("Failed writing to the register \n");
    }
}