EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:24lc16b
LIBS:74hc164
LIBS:74hc165
LIBS:74hc595
LIBS:lsm303dlhc
LIBS:my_comps
LIBS:tc1047a
LIBS:crystal-4pin
LIBS:micro-usb-b
LIBS:cam-chassis-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "16 apr 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATMEGA8-AI IC1
U 1 1 552197F0
P 5000 2150
F 0 "IC1" H 4250 3350 40  0000 L BNN
F 1 "ATMEGA8-AI" H 5500 600 40  0000 L BNN
F 2 "Housings_QFP:TQFP-32_7x7mm_Pitch0.8mm" H 5000 2150 30  0000 C CIN
F 3 "" H 5000 2150 60  0000 C CNN
	1    5000 2150
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 55219850
P 1100 1350
F 0 "C1" H 1100 1450 40  0000 L CNN
F 1 "18p" H 1106 1265 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 1138 1200 30  0000 C CNN
F 3 "~" H 1100 1350 60  0000 C CNN
	1    1100 1350
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 5521986C
P 1100 3550
F 0 "C2" H 1100 3650 40  0000 L CNN
F 1 "18p" H 1106 3465 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 1138 3400 30  0000 C CNN
F 3 "~" H 1100 3550 60  0000 C CNN
	1    1100 3550
	1    0    0    -1  
$EndComp
NoConn ~ 1500 1750
NoConn ~ 1500 3150
Text Label 3750 1850 0    60   ~ 0
xtal1
Text Label 3750 2050 0    60   ~ 0
xtal2
Text Label 1150 3250 0    60   ~ 0
xtal1
Text Label 1150 1650 0    60   ~ 0
xtal2
$Comp
L GND #PWR01
U 1 1 552198C4
P 1100 3950
F 0 "#PWR01" H 1100 3950 30  0001 C CNN
F 1 "GND" H 1100 3880 30  0001 C CNN
F 2 "" H 1100 3950 60  0000 C CNN
F 3 "" H 1100 3950 60  0000 C CNN
	1    1100 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 552198D1
P 700 1150
F 0 "#PWR02" H 700 1150 30  0001 C CNN
F 1 "GND" H 700 1080 30  0001 C CNN
F 2 "" H 700 1150 60  0000 C CNN
F 3 "" H 700 1150 60  0000 C CNN
	1    700  1150
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 55219931
P 2200 1750
F 0 "C3" H 2200 1850 40  0000 L CNN
F 1 "100n" H 2206 1665 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 2238 1600 30  0000 C CNN
F 3 "~" H 2200 1750 60  0000 C CNN
	1    2200 1750
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR03
U 1 1 55219989
P 4000 1650
F 0 "#PWR03" H 4000 1650 30  0001 C CNN
F 1 "GND" H 4000 1580 30  0001 C CNN
F 2 "" H 4000 1650 60  0000 C CNN
F 3 "" H 4000 1650 60  0000 C CNN
	1    4000 1650
	1    0    0    -1  
$EndComp
Text Label 3750 1150 0    60   ~ 0
rst
$Comp
L R R3
U 1 1 552199CE
P 2200 1100
F 0 "R3" V 2280 1100 40  0000 C CNN
F 1 "30k" V 2207 1101 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 2130 1100 30  0000 C CNN
F 3 "~" H 2200 1100 30  0000 C CNN
	1    2200 1100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 55219A0A
P 2200 2150
F 0 "#PWR04" H 2200 2150 30  0001 C CNN
F 1 "GND" H 2200 2080 30  0001 C CNN
F 2 "" H 2200 2150 60  0000 C CNN
F 3 "" H 2200 2150 60  0000 C CNN
	1    2200 2150
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR05
U 1 1 55219A29
P 2200 650
F 0 "#PWR05" H 2200 750 30  0001 C CNN
F 1 "VCC" H 2200 750 30  0000 C CNN
F 2 "" H 2200 650 60  0000 C CNN
F 3 "" H 2200 650 60  0000 C CNN
	1    2200 650 
	1    0    0    -1  
$EndComp
Text Label 2300 1450 0    60   ~ 0
rst
$Comp
L C C4
U 1 1 55219ABE
P 2200 2850
F 0 "C4" H 2200 2950 40  0000 L CNN
F 1 "100n" H 2206 2765 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 2238 2700 30  0000 C CNN
F 3 "~" H 2200 2850 60  0000 C CNN
	1    2200 2850
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR06
U 1 1 55219AC5
P 2200 3250
F 0 "#PWR06" H 2200 3250 30  0001 C CNN
F 1 "GND" H 2200 3180 30  0001 C CNN
F 2 "" H 2200 3250 60  0000 C CNN
F 3 "" H 2200 3250 60  0000 C CNN
	1    2200 3250
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR07
U 1 1 55219AE6
P 2200 2450
F 0 "#PWR07" H 2200 2550 30  0001 C CNN
F 1 "VCC" H 2200 2550 30  0000 C CNN
F 2 "" H 2200 2450 60  0000 C CNN
F 3 "" H 2200 2450 60  0000 C CNN
	1    2200 2450
	1    0    0    -1  
