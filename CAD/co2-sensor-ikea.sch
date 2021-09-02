EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:WeMos_D1_mini U101
U 1 1 61222A73
P 5300 3550
F 0 "U101" H 5800 4300 50  0000 C CNN
F 1 "WeMos_D1_mini" H 5750 4400 50  0000 C CNN
F 2 "Module:WEMOS_D1_mini_light" H 5300 2400 50  0001 C CNN
F 3 "https://wiki.wemos.cc/products:d1:d1_mini#documentation" H 3450 2400 50  0001 C CNN
	1    5300 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 3650 6350 3650
Wire Wire Line
	5700 3850 6000 3850
$Comp
L Connector:Conn_01x03_Male J103
U 1 1 6122D66D
P 8500 3750
F 0 "J103" H 8472 3682 50  0000 R CNN
F 1 "Conn_LED" H 8472 3773 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 8500 3750 50  0001 C CNN
F 3 "~" H 8500 3750 50  0001 C CNN
	1    8500 3750
	-1   0    0    1   
$EndComp
Wire Wire Line
	7750 4450 8100 4450
Wire Wire Line
	8100 4450 8100 3850
Wire Wire Line
	8100 3850 8300 3850
Wire Wire Line
	8000 4050 8000 3750
Wire Wire Line
	8000 3750 8300 3750
$Comp
L Connector:Conn_01x02_Male J101
U 1 1 61236D41
P 3500 2100
F 0 "J101" H 3608 2281 50  0000 C CNN
F 1 "Conn_Power" H 3608 2190 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3500 2100 50  0001 C CNN
F 3 "~" H 3500 2100 50  0001 C CNN
	1    3500 2100
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0101
U 1 1 612386B0
P 4150 1750
F 0 "#PWR0101" H 4150 1600 50  0001 C CNN
F 1 "+5V" H 4165 1923 50  0000 C CNN
F 2 "" H 4150 1750 50  0001 C CNN
F 3 "" H 4150 1750 50  0001 C CNN
	1    4150 1750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0102
U 1 1 6123A030
P 5200 2450
F 0 "#PWR0102" H 5200 2300 50  0001 C CNN
F 1 "+5V" H 5215 2623 50  0000 C CNN
F 2 "" H 5200 2450 50  0001 C CNN
F 3 "" H 5200 2450 50  0001 C CNN
	1    5200 2450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0103
U 1 1 6123C004
P 7000 1450
F 0 "#PWR0103" H 7000 1300 50  0001 C CNN
F 1 "+5V" H 7015 1623 50  0000 C CNN
F 2 "" H 7000 1450 50  0001 C CNN
F 3 "" H 7000 1450 50  0001 C CNN
	1    7000 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 6123C734
P 4150 2450
F 0 "#PWR0104" H 4150 2200 50  0001 C CNN
F 1 "GND" H 4155 2277 50  0000 C CNN
F 2 "" H 4150 2450 50  0001 C CNN
F 3 "" H 4150 2450 50  0001 C CNN
	1    4150 2450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 6123D0D2
P 5300 4850
F 0 "#PWR0105" H 5300 4600 50  0001 C CNN
F 1 "GND" H 5305 4677 50  0000 C CNN
F 2 "" H 5300 4850 50  0001 C CNN
F 3 "" H 5300 4850 50  0001 C CNN
	1    5300 4850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 6123D7C6
P 7000 2950
F 0 "#PWR0106" H 7000 2700 50  0001 C CNN
F 1 "GND" H 7005 2777 50  0000 C CNN
F 2 "" H 7000 2950 50  0001 C CNN
F 3 "" H 7000 2950 50  0001 C CNN
	1    7000 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 1750 4150 2100
Wire Wire Line
	4150 2100 3700 2100
Wire Wire Line
	3700 2200 4150 2200
Wire Wire Line
	4150 2200 4150 2450
Wire Wire Line
	5200 2450 5200 2750
Wire Wire Line
	5300 4350 5300 4850
Wire Wire Line
	7000 1450 7000 1600
$Comp
L Connector:Conn_01x04_Male J102
U 1 1 61246FA9
P 8500 2750
F 0 "J102" H 8472 2632 50  0000 R CNN
F 1 "Conn_I2C" H 8472 2723 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 8500 2750 50  0001 C CNN
F 3 "~" H 8500 2750 50  0001 C CNN
	1    8500 2750
	-1   0    0    1   
