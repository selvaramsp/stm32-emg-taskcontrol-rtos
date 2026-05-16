Project Description

This project implements an **EMG (Electromyography)-based embedded control system** on the **STM32F401RE microcontroller**, demonstrating a hands-free human-machine interaction mechanism combined with a simulated secure firmware update workflow.

The system uses an **EMG sensor connected to the ADC input (PA0)** of the STM32 to detect muscle activity in real time. Muscle contractions are converted into analog voltage signals, digitized using the onboard ADC, and processed by embedded firmware.

At startup, the system enters an **IDLE monitoring state**, where EMG signals are sampled periodically every **500 ms**. The acquired analog value is normalized between **0.0 and 1.0** using the ADC interface.

A predefined threshold is used for gesture detection:

- **EMG_THRESHOLD = 0.30**
- If **EMG signal < 0.30**, the system remains in monitoring mode.
- If **EMG signal ≥ 0.30**, the system interprets this as intentional muscle activation (e.g., fist clench).

To avoid repeated triggering from continuous muscle activation, a state flag (`above`) is used:

- Trigger occurs only when the signal crosses the threshold from below.
- Continuous high EMG values do not retrigger the event.
- Once the signal drops below threshold, the system rearms for the next trigger.

### Bootloader / Update Simulation Logic

When a valid EMG trigger is detected:

1. EMG trigger confirmation message is sent via UART.
2. LED1 is immediately turned OFF.
3. A simulated firmware update delay of **2 seconds** is executed.
4. Firmware update completion message is transmitted.
5. System transitions from **IDLE → UPDATED state**.

This demonstrates a simplified embedded bootloader handover concept where biometric input replaces traditional hardware buttons for firmware control.

### Updated State Behavior

Once the firmware update state is entered:

- System permanently switches to **UPDATED mode**
- LED2 begins blinking every **300 ms**
- This visually indicates successful firmware update completion and execution of the updated application.

Blink logic:

- LED2 toggles ON/OFF every 300 ms
- Implemented using non-blocking timing logic with `Kernel::Clock`

### UART Debug Monitoring

The system continuously transmits runtime debug information over UART (**115200 baud**) including:

- Real-time EMG readings
- Trigger detection messages
- Firmware update status
- System state transitions

Example output:

EMG:0.172  
EMG:0.245  
EMG:0.335  
EMG UPDATE TRIGGERED  
GETTING UPDATED  
FIRMWARE UPDATE COMPLETE  

### Hardware Components

- STM32F401RE Nucleo Development Board
- EMG Sensor Module
- LEDs for state indication
- Breadboard and jumper wires
- UART serial interface

### Software Concepts Demonstrated

This project demonstrates practical embedded systems concepts including:

- ADC-based sensor interfacing
- Real-time analog signal acquisition
- Threshold-based gesture detection
- State machine implementation
- UART serial debugging
- Timer-based event scheduling
- GPIO control
- Embedded firmware design
- Human-machine interaction using biosignals

### Applications

Potential applications include:

- Assistive wearable systems
- Gesture-controlled embedded devices
- Biomedical human-machine interfaces
- Hands-free firmware control systems
- Smart prosthetic control concepts