$EndComp
Text Label 2250 2550 0    60   ~ 0
mcu-vcc
$Comp
L C C5
U 1 1 55219B20
P 2750 2850
F 0 "C5" H 2750 2950 40  0000 L CNN
F 1 "100n" H 2756 2765 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 2788 2700 30  0000 C CNN
F 3 "~" H 2750 2850 60  0000 C CNN
	1    2750 2850
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR08
U 1 1 55219B27
P 2750 3250
F 0 "#PWR08" H 2750 3250 30  0001 C CNN
F 1 "GND" H 2750 3180 30  0001 C CNN
F 2 "" H 2750 3250 60  0000 C CNN
F 3 "" H 2750 3250 60  0000 C CNN
	1    2750 3250
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR09
U 1 1 55219B2E
P 2750 2450
F 0 "#PWR09" H 2750 2550 30  0001 C CNN
F 1 "VCC" H 2750 2550 30  0000 C CNN
F 2 "" H 2750 2450 60  0000 C CNN
F 3 "" H 2750 2450 60  0000 C CNN
	1    2750 2450
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 55219B37
P 2750 3950
F 0 "C6" H 2750 4050 40  0000 L CNN
F 1 "100n" H 2756 3865 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 2788 3800 30  0000 C CNN
F 3 "~" H 2750 3950 60  0000 C CNN
	1    2750 3950
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR010
U 1 1 55219B3E
P 2750 4350
F 0 "#PWR010" H 2750 4350 30  0001 C CNN
F 1 "GND" H 2750 4280 30  0001 C CNN
F 2 "" H 2750 4350 60  0000 C CNN
F 3 "" H 2750 4350 60  0000 C CNN
	1    2750 4350
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR011
U 1 1 55219B45
P 2750 3550
F 0 "#PWR011" H 2750 3650 30  0001 C CNN
F 1 "VCC" H 2750 3650 30  0000 C CNN
F 2 "" H 2750 3550 60  0000 C CNN
F 3 "" H 2750 3550 60  0000 C CNN
	1    2750 3550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 55219BF7
P 5000 4150
F 0 "#PWR012" H 5000 4150 30  0001 C CNN
F 1 "GND" H 5000 4080 30  0001 C CNN
F 2 "" H 5000 4150 60  0000 C CNN
F 3 "" H 5000 4150 60  0000 C CNN
	1    5000 4150
	1    0    0    -1  
$EndComp
Text Label 6200 2950 0    60   ~ 0
d-
Text Label 6450 1150 0    60   ~ 0
d+
$Comp
L R R12
U 1 1 55219EFE
P 8800 5750
F 0 "R12" V 8880 5750 40  0000 C CNN
F 1 "68" V 8807 5751 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 8730 5750 30  0000 C CNN
F 3 "~" H 8800 5750 30  0000 C CNN
	1    8800 5750
	0    -1   -1   0   
$EndComp
Text Label 8300 5750 0    60   ~ 0
d-
$Comp
L R R13
U 1 1 55219F73
P 8800 5950
F 0 "R13" V 8880 5950 40  0000 C CNN
F 1 "68" V 8807 5951 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 8730 5950 30  0000 C CNN
F 3 "~" H 8800 5950 30  0000 C CNN
	1    8800 5950
	0    -1   -1   0   
$EndComp
Text Label 8300 5950 0    60   ~ 0
d+
$Comp
L MICRO-USB-B U2
U 1 1 55219FEF
P 10400 5950
F 0 "U2" H 10400 5350 60  0000 C CNN
F 1 "MICRO-USB-B" H 10400 5800 60  0000 C CNN
F 2 "micro-usb-b:micro-usb-b" H 10400 5950 60  0000 C CNN
F 3 "~" H 10400 5950 60  0000 C CNN
	1    10400 5950
	0    -1   1    0   
$EndComp
$Comp
L R R16
U 1 1 5521A06E
P 9150 5400
F 0 "R16" V 9230 5400 40  0000 C CNN
F 1 "1k5" V 9157 5401 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 9080 5400 30  0000 C CNN
F 3 "~" H 9150 5400 30  0000 C CNN
	1    9150 5400
	-1   0    0    1   
$EndComp
$Comp
L ZENER D2
U 1 1 5521A0F5
P 9150 6500
F 0 "D2" H 9150 6600 50  0000 C CNN
F 1 "3v6" H 9150 6400 40  0000 C CNN
F 2 "MY_STAB-5-mm" H 9150 6500 60  0000 C CNN
F 3 "~" H 9150 6500 60  0000 C CNN
	1    9150 6500
	0    -1   -1   0   
$EndComp
$Comp
L ZENER D3
U 1 1 5521A107
P 9350 6250
F 0 "D3" H 9350 6350 50  0000 C CNN
F 1 "3v6" H 9350 6150 40  0000 C CNN
F 2 "MY_STAB-5-mm" H 9350 6250 60  0000 C CNN
F 3 "~" H 9350 6250 60  0000 C CNN
	1    9350 6250
	0    -1   -1   0   
$EndComp
$Comp
L R R18
U 1 1 5521A17D
P 9600 6550
F 0 "R18" V 9680 6550 40  0000 C CNN
F 1 "100k" V 9607 6551 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 9530 6550 30  0000 C CNN
F 3 "~" H 9600 6550 30  0000 C CNN
	1    9600 6550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 5521A290
P 9750 7000
F 0 "#PWR013" H 9750 7000 30  0001 C CNN
F 1 "GND" H 9750 6930 30  0001 C CNN
F 2 "" H 9750 7000 60  0000 C CNN
F 3 "" H 9750 7000 60  0000 C CNN
	1    9750 7000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 5521A361
P 9350 6550
F 0 "#PWR014" H 9350 6550 30  0001 C CNN
F 1 "GND" H 9350 6480 30  0001 C CNN
F 2 "" H 9350 6550 60  0000 C CNN
F 3 "" H 9350 6550 60  0000 C CNN
	1    9350 6550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 5521A367
P 9150 6800
F 0 "#PWR015" H 9150 6800 30  0001 C CNN
F 1 "GND" H 9150 6730 30  0001 C CNN
F 2 "" H 9150 6800 60  0000 C CNN
F 3 "" H 9150 6800 60  0000 C CNN
	1    9150 6800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 5521A48D
P 10400 6950
F 0 "#PWR016" H 10400 6950 30  0001 C CNN
F 1 "GND" H 10400 6880 30  0001 C CNN
F 2 "" H 10400 6950 60  0000 C CNN
F 3 "" H 10400 6950 60  0000 C CNN
	1    10400 6950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 5521A5BB
P 10600 4800
F 0 "#PWR017" H 10600 4800 30  0001 C CNN
F 1 "GND" H 10600 4730 30  0001 C CNN
F 2 "" H 10600 4800 60  0000 C CNN
F 3 "" H 10600 4800 60  0000 C CNN
	1    10600 4800
	1    0    0    -1  
