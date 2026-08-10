# DistanceSensor
Project Description
Designed a custom PCB for a distance-sensing system with LCD output.
Implemented ADC-based brightness control via potentiometer, with brightness level displayed on the LCD.

System Architecture:
  Microcontroller (MSP430G2553):
  Clock configuration: MCLK and SMCLK configured to 8MHz
  Peripherals used:
    Timer0_A: configured with a 10us resolution, acts as the main timer, driving the Delay_Timer               function and incremements the time of flight counter during the ultrasonic sensors echo return           window.

    Timer1_A: configured with a 100us resolution to establish a 10ms period. Functions as the PWM to           adjust the brightness of an LED mapped to port 2.2 based upon a calculated duty cycle.
  
    ADC10: 10 bit ADC initialized on channel INCH_3 (port 1.3), while using Vcc and Vss as reference           voltages. It polls the potentiometer to calculate the 0-100% duty cycle applied to TImer1_A.

    I2C interface (USCI_B0): I2C bus mapped to P1.6(SCL) and P1.7(SDA) to handle communication with the        16x2 LCD screen with a slave address of 0x27

    Interrupts (Port 2): 
