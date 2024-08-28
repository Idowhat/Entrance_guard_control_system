# Entrance_guard_control_system

The intelligent access control system based on the STM32 microcontroller can open the door lock by swiping the card, password, fingerprint, etc.

## Electronics used in the project

- STM32F103ZET6
  
  The main control chip adopts Cortex-M3 and ARM V7 stable and high processing frequency architecture chip - STM32F103ZET6.
  
- TFT-LCD

  The project adopts a 2.8-inch LCD display to show relevant prompt information.

- ATK-301

  ATK-301 Capacitive Fingerprint Identification Module is a high performance capacitive semiconductor fingerprint identification module from ALIENTK. It is used to recognize biological information
  
- Matrix Keyboard

This solution uses a matrix keypad for entering passwords, managing fingerprints, and managing IC cards.

- RC-522

RC-522 is an integrated circuit read/write module for IC cards at a distance of up to 10cm, which can communicate via SPI, I<sup>2</sup>C protocol and UART protocol.

## demo

The main interface will display the date and time and relevant welcome words as shown in the figure.
<p align = "center">
<img src="https://github.com/Idowhat/img_video/blob/main/imag_Entrance_guard/main_interface.png?raw=true" width = "60%" height = "60%" />
</p>
