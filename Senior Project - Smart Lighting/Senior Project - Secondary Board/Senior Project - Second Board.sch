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
L Device:R R1
U 1 1 6066BE9F
P 5250 3600
F 0 "R1" V 5043 3600 50  0000 C CNN
F 1 "1k" V 5134 3600 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 5180 3600 50  0001 C CNN
F 3 "~" H 5250 3600 50  0001 C CNN
	1    5250 3600
	-1   0    0    1   
$EndComp
$Comp
L Device:R_PHOTO R2
U 1 1 6066CAE6
P 5250 4000
F 0 "R2" H 5320 4046 50  0000 L CNN
F 1 "R_PHOTO" H 5320 3955 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 5300 3750 50  0001 L CNN
F 3 "~" H 5250 3950 50  0001 C CNN
	1    5250 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 3750 5250 3800
Connection ~ 5250 3800
Wire Wire Line
	5250 3800 5250 3850
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 60873ADE
P 6850 3800
F 0 "J1" V 6814 3612 50  0000 R CNN
F 1 "Screw_Terminal_01x02" V 6723 3612 50  0000 R CNN
F 2 "TerminalBlock:TerminalBlock_Altech_AK300-2_P5.00mm" H 6850 3800 50  0001 C CNN
F 3 "~" H 6850 3800 50  0001 C CNN
	1    6850 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 4200 6400 4200
Wire Wire Line
	6400 4200 6400 3900
Wire Wire Line
	6400 3900 6650 3900
Wire Wire Line
	5250 3800 6650 3800
Wire Wire Line
	5250 4200 5250 4150
$Comp
L Connector:Screw_Terminal_01x02 J6
U 1 1 608CEBFA
P 5250 3000
F 0 "J6" V 5214 2812 50  0000 R CNN
F 1 "Screw_Terminal_01x02" V 5123 2812 50  0000 R CNN
F 2 "TerminalBlock:TerminalBlock_Altech_AK300-2_P5.00mm" H 5250 3000 50  0001 C CNN
F 3 "~" H 5250 3000 50  0001 C CNN
	1    5250 3000
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR03
U 1 1 608CFEB3
P 5250 4300
F 0 "#PWR03" H 5250 4050 50  0001 C CNN
F 1 "GND" H 5255 4127 50  0000 C CNN
F 2 "" H 5250 4300 50  0001 C CNN
F 3 "" H 5250 4300 50  0001 C CNN
	1    5250 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 3200 5250 3400
Wire Wire Line
	5250 4200 5250 4300
Connection ~ 5250 4200
Wire Wire Line
	5350 3200 5350 3300
Wire Wire Line
	5350 3400 6400 3400
Wire Wire Line
	6400 3400 6400 3900
Connection ~ 6400 3900
Text Notes 4950 2900 0    50   ~ 0
Power supply input
Text Notes 6500 3700 0    50   ~ 0
Light sensor output\n
$Comp
L Device:C C5
U 1 1 6089E46C
P 5100 3400
F 0 "C5" V 4848 3400 50  0000 C CNN
F 1 "0.1" V 4939 3400 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_Tantal_D4.5mm_P5.00mm" H 5138 3250 50  0001 C CNN
F 3 "~" H 5100 3400 50  0001 C CNN
	1    5100 3400
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR01
U 1 1 608A0524
P 4950 3400
F 0 "#PWR01" H 4950 3150 50  0001 C CNN
F 1 "GND" H 4955 3227 50  0000 C CNN
F 2 "" H 4950 3400 50  0001 C CNN
F 3 "" H 4950 3400 50  0001 C CNN
	1    4950 3400
	1    0    0    -1  
$EndComp
Connection ~ 5250 3400
Wire Wire Line
	5250 3400 5250 3450
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 608A1ACA
P 5350 3300
F 0 "#FLG0101" H 5350 3375 50  0001 C CNN
F 1 "PWR_FLAG" V 5350 3428 50  0000 L CNN
F 2 "" H 5350 3300 50  0001 C CNN
F 3 "~" H 5350 3300 50  0001 C CNN
	1    5350 3300
	0    1    1    0   
$EndComp
Connection ~ 5350 3300
Wire Wire Line
	5350 3300 5350 3400
$EndSCHEMATC