$EndComp
Text Label 6150 1450 0    60   ~ 0
mosi
Text Label 6150 1550 0    60   ~ 0
miso
Text Label 6150 1650 0    60   ~ 0
sck
$Comp
L VCC #PWR018
U 1 1 5521A7C3
P 9650 4900
F 0 "#PWR018" H 9650 5000 30  0001 C CNN
F 1 "VCC" H 9650 5000 30  0000 C CNN
F 2 "" H 9650 4900 60  0000 C CNN
F 3 "" H 9650 4900 60  0000 C CNN
	1    9650 4900
	1    0    0    -1  
$EndComp
$Comp
L CONN_3X2 P7
U 1 1 5521A8ED
P 9000 1050
F 0 "P7" H 9000 1300 50  0000 C CNN
F 1 "servo" V 9000 1100 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03" H 9000 1050 60  0001 C CNN
F 3 "" H 9000 1050 60  0000 C CNN
	1    9000 1050
	1    0    0    -1  
$EndComp
Text Label 8250 1000 0    60   ~ 0
vcc
Text Label 8250 900  0    60   ~ 0
gnd
Text Label 7350 1100 0    60   ~ 0
servo1
Text Label 9450 1000 0    60   ~ 0
vcc
Text Label 9450 900  0    60   ~ 0
gnd
Text Label 10350 1100 0    60   ~ 0
servo2
$Comp
L MOSFET_P Q5
U 1 1 5521B54A
P 5350 5350
F 0 "Q5" H 5350 5540 60  0000 R CNN
F 1 "irlml2244" H 5350 5170 60  0000 R CNN
F 2 "Housings_SOT-23_SOT-143_TSOT-6:SOT-23" H 5350 5350 60  0000 C CNN
F 3 "~" H 5350 5350 60  0000 C CNN
	1    5350 5350
	0    1    -1   0   
$EndComp
$Comp
L R R5
U 1 1 5521B550
P 3900 5150
F 0 "R5" V 3980 5150 40  0000 C CNN
F 1 "3" V 3907 5151 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 3830 5150 30  0000 C CNN
F 3 "~" H 3900 5150 30  0000 C CNN
	1    3900 5150
	0    -1   -1   0   
$EndComp
$Comp
L PNP Q3
U 1 1 5521B556
P 4600 5850
F 0 "Q3" H 4600 5700 60  0000 R CNN
F 1 "bc857" H 4600 6000 60  0000 R CNN
F 2 "Housings_SOT-23_SOT-143_TSOT-6:SOT-23" H 4600 5850 60  0000 C CNN
F 3 "~" H 4600 5850 60  0000 C CNN
	1    4600 5850
	0    1    1    0   
$EndComp
$Comp
L R R6
U 1 1 5521B55E
P 3900 5350
F 0 "R6" V 3980 5350 40  0000 C CNN
F 1 "3" V 3907 5351 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 3830 5350 30  0000 C CNN
F 3 "~" H 3900 5350 30  0000 C CNN
	1    3900 5350
	0    -1   -1   0   
$EndComp
$Comp
L R R8
U 1 1 5521B565
P 5350 6500
F 0 "R8" V 5430 6500 40  0000 C CNN
F 1 "30k" V 5357 6501 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 5280 6500 30  0000 C CNN
F 3 "~" H 5350 6500 30  0000 C CNN
	1    5350 6500
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR019
U 1 1 5521B56E
P 5350 7600
F 0 "#PWR019" H 5350 7600 30  0001 C CNN
F 1 "GND" H 5350 7530 30  0001 C CNN
F 2 "" H 5350 7600 60  0000 C CNN
F 3 "" H 5350 7600 60  0000 C CNN
	1    5350 7600
	1    0    0    -1  
$EndComp
$Comp
L NPN Q4
U 1 1 5521B58F
P 5250 7150
F 0 "Q4" H 5250 7000 50  0000 R CNN
F 1 "bc847" H 5250 7300 50  0000 R CNN
F 2 "Housings_SOT-23_SOT-143_TSOT-6:SOT-23" H 5250 7150 60  0000 C CNN
F 3 "~" H 5250 7150 60  0000 C CNN
	1    5250 7150
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 5521B595
P 4600 7150
F 0 "R7" V 4680 7150 40  0000 C CNN
F 1 "1k" V 4607 7151 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 4530 7150 30  0000 C CNN
F 3 "~" H 4600 7150 30  0000 C CNN
	1    4600 7150
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 5521B5A0
P 1450 5250
F 0 "R1" V 1530 5250 40  0000 C CNN
F 1 "10" V 1457 5251 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 1380 5250 30  0000 C CNN
F 3 "~" H 1450 5250 30  0000 C CNN
	1    1450 5250
	0    -1   -1   0   
$EndComp
$Comp
L PNP Q1
U 1 1 5521B5A6
P 1800 5550
F 0 "Q1" H 1800 5400 60  0000 R CNN
F 1 "bc857" H 1800 5700 60  0000 R CNN
F 2 "Housings_SOT-23_SOT-143_TSOT-6:SOT-23" H 1800 5550 60  0000 C CNN
F 3 "~" H 1800 5550 60  0000 C CNN
	1    1800 5550
	0    1    1    0   
$EndComp
$Comp
L R R4
U 1 1 5521B5B2
P 2500 6300
F 0 "R4" V 2580 6300 40  0000 C CNN
F 1 "30k" V 2507 6301 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 2430 6300 30  0000 C CNN
F 3 "~" H 2500 6300 30  0000 C CNN
	1    2500 6300
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR020
U 1 1 5521B5B8
P 2500 7400
F 0 "#PWR020" H 2500 7400 30  0001 C CNN
F 1 "GND" H 2500 7330 30  0001 C CNN
F 2 "" H 2500 7400 60  0000 C CNN
F 3 "" H 2500 7400 60  0000 C CNN
	1    2500 7400
	1    0    0    -1  
