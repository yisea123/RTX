# CMSIS_RTOS
Best RTOS for Crotex-M


Environment:

Software: KEIL ARM 5.25


Pack:STM32F1XX_DFP、CMSIS
     

Device:


STM32F103RCT6

#V1.0
建立工程模板。
#V1.1
1.增加led的bsp。
2.增加led的500ms闪烁thread。
#V1.2
1.增加UART的bsp。（包含USART1、USART2、USART3、UART4、UART5）。
2.增加UART的发送数据thread。
————thread可根据传参创建任意的USART（1、2、3、4、5）,默认波特率115200。
————支持多个串口多thread。（thread要设置multiple instances）
————封装好层，发送数据采用Message queue,数据结构体封装到Memory pool。在任意线程中，要向串口发送数据，只要
————————发送消息到uart_send_queue。
3.增加一个Virtual Timers：Timer0，计时单位1ms，以支持数据传输时的超时机制。
4.增加UART的接受数据thread。
————thread可根据传参创建任意的USART（1、2、3、4、5）。
————UART开启了接受中断。
————UART 接受数据thread实现了串口透传，默认每帧数据时间间隔大于2ms。（串口接收数据时计时清零并开始计时，计时超过2ms认为一帧数据收完）
————封装好层，接受完的一帧数据填入Message queue,数据结构体封装到Memory pool。在任意线程中，只要等待uart_receive_queue消息即可。
————多个串口接收数据时要注意Memory pool的大小问题。
5.增加UART的功能测试thread。
————实现串口回传。
