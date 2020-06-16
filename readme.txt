Версия 1.0

Автор: https://github.com/zapta/misc/tree/master/paste_injector

BOM:
Name	Value	Comment
1x 3.3K	R2	0805
1x 10K	R3	0805
2x 0.1uf	C3 C4	ceramic 25V 0805
1x LED Red 0805	D1	
1x Micro USB connector ZX62RD-AB-5P8		
1x Trimpot 10K 3362P-1-103LF		
1x ATMEGA328P TQFP32	U1	
1x Resonator 16Mhz AWSCR-16.00CV-T	Q1	
1x ULN2003A SOIC	U2	
2x Push Button		
1x Tantalum cap 10uF 1206	C1	
1x 5V bipolar stepper motor 28BYJ-48		

Как прошить:
1. Любым программатором загружается bootloader (HEX файл и фьюзы прилагаются). Самой простой вариант прошить через USB Arduino NANO и "сдуть" с нее чип.
2. Впаивается чип на плату.
3. Заливается INO файл из Arduino IDE (как Arduino NANO) с помощью USB-UART преобразователя (FTDI).