$EndComp
$Comp
L NPN Q2
U 1 1 5521B5BF
P 2400 6950
F 0 "Q2" H 2400 6800 50  0000 R CNN
F 1 "bc847" H 2400 7100 50  0000 R CNN
F 2 "Housings_SOT-23_SOT-143_TSOT-6:SOT-23" H 2400 6950 60  0000 C CNN
F 3 "~" H 2400 6950 60  0000 C CNN
	1    2400 6950
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5521B5C5
P 1750 6950
F 0 "R2" V 1830 6950 40  0000 C CNN
F 1 "1k" V 1757 6951 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 1680 6950 30  0000 C CNN
F 3 "~" H 1750 6950 30  0000 C CNN
	1    1750 6950
	0    1    1    0   
$EndComp
Text Label 4800 5250 0    60   ~ 0
src
Text Label 5350 5850 1    60   ~ 0
gate
Text Label 2100 5250 0    60   ~ 0
src
Text Label 2500 5600 1    60   ~ 0
gate
Text Label 3350 7150 0    60   ~ 0
servo-en-400mA
Text Label 700  6950 0    60   ~ 0
servo-en-60mA
Text Label 5950 5250 0    60   ~ 0
vcc
Text Label 700  5250 0    60   ~ 0
power
Text Label 2950 5250 0    60   ~ 0
power
$Comp
L R R10
U 1 1 5521B600
P 7950 1100
F 0 "R10" V 8030 1100 40  0000 C CNN
F 1 "100" V 7957 1101 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 7880 1100 30  0000 C CNN
F 3 "~" H 7950 1100 30  0000 C CNN
	1    7950 1100
	0    1    1    0   
$EndComp
$Comp
L R R19
U 1 1 5521B880
P 10050 1100
F 0 "R19" V 10130 1100 40  0000 C CNN
F 1 "100" V 10057 1101 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 9980 1100 30  0000 C CNN
F 3 "~" H 10050 1100 30  0000 C CNN
	1    10050 1100
	0    1    1    0   
$EndComp
$Comp
L VCC #PWR021
U 1 1 5521BADC
P 650 5150
F 0 "#PWR021" H 650 5250 30  0001 C CNN
F 1 "VCC" H 650 5250 30  0000 C CNN
F 2 "" H 650 5150 60  0000 C CNN
F 3 "" H 650 5150 60  0000 C CNN
	1    650  5150
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR022
U 1 1 5521BB76
P 2900 5150
F 0 "#PWR022" H 2900 5250 30  0001 C CNN
F 1 "VCC" H 2900 5250 30  0000 C CNN
F 2 "" H 2900 5150 60  0000 C CNN
F 3 "" H 2900 5150 60  0000 C CNN
	1    2900 5150
	1    0    0    -1  
$EndComp
Text Label 6150 1850 0    60   ~ 0
servo-en-60mA
Text Label 6150 1950 0    60   ~ 0
servo-en-400mA
Text Label 6200 2850 0    60   ~ 0
usb-en
Text Label 9150 5100 1    60   ~ 0
usb-en
$Comp
L R R14
U 1 1 5521BF78
P 8850 6550
F 0 "R14" V 8930 6550 40  0000 C CNN
F 1 "100k" V 8857 6551 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 8780 6550 30  0000 C CNN
F 3 "~" H 8850 6550 30  0000 C CNN
	1    8850 6550
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 5521C255
P 7650 6200
F 0 "C8" H 7650 6300 40  0000 L CNN
F 1 "4u7" H 7656 6115 40  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 7688 6050 30  0000 C CNN
F 3 "~" H 7650 6200 60  0000 C CNN
	1    7650 6200
	-1   0    0    1   
$EndComp
$Comp
L VCC #PWR023
U 1 1 5521C271
P 7650 5900
F 0 "#PWR023" H 7650 6000 30  0001 C CNN
F 1 "VCC" H 7650 6000 30  0000 C CNN
F 2 "" H 7650 5900 60  0000 C CNN
F 3 "" H 7650 5900 60  0000 C CNN
	1    7650 5900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR024
U 1 1 5521C30D
P 7650 6500
F 0 "#PWR024" H 7650 6500 30  0001 C CNN
F 1 "GND" H 7650 6430 30  0001 C CNN
F 2 "" H 7650 6500 60  0000 C CNN
F 3 "" H 7650 6500 60  0000 C CNN
	1    7650 6500
	1    0    0    -1  
$EndComp
$Comp
L CP1 C7
U 1 1 55240250
P 5850 5600
F 0 "C7" H 5900 5700 50  0000 L CNN
F 1 "1000u" H 5900 5500 50  0000 L CNN
F 2 "Discret:C2V10" H 5850 5600 60  0000 C CNN
F 3 "~" H 5850 5600 60  0000 C CNN
	1    5850 5600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR025
U 1 1 5524036E
P 5850 6000
F 0 "#PWR025" H 5850 6000 30  0001 C CNN
F 1 "GND" H 5850 5930 30  0001 C CNN
F 2 "" H 5850 6000 60  0000 C CNN
F 3 "" H 5850 6000 60  0000 C CNN
	1    5850 6000
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 55240468
P 6750 4950
F 0 "D1" H 6750 5050 50  0000 C CNN
F 1 "dbg-led" H 6750 4850 50  0000 C CNN
F 2 "LEDs:LED-5MM" H 6750 4950 60  0000 C CNN
F 3 "~" H 6750 4950 60  0000 C CNN
	1    6750 4950
	0    1    1    0   
$EndComp
$Comp
L R R9
U 1 1 55240477
P 6750 4300
F 0 "R9" V 6830 4300 40  0000 C CNN
F 1 "1k" V 6757 4301 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 6680 4300 30  0000 C CNN
F 3 "~" H 6750 4300 30  0000 C CNN
	1    6750 4300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR026
U 1 1 552406B4
P 6750 5550
F 0 "#PWR026" H 6750 5550 30  0001 C CNN
F 1 "GND" H 6750 5480 30  0001 C CNN
F 2 "" H 6750 5550 60  0000 C CNN
F 3 "" H 6750 5550 60  0000 C CNN
	1    6750 5550
	1    0    0    -1  