$EndComp
$Comp
L Device:C C101
U 1 1 6122B09C
P 6350 2150
F 0 "C101" H 6465 2196 50  0000 L CNN
F 1 "C" H 6465 2105 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.8mm_W2.6mm_P2.50mm" H 6388 2000 50  0001 C CNN
F 3 "~" H 6350 2150 50  0001 C CNN
	1    6350 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 1600 6350 1600
Wire Wire Line
	6350 1600 6350 2000
Wire Wire Line
	6350 2300 6350 2800
Wire Wire Line
	6350 2800 7000 2800
Wire Wire Line
	7000 2800 7000 2950
Text GLabel 5950 3250 2    50   Input ~ 0
SCL
Text GLabel 5950 3350 2    50   Input ~ 0
SDA
Text GLabel 8100 2650 0    50   Input ~ 0
SCL
Text GLabel 8100 2550 0    50   Input ~ 0
SDA
Wire Wire Line
	8100 2550 8300 2550
Wire Wire Line
	8100 2650 8300 2650
$Comp
L power:+3V3 #PWR0107
U 1 1 6124573F
P 7700 2600
F 0 "#PWR0107" H 7700 2450 50  0001 C CNN
F 1 "+3V3" H 7715 2773 50  0000 C CNN
F 2 "" H 7700 2600 50  0001 C CNN
F 3 "" H 7700 2600 50  0001 C CNN
	1    7700 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 61246096
P 8100 2950
F 0 "#PWR0108" H 8100 2700 50  0001 C CNN
F 1 "GND" H 8105 2777 50  0000 C CNN
F 2 "" H 8100 2950 50  0001 C CNN
F 3 "" H 8100 2950 50  0001 C CNN
	1    8100 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 2750 8100 2750
Wire Wire Line
	8100 2750 8100 2950
Wire Wire Line
	7700 2850 7700 2600
$Comp
L power:+3V3 #PWR0109
U 1 1 61248F56
P 5400 2450
F 0 "#PWR0109" H 5400 2300 50  0001 C CNN
F 1 "+3V3" H 5415 2623 50  0000 C CNN
F 2 "" H 5400 2450 50  0001 C CNN
F 3 "" H 5400 2450 50  0001 C CNN
	1    5400 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 2450 5400 2750
Wire Wire Line
	7700 2850 8300 2850
Wire Wire Line
	5700 3250 5950 3250
Wire Wire Line
	5700 3350 5950 3350
$Comp
L Connector:Conn_01x04_Male J104
U 1 1 6125B88C
P 8500 5050
F 0 "J104" H 8472 4932 50  0000 R CNN
F 1 "Conn_UART" H 8472 5023 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 8500 5050 50  0001 C CNN
F 3 "~" H 8500 5050 50  0001 C CNN
	1    8500 5050
	-1   0    0    1   
$EndComp
Text GLabel 5950 3450 2    50   Input ~ 0
TXOUT
Text GLabel 5950 3550 2    50   Input ~ 0
RXIN
Text GLabel 8000 4850 0    50   Input ~ 0
RXIN
Text GLabel 8000 4950 0    50   Input ~ 0
TXOUT
$Comp
L power:+5V #PWR0110
U 1 1 6126074D
P 7500 4900
F 0 "#PWR0110" H 7500 4750 50  0001 C CNN
F 1 "+5V" H 7515 5073 50  0000 C CNN
F 2 "" H 7500 4900 50  0001 C CNN
F 3 "" H 7500 4900 50  0001 C CNN
	1    7500 4900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 61261132
P 8000 5300
F 0 "#PWR0111" H 8000 5050 50  0001 C CNN
F 1 "GND" H 8005 5127 50  0000 C CNN
F 2 "" H 8000 5300 50  0001 C CNN
F 3 "" H 8000 5300 50  0001 C CNN
	1    8000 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 5050 8000 5050
Wire Wire Line
	8000 5050 8000 5300
Wire Wire Line
	7500 4900 7500 5150
Wire Wire Line
	7500 5150 8300 5150
