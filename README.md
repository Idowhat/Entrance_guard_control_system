# 门禁控制系统

基于STM32微控制器的智能门禁控制系统支持通过刷卡、密码、指纹等方式开锁。

## 元件介绍

- STM32F103ZET6
  
 主控芯片采用基于Cortex-M3架构的STM32F103ZET6，具备ARM V7架构，具有稳定的性能和高处理速度。
  
- TFT-LCD

 项目采用了一块2.8英寸的TFT-LCD显示屏，用于显示相关的提示和状态信息。
 
- ATK-301

ATK-301电容式指纹识别模块是由ALIENTK生产的高性能电容半导体指纹识别模块，用于识别生物信息。
  
- Matrix Keyboard

该方案采用矩阵键盘，用于输入密码、管理指纹以及IC卡的控制操作。

- RC-522

RC-522是一款集成的IC卡读写模块，最大读取距离为10厘米，支持通过SPI、I<sup>2</sup>C和UART协议进行通信。

## 展示

### 界面演示

主界面将显示日期、时间以及相关的欢迎词，如图所示。
<p align = "center">
<img src="https://github.com/Idowhat/img_video/blob/main/img_Entrance_guard/main_interface.png?raw=true" width = "30%" height = "30%" />
</p>

在管理界面输入密码后，可以进行IC卡管理、时间修改、指纹管理和密码管理。

<p align = "center">    
<img  src="https://github.com/Idowhat/img_video/blob/main/img_Entrance_guard/Gen_mana_inter.png?raw=true" hight="600" width="200" />
<img  src="https://github.com/Idowhat/img_video/blob/main/img_Entrance_guard/IC_inter.png?raw=true"  hight="600" width="200" />
<img  src="https://github.com/Idowhat/img_video/blob/main/img_Entrance_guard/modification_time.png?raw=true"  hight="600" width="200" />
<img  src="https://github.com/Idowhat/img_video/blob/main/img_Entrance_guard/finger_mana_inter.png?raw=true" hight="600" width="200" />
</p>

### 开锁演示

接下来将分别演示密码解锁、指纹解锁和IC卡解锁的方法。

<p align = "center">    
<img  src="https://github.com/Idowhat/img_video/blob/main/img_Entrance_guard/passward.png?raw=true" hight="600" width="300" />
<img  src="https://github.com/Idowhat/img_video/blob/main/img_Entrance_guard/finger_pass.png?raw=true"  hight="600" width="300" />
<img  src="https://github.com/Idowhat/img_video/blob/main/img_Entrance_guard/IC_pass.png?raw=true"  hight="600" width="300" />
</p>



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

## Demonstrations

### Interface Demo

The main interface will display the date and time and relevant welcome words as shown in the figure.
<p align = "center">
<img src="https://github.com/Idowhat/img_video/blob/main/img_Entrance_guard/main_interface.png?raw=true" width = "30%" height = "30%" />
</p>

After entering the password into the management interface, you can perform IC card management, time modification, fingerprint management, and password management.

<p align = "center">    
<img  src="https://github.com/Idowhat/img_video/blob/main/img_Entrance_guard/Gen_mana_inter.png?raw=true" hight="600" width="200" />
<img  src="https://github.com/Idowhat/img_video/blob/main/img_Entrance_guard/IC_inter.png?raw=true"  hight="600" width="200" />
<img  src="https://github.com/Idowhat/img_video/blob/main/img_Entrance_guard/modification_time.png?raw=true"  hight="600" width="200" />
<img  src="https://github.com/Idowhat/img_video/blob/main/img_Entrance_guard/finger_mana_inter.png?raw=true" hight="600" width="200" />
</p>

### Unlock Demo

Next is the demonstration of password unlocking, fingerprint unlocking and IC card unlocking methods respectively.

<p align = "center">    
<img  src="https://github.com/Idowhat/img_video/blob/main/img_Entrance_guard/passward.png?raw=true" hight="600" width="300" />
<img  src="https://github.com/Idowhat/img_video/blob/main/img_Entrance_guard/finger_pass.png?raw=true"  hight="600" width="300" />
<img  src="https://github.com/Idowhat/img_video/blob/main/img_Entrance_guard/IC_pass.png?raw=true"  hight="600" width="300" />
</p>