$EndComp
$Comp
L LED D4
U 1 1 552409A3
P 10350 3950
F 0 "D4" H 10350 4050 50  0000 C CNN
F 1 "light-led" H 10350 3850 50  0000 C CNN
F 2 "LEDs:LED-5MM" H 10350 3950 60  0000 C CNN
F 3 "~" H 10350 3950 60  0000 C CNN
	1    10350 3950
	0    1    1    0   
$EndComp
$Comp
L R R20
U 1 1 552409AE
P 10350 3300
F 0 "R20" V 10430 3300 40  0000 C CNN
F 1 "33" V 10357 3301 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 10280 3300 30  0000 C CNN
F 3 "~" H 10350 3300 30  0000 C CNN
	1    10350 3300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR027
U 1 1 55240AD0
P 10350 4400
F 0 "#PWR027" H 10350 4400 30  0001 C CNN
F 1 "GND" H 10350 4330 30  0001 C CNN
F 2 "" H 10350 4400 60  0000 C CNN
F 3 "" H 10350 4400 60  0000 C CNN
	1    10350 4400
	1    0    0    -1  
$EndComp
$Comp
L LED D5
U 1 1 55240C65
P 10650 3950
F 0 "D5" H 10650 4050 50  0000 C CNN
F 1 "light-led" H 10650 3850 50  0000 C CNN
F 2 "LEDs:LED-5MM" H 10650 3950 60  0000 C CNN
F 3 "~" H 10650 3950 60  0000 C CNN
	1    10650 3950
	0    1    1    0   
$EndComp
$Comp
L R R21
U 1 1 55240C6B
P 10650 3300
F 0 "R21" V 10730 3300 40  0000 C CNN
F 1 "33" V 10657 3301 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 10580 3300 30  0000 C CNN
F 3 "~" H 10650 3300 30  0000 C CNN
	1    10650 3300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR028
U 1 1 55240C73
P 10650 4400
F 0 "#PWR028" H 10650 4400 30  0001 C CNN
F 1 "GND" H 10650 4330 30  0001 C CNN
F 2 "" H 10650 4400 60  0000 C CNN
F 3 "" H 10650 4400 60  0000 C CNN
	1    10650 4400
	1    0    0    -1  
$EndComp
$Comp
L LED D6
U 1 1 55240C79
P 10950 3950
F 0 "D6" H 10950 4050 50  0000 C CNN
F 1 "light-led" H 10950 3850 50  0000 C CNN
F 2 "LEDs:LED-5MM" H 10950 3950 60  0000 C CNN
F 3 "~" H 10950 3950 60  0000 C CNN
	1    10950 3950
	0    1    1    0   
$EndComp
$Comp
L R R22
U 1 1 55240C7F
P 10950 3300
F 0 "R22" V 11030 3300 40  0000 C CNN
F 1 "33" V 10957 3301 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 10880 3300 30  0000 C CNN
F 3 "~" H 10950 3300 30  0000 C CNN
	1    10950 3300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR029
U 1 1 55240C87
P 10950 4400
F 0 "#PWR029" H 10950 4400 30  0001 C CNN
F 1 "GND" H 10950 4330 30  0001 C CNN
F 2 "" H 10950 4400 60  0000 C CNN
F 3 "" H 10950 4400 60  0000 C CNN
	1    10950 4400
	1    0    0    -1  
$EndComp
$Comp
L MOSFET_P Q7
U 1 1 55240F47
P 10250 2350
F 0 "Q7" H 10250 2540 60  0000 R CNN
F 1 "irlml2244" H 10250 2170 60  0000 R CNN
F 2 "Housings_SOT-23_SOT-143_TSOT-6:SOT-23" H 10250 2350 60  0000 C CNN
F 3 "~" H 10250 2350 60  0000 C CNN
	1    10250 2350
	1    0    0    1   
$EndComp
$Comp
L R R17
U 1 1 5524127C
P 9600 1950
F 0 "R17" V 9680 1950 40  0000 C CNN
F 1 "1k" V 9607 1951 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 9530 1950 30  0000 C CNN
F 3 "~" H 9600 1950 30  0000 C CNN
	1    9600 1950
	1    0    0    -1  
$EndComp
$Comp
L NPN Q6
U 1 1 552414BD
P 9500 2650
F 0 "Q6" H 9500 2500 50  0000 R CNN
F 1 "NPN" H 9500 2800 50  0000 R CNN
F 2 "Housings_SOT-23_SOT-143_TSOT-6:SOT-23" H 9500 2650 60  0000 C CNN
F 3 "~" H 9500 2650 60  0000 C CNN
	1    9500 2650
	1    0    0    -1  
$EndComp
$Comp
L R R11
U 1 1 55241567
P 8600 2650
F 0 "R11" V 8680 2650 40  0000 C CNN
F 1 "1k" V 8607 2651 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 8530 2650 30  0000 C CNN
F 3 "~" H 8600 2650 30  0000 C CNN
	1    8600 2650
	0    -1   -1   0   
$EndComp
$Comp
L R R15
U 1 1 5524160B
P 9000 3050
F 0 "R15" V 9080 3050 40  0000 C CNN
F 1 "30k" V 9007 3051 40  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 8930 3050 30  0000 C CNN
F 3 "~" H 9000 3050 30  0000 C CNN
	1    9000 3050
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR030
U 1 1 55241757
P 9000 3500
F 0 "#PWR030" H 9000 3500 30  0001 C CNN
F 1 "GND" H 9000 3430 30  0001 C CNN
F 2 "" H 9000 3500 60  0000 C CNN
F 3 "" H 9000 3500 60  0000 C CNN
	1    9000 3500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR031
U 1 1 552419C1
P 9600 3500
F 0 "#PWR031" H 9600 3500 30  0001 C CNN
F 1 "GND" H 9600 3430 30  0001 C CNN
F 2 "" H 9600 3500 60  0000 C CNN
F 3 "" H 9600 3500 60  0000 C CNN
	1    9600 3500
	1    0    0    -1  
