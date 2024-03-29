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
### 1.优化串口发送机制，使用串口发送中断，在连续发送字符等待发送完成中断时，线程不占用CPU，提高效率。<br>
### 2.增加硬件定时器TIM2的超时机制。<br>
因为RTOS系统时钟为1ms，若采用Virtual Timer，则定时时间只能为1ms的整数倍，不能实现us级定时需求。<br>
超时机制放弃使用Virtual Timer，采用硬件定时器TIM2，计时单位设置为10us。<br>
串口接受透传采用该机制后，接受完成的判断时间设置为300us，提升串口接收数据的响应速度（原先为2ms）。<br>
超时机制封装为一个thread，为以后SPI、I2C等外设连接超时机制预留统一接口。<br>
### 3.增加按键thread，按键采用外部中断方式，thread中支持按键防抖动，且仅占用几乎很少的CPU资源。<br>

# 2018.5.2
## v1.4
### 1.优化串口收发thread<br>
为每个串口收、发数据threa分配独立的Memory pool、Message queue，从而支持多串口收、发线程。<br>
采用预处理，用到哪几个串口才定义数据资源，节省空间。<br>
目前支持串口为USART1、USART2、USART3、UART4。<br>
### 2.优化按键thread<br>
采用signal方式向线程发送按键信号。<br>
设置了按键焦点线程机制。<br>
当某一线程需要获取按键信号时，将按键当前焦点线程ID设置为自身线程ID，则随后可接收按键signal。<br>
### 3.添加lua解释器<br>
lua输入输出使用USART1。<br>
stdio.h 底层重定向到USART1。<br>
调整了堆栈大小，以解决lua分配内存不足问题。
调整了lua任务堆栈大小，以解决lua任务运行内存不足问题。
部分底层接口待重写与优化。<br>

# 2018.5.3
## v1.5
### 1.优化串口收发thread<br>
为串口收发thread设置发送完成信号，设置当前串口使用焦点线程，实现互斥，保护Memory pool、Message queue，直到发送完毕才释放。<br>
增大串口发送线程堆栈。<br>
优化串口回传的测试线程。<br>
### 2.为各线程统一分配signal值<br>
### 3.优化lua解释器<br>
在串口收发线程机制上重写puts、printf、gets，以适配RTOS，并提升CPU效率。<br>
增大lua线程堆栈。<br>
