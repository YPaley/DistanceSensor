# DistanceSensor
Project Description
Designed a custom PCB for a distance-sensing system with LCD output.
Implemented ADC-based brightness control via potentiometer, with brightness level displayed on the LCD.


System Architecture:
  Microcontroller (MSP430G2553):
  Clock configuration: MCLK and SMCLK configured to 8MHz
  Peripherals used:
    Timer0_A: configured with a 10us resolution, acts as the main timer, driving the Delay_Timer function and increments the time of flight counter during the ultrasonic sensors echo return window.

    Timer1_A: configured with a 100us resolution to establish a 10ms period. Functions as the PWM to adjust the brightness of an LED mapped to port 2.2 based upon a calculated duty cycle.
  
    ADC10: 10 bit ADC initialized on channel INCH_3 (port 1.3), while using Vcc and Vss as reference voltages. It polls the potentiometer to calculate the 0-100% duty cycle applied to TImer1_A.

    I2C interface (USCI_B0): I2C bus mapped to P1.6(SCL) and P1.7(SDA) to handle communication with the 16x2 LCD screen with a slave address of 0x27

    Interrupts (Port 2): Pin P2.0 configured as input with active pull-down resistor and hardware interrupts enabled. Operates as a state machine to capture the rising and falling edges of an ultrasonic echo signal. Pin2.1 is utilized as the output to fire the trigger pulse.



Power Management:
    Hardware: The power architecture utilized two boost converter modules to set up a low voltage battery source

    3.3V rail(TPS613221A): This regulator steps up the input voltage to 3.3V. it connects to the 3.3VREG header on the main PCB to power the MSP430G2553, potentiometer, MOSFET, and the MCUs internal analog/digial logic. 
          

    5.0V Rail(TPS613222A): This regulator steps up the input voltage to 5V. it connects to the 5VREG header on the main PCB to power the ultrasonic distance sensor and the LCD. 

    Filtering and stability: Both regulators utilize a 4.7uH switching inductor to smooth out current flow and two 22uF bypass capacitors at the input and output nodes to filter voltage ripple. The LC network minimizes high-frequency noise, ensuring stable DC power is delivered to board.



Sensor and Peripheral Integration:
    Distance Sensor (HC-SR04): The MCU initiates a reading by sending a 10us tergger pulse via pin P2.1. The echo return is recived on pin P2.0, where a hardware interrupt tiggers a state machine to measure the pulse width using Timer0_A.

    Display interface (16x2 LCD): The LCD is controlled using I2C, at slave address 0x27. The communication lines are mapped to the hardware I2C pins P1.6(SCL) and P1.7(SDA).

    Analog input and PWN control: A potentiomter voltage divider is read with the internal ADC on pin P1.3(INCH_3). This analog reading is scaled into a percentage from 0 to 100%, setting the duty cycle for the PWM controlled LED on pin P2.2.

    Status indicator(MOSFET LED): Pin P2.5 toggles the gate of a BS170 N-Channel during each iteration of the main execution loop, blinking an LED to indicate that the system is actively polling.