Wire Wire Line
	5700 3450 5950 3450
Wire Wire Line
	5700 3550 5950 3550
Wire Wire Line
	8000 4850 8300 4850
Wire Wire Line
	8000 4950 8300 4950
$Comp
L 74xx_IEEE:74125 U102
U 1 1 6128A942
P 6850 3750
F 0 "U102" H 6850 4216 50  0000 C CNN
F 1 "74125" H 6850 4125 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 6850 3750 50  0001 C CNN
F 3 "" H 6850 3750 50  0001 C CNN
	1    6850 3750
	1    0    0    -1  
$EndComp
$Comp
L 74xx_IEEE:74125 U102
U 2 1 6128CAC7
P 6850 4550
F 0 "U102" H 6850 5016 50  0000 C CNN
F 1 "74125" H 6850 4925 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 6850 4550 50  0001 C CNN
F 3 "" H 6850 4550 50  0001 C CNN
	2    6850 4550
	1    0    0    -1  
$EndComp
$Comp
L 74xx_IEEE:74125 U102
U 3 1 6128D8F1
P 6850 5450
F 0 "U102" H 6850 5916 50  0000 C CNN
F 1 "74125" H 6850 5825 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 6850 5450 50  0001 C CNN
F 3 "" H 6850 5450 50  0001 C CNN
	3    6850 5450
	1    0    0    -1  
$EndComp
$Comp
L 74xx_IEEE:74125 U102
U 4 1 6128E096
P 6850 6200
F 0 "U102" H 6850 6666 50  0000 C CNN
F 1 "74125" H 6850 6575 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 6850 6200 50  0001 C CNN
F 3 "" H 6850 6200 50  0001 C CNN
	4    6850 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 3750 6200 3750
Wire Wire Line
	6200 3750 6200 3850
Wire Wire Line
	6200 3850 6350 3850
Wire Wire Line
	7350 3750 7500 3750
Wire Wire Line
	7500 3750 7500 3650
Wire Wire Line
	7500 3650 8300 3650
Wire Wire Line
	7350 4550 7500 4550
Wire Wire Line
	7500 4550 7500 4050
Wire Wire Line
	7500 4050 8000 4050
$Comp
L power:+5V #PWR0112
U 1 1 61296BEA
P 6150 5200
F 0 "#PWR0112" H 6150 5050 50  0001 C CNN
F 1 "+5V" H 6165 5373 50  0000 C CNN
F 2 "" H 6150 5200 50  0001 C CNN
F 3 "" H 6150 5200 50  0001 C CNN
	1    6150 5200
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0113
U 1 1 6129736A
P 6150 5950
F 0 "#PWR0113" H 6150 5800 50  0001 C CNN
F 1 "+5V" H 6165 6123 50  0000 C CNN
F 2 "" H 6150 5950 50  0001 C CNN
F 3 "" H 6150 5950 50  0001 C CNN
	1    6150 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 5350 6150 5350
Wire Wire Line
	6150 5350 6150 5200
Wire Wire Line
	6350 6100 6150 6100
Wire Wire Line
	6150 6100 6150 5950
Wire Wire Line
	6350 5550 6150 5550
Wire Wire Line
	6150 5550 6150 5350
Connection ~ 6150 5350
Wire Wire Line
	6350 6300 6150 6300
Wire Wire Line
	6150 6300 6150 6100
Connection ~ 6150 6100
$Comp
L power:GND #PWR0114
U 1 1 6129C13B
P 6150 4750
F 0 "#PWR0114" H 6150 4500 50  0001 C CNN
F 1 "GND" H 6155 4577 50  0000 C CNN
F 2 "" H 6150 4750 50  0001 C CNN
F 3 "" H 6150 4750 50  0001 C CNN
	1    6150 4750
	1    0    0    -1  
$EndComp
Text GLabel 7750 4450 0    50   Input ~ 0
A0
Text GLabel 5950 3050 2    50   Input ~ 0
A0
Wire Wire Line
	5700 3050 5950 3050
Wire Wire Line
	6000 3850 6000 4650
Wire Wire Line
	6000 4650 6350 4650
Wire Wire Line
	6350 4450 6150 4450
Wire Wire Line
	6150 4450 6150 4750
$EndSCHEMATC
