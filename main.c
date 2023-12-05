#include "mbed.h"
#include "MPU6050.h"

// Pin connections
I2C i2c(D14, D15); // SDA, SCL
MPU6050 mpu(i2c);

InterruptIn userButton(USER_BUTTON); // User button for manual reset
DigitalOut myled(LED1); // On-board LED

// Thresholds for fall detection
const float accel_threshold = 2.5; // Threshold for a fall detection in g
const int stillness_delay = 5000; // Time in milliseconds to wait for stillness

// Function to handle fall detection
void fall_detected() {
    myled = 1; // Turn on the LED as a fall indicator
    wait_ms(stillness_delay);
    myled = 0;
}

int main() {
    mpu.initialize();
    userButton.mode(PullUp); // Set internal pull-up resistor for button

    while (1) {
        int16_t ax, ay, az;
        mpu.getAcceleration(&ax, &ay, &az);

        // Convert raw accelerometer data to g
        float ax_g = ax / 16384.0;
        float ay_g = ay / 16384.0;
        float az_g = az / 16384.0;

        // Calculate magnitude of acceleration vector
        float magnitude = sqrt(ax_gax_g + ay_gay_g + az_g*az_g);

        if (magnitude > accel_threshold) {
            fall_detected();
        }

        if (userButton == 0) { // If button is pressed, reset
            myled = 0;
        }

        wait_ms(100); // Adjust the sampling rate as needed

        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 0);
        HAL_Delay(30000);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
        HAL_Delay(500);
    }

    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    while (1) {
        // Check if the button is pressed
        if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET) {
        } 
        else {
        }
    }
}

void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable /
    __HAL_RCC_GPIOC_CLK_ENABLE();

    /Configure GPIO pin : PC13 (User Button) */
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}