$EndComp
Text Label 6750 3950 1    60   ~ 0
dbg-led
$Comp
L CONN_3 K1
U 1 1 552FF59F
P 8250 2050
F 0 "K1" V 8200 2050 50  0000 C CNN
F 1 "pyro" V 8300 2050 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 8250 2050 60  0001 C CNN
F 3 "" H 8250 2050 60  0000 C CNN
	1    8250 2050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR032
U 1 1 552FF855
P 7800 2250
F 0 "#PWR032" H 7800 2250 30  0001 C CNN
F 1 "GND" H 7800 2180 30  0001 C CNN
F 2 "" H 7800 2250 60  0000 C CNN
F 3 "" H 7800 2250 60  0000 C CNN
	1    7800 2250
	1    0    0    -1  
$EndComp
Text Label 7400 2050 0    60   ~ 0
pyro-sen
$Comp
L VCC #PWR033
U 1 1 552FF5E1
P 7650 1750
F 0 "#PWR033" H 7650 1850 30  0001 C CNN
F 1 "VCC" H 7650 1850 30  0000 C CNN
F 2 "" H 7650 1750 60  0000 C CNN
F 3 "" H 7650 1750 60  0000 C CNN
	1    7650 1750
	1    0    0    -1  
$EndComp
Text Label 6450 1250 0    60   ~ 0
d-
Text Label 6100 2250 0    60   ~ 0
servo1
Text Label 6100 2350 0    60   ~ 0
servo2
Text Label 6200 3050 0    60   ~ 0
dbg-led
Text Label 8100 2650 0    60   ~ 0
led
Text Label 6200 3150 0    60   ~ 0
led
$Comp
L TST P1
U 1 1 552FFFBF
P 7200 3900
F 0 "P1" H 7200 4200 40  0000 C CNN
F 1 "TST" H 7200 4150 30  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01" H 7200 3900 60  0000 C CNN
F 3 "~" H 7200 3900 60  0000 C CNN
	1    7200 3900
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR034
U 1 1 5530007B
P 7100 4050
F 0 "#PWR034" H 7100 4150 30  0001 C CNN
F 1 "VCC" H 7100 4150 30  0000 C CNN
F 2 "" H 7100 4050 60  0000 C CNN
F 3 "" H 7100 4050 60  0000 C CNN
	1    7100 4050
	1    0    0    -1  
$EndComp
$Comp
L TST P2
U 1 1 55300130
P 7400 3900
F 0 "P2" H 7400 4200 40  0000 C CNN
F 1 "TST" H 7400 4150 30  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01" H 7400 3900 60  0000 C CNN
F 3 "~" H 7400 3900 60  0000 C CNN
	1    7400 3900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR035
U 1 1 55300137
P 7400 4100
F 0 "#PWR035" H 7400 4100 30  0001 C CNN
F 1 "GND" H 7400 4030 30  0001 C CNN
F 2 "" H 7400 4100 60  0000 C CNN
F 3 "" H 7400 4100 60  0000 C CNN
	1    7400 4100
	1    0    0    -1  
$EndComp
$Comp
L TST P3
U 1 1 5530013D
P 7600 3900
F 0 "P3" H 7600 4200 40  0000 C CNN
F 1 "TST" H 7600 4150 30  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01" H 7600 3900 60  0000 C CNN
F 3 "~" H 7600 3900 60  0000 C CNN
	1    7600 3900
	1    0    0    -1  
$EndComp
Text Label 7600 4050 1    60   ~ 0
rst
$Comp
L TST P4
U 1 1 55300144
P 7800 3900
F 0 "P4" H 7800 4200 40  0000 C CNN
F 1 "TST" H 7800 4150 30  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01" H 7800 3900 60  0000 C CNN
F 3 "~" H 7800 3900 60  0000 C CNN
	1    7800 3900
	1    0    0    -1  
$EndComp
Text Label 7800 4050 1    60   ~ 0
sck
$Comp
L TST P5
U 1 1 5530014E
P 8000 3900
F 0 "P5" H 8000 4200 40  0000 C CNN
F 1 "TST" H 8000 4150 30  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01" H 8000 3900 60  0000 C CNN
F 3 "~" H 8000 3900 60  0000 C CNN
	1    8000 3900
	1    0    0    -1  
$EndComp
Text Label 8000 4050 1    60   ~ 0
miso
$Comp
L TST P6
U 1 1 55300157
P 8200 3900
F 0 "P6" H 8200 4200 40  0000 C CNN
F 1 "TST" H 8200 4150 30  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01" H 8200 3900 60  0000 C CNN
F 3 "~" H 8200 3900 60  0000 C CNN
	1    8200 3900
	1    0    0    -1  
$EndComp
Text Label 8200 4050 1    60   ~ 0
mosi
$Comp
L PWR_FLAG #FLG036
U 1 1 5530026F
P 5850 5050
F 0 "#FLG036" H 5850 5145 30  0001 C CNN
F 1 "PWR_FLAG" H 5850 5230 30  0000 C CNN
F 2 "" H 5850 5050 60  0000 C CNN
F 3 "" H 5850 5050 60  0000 C CNN
	1    5850 5050
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG037
U 1 1 553007FD
P 10200 4800
F 0 "#FLG037" H 10200 4895 30  0001 C CNN
F 1 "PWR_FLAG" H 10200 4980 30  0000 C CNN
F 2 "" H 10200 4800 60  0000 C CNN
F 3 "" H 10200 4800 60  0000 C CNN
	1    10200 4800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR038
U 1 1 553009E1
P 8850 6900
F 0 "#PWR038" H 8850 6900 30  0001 C CNN
F 1 "GND" H 8850 6830 30  0001 C CNN
F 2 "" H 8850 6900 60  0000 C CNN
F 3 "" H 8850 6900 60  0000 C CNN
	1    8850 6900
	1    0    0    -1  
