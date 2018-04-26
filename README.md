# CMSIS_RTOS
## Best RTOS for Crotex-M
## Environment:
## Software: KEIL ARM 5.25
## Pack:STM32F1XX_DFP、CMSIS
## Device:
## STM32F103RCT6

# 2018.4.24
## V1.0
### 建立工程模板。
## V1.1
### 1.增加led的bsp。<br> 
### 2.增加led的500ms闪烁thread。

# 2018.4.25
## V1.2
### 1.增加UART的bsp。（包含USART1、USART2、USART3、UART4、UART5）。<br>
### 2.增加UART的发送数据thread。
thread可根据传参创建任意的USART（1、2、3、4、5）,默认波特率115200。<br>
支持多个串口多thread。（thread要设置multiple instances）<br>
封装好层，发送数据采用Message queue,数据结构体封装到Memory pool。在任意线程中，要向串口发送数据，只要<br>
发送消息到uart_send_queue。
### 3.增加一个Virtual Timers：Timer0，计时单位1ms，以支持数据传输时的超时机制。<br>
### 4.增加UART的接受数据thread。<br>
thread可根据传参创建任意的USART（1、2、3、4、5）。<br>
UART开启了接受中断。<br>
UART 接受数据thread实现了串口透传，默认每帧数据时间间隔大于2ms。（串口接收数据时计时清零并开始计时，计时超过2ms认为一帧数据收完）<br>
封装好层，接受完的一帧数据填入Message queue,数据结构体封装到Memory pool。在任意线程中，只要等待uart_receive_queue消息即可。<br>
多个串口接收数据时要注意Memory pool的大小问题。<br>
### 5.增加UART的功能测试thread。<br>
实现串口回传。<br>

# 2018.4.26
## v1.3
### 1.优化串口发送机制，使用串口发送中断，在连续发送字符等待发送完成中断时，线程不占用CPU，提高效率。
### 2.增加硬件定时器TIM2的超时机制。
因为RTOS系统时钟为1ms，若采用Virtual Timer，则定时时间只能为1ms的整数倍，不能实现us级定时需求。<br>
超时机制放弃使用Virtual Timer，采用硬件定时器TIM2，计时单位设置为10us。<br>
串口接受透传采用该机制后，接受完成的判断时间设置为300us，提升串口接收数据的响应速度（原先为2ms）。<br>
超时机制封装为一个thread，为以后SPI、I2C等外设连接超时机制预留统一接口。<br>
### 3.增加按键thread，按键采用外部中断方式，thread中支持按键防抖动，且仅占用几乎很少的CPU资源。

