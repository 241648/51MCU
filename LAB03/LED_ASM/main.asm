;
; @time: 2019-10-10 
; @author: Jeremy.Zhang
; @function: LED blinks based on assemble program
;


; pins redifine, low works(����������, �͵�ƽ��Ч)
LED1 BIT P2.4
LED2 BIT P2.5
LED3 BIT P2.6
LED4 BIT P2.7
BEEP BIT P1.0


; EQU(Equal) assign(��ֵ)
DelayTimes_100MS EQU 6FH


; program start(������ʼ) 
ORG 0000H                           ;���������ʼ���е�ַ 
LJMP START                          ;��ת��'START'��Ƿ����������� 


ORG 0100H
START:
    MOV SP, #70H                    ;���ö�ջ, Ŀ��: ����ֲ��������жϷ��� 
START1:
    LCALL LEDRUN                    ;����LED���� 
    LJMP  START1                    ;����'START1'��Ƿ�, ������while(1)ѭ�� 


; Delay 100Ms function(��ʱ100MS����)
Delay100MS:
    MOV R7, DelayTimes_100MS
    
    Delay100MS_1:  MOV R6, #10
    Delay100MS_2:  MOV R5, #150
    Delay100MS_3:  MOV R4, #200
    Delay100MS_4:  DJNZ R4, Delay100MS_4
                   DJNZ R5, Delay100MS_3
                   DJNZ R6, Delay100MS_2
                   DJNZ R7, Delay100MS_1
RET                                 


; LED blinks function(LED����ƺ���)
LEDRUN: 
    CLR   LED1                       ;���õ͵�ƽ 
    SETB  LED2                       ;���øߵ�ƽ 
    SETB  LED3
    SETB  LED4
    CLR   BEEP
    MOV   DelayTimes_100MS, #10      ;������Ҫ10����ʱ100MS 
    LCALL Delay100MS                 ;����Delay100MS����
   
    SETB  LED1                       
    CLR   LED2
    SETB  LED3
    SETB  LED4 
    SETB  BEEP                     
    MOV   DelayTimes_100MS, #10       
    LCALL Delay100MS 

    SETB  LED1                       
    SETB  LED2
    CLR   LED3
    SETB  LED4
    CLR   BEEP                      
    MOV   DelayTimes_100MS, #10       
    LCALL Delay100MS 

    SETB  LED1                       
    SETB  LED2
    SETB  LED3
    CLR   LED4
    SETB  BEEP                      
    MOV   DelayTimes_100MS, #10       
    LCALL Delay100MS 
                 
RET                                  ;����������Ƿ� 
    
END 