$EndComp
Text Label 6100 2150 0    60   ~ 0
pyro-sen
NoConn ~ 6000 2050
NoConn ~ 6000 2450
NoConn ~ 6000 2550
NoConn ~ 6000 2750
NoConn ~ 6000 3250
NoConn ~ 6000 3350
NoConn ~ 6000 3450
NoConn ~ 6000 1350
$Comp
L VCC #PWR039
U 1 1 55300EC2
P 9600 1450
F 0 "#PWR039" H 9600 1550 30  0001 C CNN
F 1 "VCC" H 9600 1550 30  0000 C CNN
F 2 "" H 9600 1450 60  0000 C CNN
F 3 "" H 9600 1450 60  0000 C CNN
	1    9600 1450
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR040
U 1 1 55300EC8
P 10350 1950
F 0 "#PWR040" H 10350 2050 30  0001 C CNN
F 1 "VCC" H 10350 2050 30  0000 C CNN
F 2 "" H 10350 1950 60  0000 C CNN
F 3 "" H 10350 1950 60  0000 C CNN
	1    10350 1950
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG041
U 1 1 552FFAA1
P 9850 4900
F 0 "#FLG041" H 9850 4995 30  0001 C CNN
F 1 "PWR_FLAG" H 9850 5080 30  0000 C CNN
F 2 "" H 9850 4900 60  0000 C CNN
F 3 "" H 9850 4900 60  0000 C CNN
	1    9850 4900
	1    0    0    -1  
$EndComp
Text Label 2800 2550 0    60   ~ 0
mcu-vcc
Text Label 2850 3650 0    60   ~ 0
mcu-vcc
Text Label 3850 1350 2    60   ~ 0
mcu-vcc
Text Label 4950 800  1    60   ~ 0
mcu-vcc
Text Label 5050 800  1    60   ~ 0
mcu-vcc
$Comp
L crystal-4pin U1
U 1 1 55302327
P 1300 2450
F 0 "U1" H 1300 2150 60  0000 C CNN
F 1 "crystal-4pin" H 1300 2800 60  0000 C CNN
F 2 "crystal-smd-5x3:CRYSTAL-SMD-5x3" H 1250 2450 60  0001 C CNN
F 3 "" H 1250 2450 60  0000 C CNN
	1    1300 2450
	0    1    1    0   
$EndComp
Wire Wire Line
	1100 1500 1100 1750
Wire Wire Line
	1100 3150 1100 3400
Wire Wire Line
	4100 1850 3700 1850
Wire Wire Line
	4100 2050 3700 2050
Wire Wire Line
	1100 1650 1400 1650
Connection ~ 1100 1650
Wire Wire Line
	1100 3250 1400 3250
Connection ~ 1100 3250
Wire Wire Line
	1100 950  1100 1200
Wire Wire Line
	1100 950  700  950 
Wire Wire Line
	700  950  700  1150
Wire Wire Line
	1100 3700 1100 3950
Wire Wire Line
	4100 1150 3700 1150
Wire Wire Line
	4100 1350 3700 1350
Wire Wire Line
	4100 1450 3700 1450
Wire Wire Line
	4100 1550 4000 1550
Wire Wire Line
	4000 1550 4000 1650
Wire Wire Line
	4950 850  4950 550 
Wire Wire Line
	5050 850  5050 550 
Wire Wire Line
	2200 1250 2200 1600
Wire Wire Line
	2200 1900 2200 2150
Wire Wire Line
	2200 650  2200 950 
Wire Wire Line
	2200 1450 2500 1450
Connection ~ 2200 1450
Wire Wire Line
	2200 3000 2200 3250
Wire Wire Line
	2200 2450 2200 2700
Wire Wire Line
	2200 2550 2500 2550
Connection ~ 2200 2550
Wire Wire Line
	2750 3000 2750 3250
Wire Wire Line
	2750 2450 2750 2700
Wire Wire Line
	2750 2550 3050 2550
Connection ~ 2750 2550
Wire Wire Line
	2750 4100 2750 4350
Wire Wire Line
	2750 3550 2750 3800
Wire Wire Line
	2750 3650 3050 3650
Connection ~ 2750 3650
Wire Wire Line
	3700 1450 3700 1350
Wire Wire Line
	4950 3750 4950 3950
Wire Wire Line
	4950 3950 5050 3950
Wire Wire Line
	5050 3950 5050 3750
Wire Wire Line
	5000 3950 5000 4150
Connection ~ 5000 3950
Wire Wire Line
	6000 2950 6350 2950
Wire Wire Line
	6000 3050 6350 3050
Wire Wire Line
	6000 1650 6350 1650
Wire Wire Line
	6000 1550 6350 1550
Wire Wire Line
	6000 1450 6350 1450
Wire Wire Line
	8250 5750 8650 5750
Wire Wire Line
	8950 5750 9850 5750
Wire Wire Line
	8250 5950 8650 5950
Wire Wire Line
	9150 5550 9150 6300
Connection ~ 9150 5750
Wire Wire Line
	9150 4750 9150 5250
Wire Wire Line
	9350 6050 9350 5950
Connection ~ 9350 5950
Wire Wire Line
	8950 5950 9850 5950
Wire Wire Line
	9600 6150 9600 6400
Wire Wire Line
	9600 6150 9850 6150
Wire Wire Line
	9850 6350 9750 6350
Wire Wire Line
	9750 6350 9750 7000
Wire Wire Line
	9600 6900 9750 6900
Wire Wire Line
	9600 6700 9600 6900
Connection ~ 9750 6900
Wire Wire Line
	9150 6700 9150 6800
Wire Wire Line
	9350 6450 9350 6550
Wire Wire Line
	10300 6750 10300 6850
Wire Wire Line
	10300 6850 10500 6850
Wire Wire Line
	10500 6850 10500 6750
Wire Wire Line
	10400 6850 10400 6950
Connection ~ 10400 6850
Wire Wire Line
	10300 5150 10300 5050
Wire Wire Line
	10300 5050 10500 5050
Wire Wire Line
	10500 5050 10500 5150
Wire Wire Line
	10400 5050 10400 4700
Wire Wire Line
	10400 4700 10600 4700
Wire Wire Line
	10600 4700 10600 4800
Connection ~ 10400 5050
Wire Wire Line
	9850 5550 9650 5550
Wire Wire Line
	9650 5550 9650 4900
Wire Wire Line
	8600 900  8200 900 
Wire Wire Line
	8600 1000 8200 1000
Wire Wire Line
	8100 1100 8600 1100
Wire Wire Line
	9400 900  9800 900 
Wire Wire Line
	9800 1000 9400 1000
Wire Wire Line
	9400 1100 9900 1100
Wire Wire Line
	4600 5650 4600 5250
Connection ~ 4600 5250
Wire Wire Line
	5550 5250 6350 5250
Wire Wire Line
	3450 5950 4400 5950
Connection ~ 5350 5950
Wire Wire Line
	5350 7600 5350 7350
Wire Wire Line
	3550 5150 3550 5350
Wire Wire Line
	3550 5150 3750 5150
Wire Wire Line
	3550 5350 3750 5350
Connection ~ 3550 5250
Wire Wire Line
	4050 5350 4250 5350
Wire Wire Line
	4250 5350 4250 5150
Wire Wire Line
	4250 5150 4050 5150
Wire Wire Line
	4250 5250 5150 5250
Connection ~ 4250 5250
Wire Wire Line
	5350 5550 5350 6350
Wire Wire Line
	3550 5250 2900 5250
Wire Wire Line
	4800 5950 5350 5950
Wire Wire Line
	4750 7150 5050 7150
Wire Wire Line
	3300 7150 4450 7150
Wire Wire Line
	5350 6650 5350 6950
Wire Wire Line
	2500 7400 2500 7150
Wire Wire Line
	1900 6950 2200 6950
Wire Wire Line
	650  6950 1600 6950
Wire Wire Line
	2500 6450 2500 6750
Wire Wire Line
	2000 5650 2500 5650
Wire Wire Line
	1600 5650 1050 5650
Wire Wire Line
	1050 5650 1050 5250
Wire Wire Line
	650  5250 1300 5250
Connection ~ 1050 5250
Wire Wire Line
	1600 5250 2250 5250
Wire Wire Line
	1800 5250 1800 5350
Connection ~ 1800 5250
Wire Wire Line
	2500 5450 2500 6150
Connection ~ 2500 5650
Wire Wire Line
	7300 1100 7800 1100
Wire Wire Line
	10200 1100 10700 1100
Wire Wire Line
	650  5250 650  5150
Wire Wire Line
	2900 5250 2900 5150
Wire Wire Line
	6000 1850 6950 1850
Wire Wire Line
	6000 1950 6950 1950
Wire Wire Line
	6000 2850 6350 2850
Wire Wire Line
	8850 6200 8850 6400
Wire Wire Line
	8850 6200 9150 6200
Connection ~ 9150 6200
Wire Wire Line
	7650 6350 7650 6500
Wire Wire Line
	7650 5900 7650 6050
Wire Wire Line
	3450 5250 3450 5950
Connection ~ 3450 5250
Wire Wire Line
	5850 5050 5850 5450
Connection ~ 5850 5250
Wire Wire Line
	5850 5750 5850 6000
Wire Wire Line
	6750 4450 6750 4750
Wire Wire Line
	6750 3550 6750 4150
Wire Wire Line
	6750 5150 6750 5550
Wire Wire Line
	10350 3450 10350 3750
Wire Wire Line
	10350 4150 10350 4400
Wire Wire Line
	10350 2550 10350 3150
Wire Wire Line
	10650 3450 10650 3750
Wire Wire Line
	10650 4150 10650 4400
Wire Wire Line
	10950 3450 10950 3750
Wire Wire Line
	10950 4150 10950 4400
Wire Wire Line
	10650 2850 10650 3150
Wire Wire Line
	10350 2850 10950 2850
Connection ~ 10350 2850
Wire Wire Line
	10950 2850 10950 3150
Connection ~ 10650 2850
Wire Wire Line
	10350 2150 10350 1950
Wire Wire Line
	10050 2350 9600 2350
Wire Wire Line
	9600 2100 9600 2450
Wire Wire Line
	9600 1450 9600 1800
Connection ~ 9600 2350
Wire Wire Line
	8750 2650 9300 2650
Wire Wire Line
	9000 2650 9000 2900
Connection ~ 9000 2650
Wire Wire Line
	9000 3200 9000 3500
Wire Wire Line
	8050 2650 8450 2650
Wire Wire Line
	9600 2850 9600 3500
Wire Wire Line
	7900 2150 7800 2150
Wire Wire Line
	7800 2150 7800 2250
Wire Wire Line
	7900 2050 7350 2050
Wire Wire Line
	7900 1950 7650 1950
Wire Wire Line
	7650 1950 7650 1750
Wire Wire Line
	6000 3150 6350 3150
Wire Wire Line
	6000 1150 6600 1150
Wire Wire Line
	6000 1250 6600 1250
Wire Wire Line
	6000 2250 6400 2250
Wire Wire Line
	6000 2350 6400 2350
Wire Wire Line
	7200 3900 7200 4100
Wire Wire Line
	7100 4050 7100 4100
Wire Wire Line
	7100 4100 7200 4100
Wire Wire Line
	7400 3900 7400 4100
Wire Wire Line
	7600 3900 7600 4100
Wire Wire Line
	7800 3900 7800 4100
Wire Wire Line
	8000 3900 8000 4100
Wire Wire Line
	8200 3900 8200 4100
Wire Wire Line
	9850 4900 9850 5000
Wire Wire Line
	9850 5000 9650 5000
Connection ~ 9650 5000
Wire Wire Line
	10200 4800 10200 4900
Wire Wire Line
	10200 4900 10400 4900
Connection ~ 10400 4900
Wire Wire Line
	8850 6700 8850 6900
Wire Wire Line
	6000 2150 6400 2150
$EndSCHEMATC
