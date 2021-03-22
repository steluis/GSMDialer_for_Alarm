EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Combinatore Allarme - Display 2x20 - Scatola piccola"
Date "01-01-2020"
Rev "0.1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CombinatoreGSM_Kicad-rescue:NANO_SIM_CARD_HOLDER-NANO_SIM_CARD_HOLDER U2
U 1 1 5E021763
P 7250 2500
F 0 "U2" H 7250 2500 50  0001 L BNN
F 1 "NANO_SIM_CARD_HOLDER" H 7250 2500 50  0001 L BNN
F 2 "Downloads:NANO_SIM_CARD_HOLDER" H 7250 2500 50  0001 L BNN
F 3 "" H 7250 2500 50  0001 C CNN
	1    7250 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 2200 8300 2200
Text Label 8200 2200 0    50   ~ 0
IO_SIM
$Comp
L power:GND #PWR0101
U 1 1 5E02260D
P 8100 2950
F 0 "#PWR0101" H 8100 2700 50  0001 C CNN
F 1 "GND" H 8105 2777 50  0000 C CNN
F 2 "" H 8100 2950 50  0001 C CNN
F 3 "" H 8100 2950 50  0001 C CNN
	1    8100 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 2800 8100 2800
Wire Wire Line
	8100 2800 8100 2950
Wire Wire Line
	6550 2800 6100 2800
Wire Wire Line
	6550 2500 6100 2500
Wire Wire Line
	6550 2200 6100 2200
Text Label 6100 2200 0    50   ~ 0
SIM_CLK
Text Label 6100 2500 0    50   ~ 0
SIM_RST
Text Label 6100 2800 0    50   ~ 0
SIM_VCC
$Comp
L power:GND #PWR0102
U 1 1 5E02F7EE
P 10450 4100
F 0 "#PWR0102" H 10450 3850 50  0001 C CNN
F 1 "GND" H 10455 3927 50  0000 C CNN
F 2 "" H 10450 4100 50  0001 C CNN
F 3 "" H 10450 4100 50  0001 C CNN
	1    10450 4100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5E031328
P 8050 1500
F 0 "#PWR0103" H 8050 1250 50  0001 C CNN
F 1 "GND" H 8055 1327 50  0000 C CNN
F 2 "" H 8050 1500 50  0001 C CNN
F 3 "" H 8050 1500 50  0001 C CNN
	1    8050 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 1700 8400 1700
Wire Wire Line
	8050 1500 8800 1500
Text Label 8450 1700 0    50   ~ 0
TXD
Wire Wire Line
	8800 1800 8400 1800
Text Label 8450 1800 0    50   ~ 0
RXD
$Comp
L Device:C C7
U 1 1 5E034515
P 7100 1000
F 0 "C7" H 7215 1046 50  0000 L CNN
F 1 "33pf" H 7215 955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7138 850 50  0001 C CNN
F 3 "~" H 7100 1000 50  0001 C CNN
	1    7100 1000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5E034DF8
P 6800 1000
F 0 "C4" H 6500 1050 50  0000 L CNN
F 1 "10pf" H 6500 950 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6838 850 50  0001 C CNN
F 3 "~" H 6800 1000 50  0001 C CNN
	1    6800 1000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5E035111
P 6800 650
F 0 "C3" H 6600 700 50  0000 L CNN
F 1 "33pf" H 6600 550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6838 500 50  0001 C CNN
F 3 "~" H 6800 650 50  0001 C CNN
	1    6800 650 
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 5E035539
P 7100 650
F 0 "C6" H 7215 696 50  0000 L CNN
F 1 "33pf" H 7215 605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7138 500 50  0001 C CNN
F 3 "~" H 7100 650 50  0001 C CNN
	1    7100 650 
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 5E0357D0
P 6800 1350
F 0 "C5" H 6500 1400 50  0000 L CNN
F 1 "10pf" H 6500 1300 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6838 1200 50  0001 C CNN
F 3 "~" H 6800 1350 50  0001 C CNN
	1    6800 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C8
U 1 1 5E035AE5
P 7100 1350
F 0 "C8" H 7215 1396 50  0000 L CNN
F 1 "10pf" H 7215 1305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7138 1200 50  0001 C CNN
F 3 "~" H 7100 1350 50  0001 C CNN
	1    7100 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 5E035E0D
P 6500 500
F 0 "#PWR0104" H 6500 250 50  0001 C CNN
F 1 "GND" H 6505 327 50  0000 C CNN
F 2 "" H 6500 500 50  0001 C CNN
F 3 "" H 6500 500 50  0001 C CNN
	1    6500 500 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5E0361D1
P 6500 1500
F 0 "#PWR0105" H 6500 1250 50  0001 C CNN
F 1 "GND" H 6505 1327 50  0000 C CNN
F 2 "" H 6500 1500 50  0001 C CNN
F 3 "" H 6500 1500 50  0001 C CNN
	1    6500 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 1500 6800 1500
Wire Wire Line
	6800 1500 7100 1500
Connection ~ 6800 1500
Wire Wire Line
	6800 1200 6800 1150
Wire Wire Line
	7100 1200 7100 1150
Wire Wire Line
	7100 850  7100 800 
Wire Wire Line
	6800 850  6800 800 
Wire Wire Line
	6800 1200 7100 1200
Connection ~ 6800 1200
Connection ~ 7100 1200
Connection ~ 7100 800 
Wire Wire Line
	7100 800  6800 800 
Connection ~ 6800 800 
Wire Wire Line
	7100 500  6800 500 
Wire Wire Line
	6800 500  6500 500 
Connection ~ 6800 500 
Text Label 7950 800  0    50   ~ 0
MICP
Text Label 7950 1200 0    50   ~ 0
MICN
$Comp
L Connector:Conn_01x02_Male J7
U 1 1 5E042D04
P 11000 2050
F 0 "J7" H 10972 2024 50  0000 R CNN
F 1 " " H 10972 1933 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 11000 2050 50  0001 C CNN
F 3 "~" H 11000 2050 50  0001 C CNN
	1    11000 2050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10600 2050 10800 2050
Wire Wire Line
	10600 2150 10800 2150
Text Label 10600 2050 0    50   ~ 0
SPKP
Text Label 10600 2150 0    50   ~ 0
SPKN
Wire Wire Line
	10600 1850 11000 1850
Wire Wire Line
	10600 1950 11000 1950
Text Label 10750 1850 0    50   ~ 0
MICP
Text Label 10750 1950 0    50   ~ 0
MICN
Wire Wire Line
	10600 2750 11000 2750
Text Label 10750 2750 0    50   ~ 0
IO_SIM
Wire Wire Line
	10600 2850 11000 2850
Text Label 10750 2850 0    50   ~ 0
SIM_CLK
Wire Wire Line
	10600 2950 11000 2950
Text Label 10750 2950 0    50   ~ 0
SIM_RST
Wire Wire Line
	10600 2650 11000 2650
Text Label 10750 2650 0    50   ~ 0
SIM_VCC
$Comp
L Connector:Conn_Coaxial J6
U 1 1 5E04F08F
P 11000 1100
F 0 "J6" H 11100 1075 50  0000 L CNN
F 1 " " H 11100 984 50  0000 L CNN
F 2 "Connector_Coaxial:U.FL_Hirose_U.FL-R-SMT-1_Vertical" H 11000 1100 50  0001 C CNN
F 3 " ~" H 11000 1100 50  0001 C CNN
	1    11000 1100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5E04F6B3
P 11000 1450
F 0 "#PWR0106" H 11000 1200 50  0001 C CNN
F 1 "GND" H 11005 1277 50  0000 C CNN
F 2 "" H 11000 1450 50  0001 C CNN
F 3 "" H 11000 1450 50  0001 C CNN
	1    11000 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	11000 1300 11000 1450
Wire Wire Line
	10800 1100 10800 1450
Wire Wire Line
	10800 1450 10600 1450
$Comp
L power:+4V #PWR0107
U 1 1 5E051B06
P 10450 700
F 0 "#PWR0107" H 10450 550 50  0001 C CNN
F 1 "+4V" H 10465 873 50  0000 C CNN
F 2 "" H 10450 700 50  0001 C CNN
F 3 "" H 10450 700 50  0001 C CNN
	1    10450 700 
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C9
U 1 1 5E05A808
P 10700 800
F 0 "C9" H 10788 846 50  0000 L CNN
F 1 "1000uf" H 10788 755 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_10x10" H 10700 800 50  0001 C CNN
F 3 "~" H 10700 800 50  0001 C CNN
	1    10700 800 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 5E05C2C3
P 10700 950
F 0 "#PWR0108" H 10700 700 50  0001 C CNN
F 1 "GND" H 10705 777 50  0000 C CNN
F 2 "" H 10700 950 50  0001 C CNN
F 3 "" H 10700 950 50  0001 C CNN
	1    10700 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	10700 900  10700 950 
Wire Wire Line
	10700 700  10450 700 
Wire Wire Line
	10450 700  10450 900 
Connection ~ 10450 700 
$Comp
L Device:LED D2
U 1 1 5E05F4F5
P 10800 3300
F 0 "D2" V 10839 3183 50  0000 R CNN
F 1 "LED" V 10748 3183 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 10800 3300 50  0001 C CNN
F 3 "~" H 10800 3300 50  0001 C CNN
	1    10800 3300
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 5E061C0C
P 10800 4100
F 0 "#PWR0109" H 10800 3850 50  0001 C CNN
F 1 "GND" H 10805 3927 50  0000 C CNN
F 2 "" H 10800 4100 50  0001 C CNN
F 3 "" H 10800 4100 50  0001 C CNN
	1    10800 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10600 2350 11050 2350
Text Label 10700 2350 0    50   ~ 0
LED_RETE
Wire Wire Line
	10800 3150 10500 3150
Text Label 10500 3150 0    50   ~ 0
LED_RETE
$Comp
L Device:R_US R2
U 1 1 5E064BE7
P 10800 3800
F 0 "R2" H 10868 3846 50  0000 L CNN
F 1 "220" H 10868 3755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 10840 3790 50  0001 C CNN
F 3 "~" H 10800 3800 50  0001 C CNN
	1    10800 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	10450 4100 10450 3800
Wire Wire Line
	10800 3450 10800 3650
Wire Wire Line
	10800 3950 10800 4100
$Comp
L MCU_Microchip_ATmega:ATmega328P-PU U1
U 1 1 5E06E3AB
P 1400 2650
F 0 "U1" H 850 4200 50  0000 R CNN
F 1 "ATmega328P-PU" H 1200 4100 50  0000 R CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 1400 2650 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf" H 1400 2650 50  0001 C CNN
	1    1400 2650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0110
U 1 1 5E072B81
P 1400 800
F 0 "#PWR0110" H 1400 650 50  0001 C CNN
F 1 "+5V" H 1415 973 50  0000 C CNN
F 2 "" H 1400 800 50  0001 C CNN
F 3 "" H 1400 800 50  0001 C CNN
	1    1400 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 1150 1400 1000
Wire Wire Line
	1500 1150 1500 1000
Wire Wire Line
	1500 1000 1400 1000
Connection ~ 1400 1000
Wire Wire Line
	1400 1000 1400 800 
Wire Wire Line
	2000 2450 2150 2450
Wire Wire Line
	2000 2550 2550 2550
Text Label 2450 2550 0    50   ~ 0
OUT1
Wire Wire Line
	2000 2650 2550 2650
Text Label 2450 2650 0    50   ~ 0
OUT2
$Comp
L Connector:Conn_01x04_Male J3
U 1 1 5E07C70A
P 3800 1250
F 0 "J3" H 3772 1224 50  0000 R CNN
F 1 "Display" H 3772 1133 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal" H 3800 1250 50  0001 C CNN
F 3 "~" H 3800 1250 50  0001 C CNN
	1    3800 1250
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 5E07D366
P 3300 1150
F 0 "#PWR0111" H 3300 900 50  0001 C CNN
F 1 "GND" H 3305 977 50  0000 C CNN
F 2 "" H 3300 1150 50  0001 C CNN
F 3 "" H 3300 1150 50  0001 C CNN
	1    3300 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 1150 3300 1150
$Comp
L power:+5V #PWR0112
U 1 1 5E07F583
P 3450 1000
F 0 "#PWR0112" H 3450 850 50  0001 C CNN
F 1 "+5V" H 3465 1173 50  0000 C CNN
F 2 "" H 3450 1000 50  0001 C CNN
F 3 "" H 3450 1000 50  0001 C CNN
	1    3450 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 1250 3450 1250
Wire Wire Line
	3450 1250 3450 1000
Wire Wire Line
	3600 1350 3450 1350
Wire Wire Line
	3450 1350 3450 2300
Wire Wire Line
	3600 1450 3550 1450
Wire Wire Line
	3550 1450 3550 2400
$Comp
L Connector:Conn_01x03_Male J2
U 1 1 5E086269
P 3150 3250
F 0 "J2" H 3250 3100 50  0000 R CNN
F 1 "SER" H 3150 3100 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 3150 3250 50  0001 C CNN
F 3 "~" H 3150 3250 50  0001 C CNN
	1    3150 3250
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0113
U 1 1 5E089202
P 2800 3350
F 0 "#PWR0113" H 2800 3100 50  0001 C CNN
F 1 "GND" H 2805 3177 50  0000 C CNN
F 2 "" H 2800 3350 50  0001 C CNN
F 3 "" H 2800 3350 50  0001 C CNN
	1    2800 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 3350 2800 3350
Wire Wire Line
	2950 3150 2000 3150
Wire Wire Line
	2950 3250 2000 3250
$Comp
L Device:D D1
U 1 1 5E091059
P 3400 2750
F 0 "D1" H 3400 2966 50  0000 C CNN
F 1 "1N4148" H 3400 2875 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 3400 2750 50  0001 C CNN
F 3 "~" H 3400 2750 50  0001 C CNN
	1    3400 2750
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_US R1
U 1 1 5E093B43
P 3400 2950
F 0 "R1" V 3500 3100 50  0000 C CNN
F 1 "220" V 3500 2950 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3440 2940 50  0001 C CNN
F 3 "~" H 3400 2950 50  0001 C CNN
	1    3400 2950
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR0114
U 1 1 5E095B36
P 3750 2650
F 0 "#PWR0114" H 3750 2500 50  0001 C CNN
F 1 "+5V" H 3765 2823 50  0000 C CNN
F 2 "" H 3750 2650 50  0001 C CNN
F 3 "" H 3750 2650 50  0001 C CNN
	1    3750 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 2750 3550 2950
Wire Wire Line
	3550 2950 3750 2950
Wire Wire Line
	3750 2950 3750 2650
Connection ~ 3550 2950
Wire Wire Line
	3250 2750 3250 2950
Wire Wire Line
	3250 2950 2000 2950
Connection ~ 3250 2950
$Comp
L Connector:Conn_01x02_Male J4
U 1 1 5E0A02AD
P 3850 3200
F 0 "J4" H 3822 3174 50  0000 R CNN
F 1 "RST" H 3822 3083 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3850 3200 50  0001 C CNN
F 3 "~" H 3850 3200 50  0001 C CNN
	1    3850 3200
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 5E0A1F92
P 3650 3450
F 0 "#PWR0115" H 3650 3200 50  0001 C CNN
F 1 "GND" H 3655 3277 50  0000 C CNN
F 2 "" H 3650 3450 50  0001 C CNN
F 3 "" H 3650 3450 50  0001 C CNN
	1    3650 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 3300 3650 3450
Wire Wire Line
	3650 3200 3250 3200
Wire Wire Line
	3250 3200 3250 2950
$Comp
L Device:Crystal Y1
U 1 1 5E0AAA8C
P 2850 1900
F 0 "Y1" V 2804 2031 50  0000 L CNN
F 1 "Crystal" V 2895 2031 50  0000 L CNN
F 2 "Crystal:Crystal_HC49-4H_Vertical" H 2850 1900 50  0001 C CNN
F 3 "~" H 2850 1900 50  0001 C CNN
	1    2850 1900
	0    1    1    0   
$EndComp
Wire Wire Line
	3000 2750 3000 2300
Wire Wire Line
	3000 2300 3450 2300
Wire Wire Line
	2000 2750 3000 2750
Wire Wire Line
	3550 2400 3100 2400
Wire Wire Line
	3100 2400 3100 2850
Wire Wire Line
	2000 2850 3100 2850
$Comp
L Device:C C1
U 1 1 5E0B7D52
P 2850 1550
F 0 "C1" H 2700 1650 50  0000 L CNN
F 1 "22pf" H 2900 1450 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 2888 1400 50  0001 C CNN
F 3 "~" H 2850 1550 50  0001 C CNN
	1    2850 1550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5E0B887F
P 2850 2250
F 0 "C2" H 2900 2400 50  0000 L CNN
F 1 "22pf" H 2950 2300 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 2888 2100 50  0001 C CNN
F 3 "~" H 2850 2250 50  0001 C CNN
	1    2850 2250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 5E0B931B
P 2850 2500
F 0 "#PWR0116" H 2850 2250 50  0001 C CNN
F 1 "GND" H 2855 2327 50  0000 C CNN
F 2 "" H 2850 2500 50  0001 C CNN
F 3 "" H 2850 2500 50  0001 C CNN
	1    2850 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 2500 2850 2400
Wire Wire Line
	2850 2100 2850 2050
Wire Wire Line
	2850 1750 2850 1700
$Comp
L power:GND #PWR0117
U 1 1 5E0C2720
P 3100 1400
F 0 "#PWR0117" H 3100 1150 50  0001 C CNN
F 1 "GND" H 3105 1227 50  0000 C CNN
F 2 "" H 3100 1400 50  0001 C CNN
F 3 "" H 3100 1400 50  0001 C CNN
	1    3100 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 1400 3100 1400
Wire Wire Line
	2000 2050 2450 2050
Wire Wire Line
	2450 2050 2450 1750
Wire Wire Line
	2450 1750 2850 1750
Connection ~ 2850 1750
Wire Wire Line
	2000 2150 2550 2150
Wire Wire Line
	2550 2150 2550 2050
Wire Wire Line
	2550 2050 2850 2050
Connection ~ 2850 2050
$Comp
L Connector:Conn_01x01_Male J1
U 1 1 5E0CD938
P 5750 650
F 0 "J1" H 5722 674 50  0000 R CNN
F 1 "GND_PR" H 5722 583 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 5750 650 50  0001 C CNN
F 3 "~" H 5750 650 50  0001 C CNN
	1    5750 650 
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0118
U 1 1 5E0CE3B0
P 5550 750
F 0 "#PWR0118" H 5550 500 50  0001 C CNN
F 1 "GND" H 5555 577 50  0000 C CNN
F 2 "" H 5550 750 50  0001 C CNN
F 3 "" H 5550 750 50  0001 C CNN
	1    5550 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 650  5550 750 
Wire Wire Line
	2000 1450 2400 1450
Text Label 2250 1450 0    50   ~ 0
OK
Wire Wire Line
	2000 1650 2400 1650
Text Label 2250 1650 0    50   ~ 0
OFF_AMPLI
$Comp
L power:GND #PWR0119
U 1 1 5E0DE454
P 1400 4200
F 0 "#PWR0119" H 1400 3950 50  0001 C CNN
F 1 "GND" H 1405 4027 50  0000 C CNN
F 2 "" H 1400 4200 50  0001 C CNN
F 3 "" H 1400 4200 50  0001 C CNN
	1    1400 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 4150 1400 4200
NoConn ~ 7950 2500
$Comp
L Regulator_Switching:LM2596S-ADJ U5
U 1 1 5E05927D
P 4900 5750
F 0 "U5" H 4900 6117 50  0000 C CNN
F 1 "LM2596S-ADJ" H 4900 6026 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-263-5_TabPin3" H 4950 5500 50  0001 L CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm2596.pdf" H 4900 5750 50  0001 C CNN
	1    4900 5750
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LM7805_TO220 U6
U 1 1 5E05B0F2
P 4200 7050
F 0 "U6" H 4200 7292 50  0000 C CNN
F 1 "LM7805_TO220" H 4200 7201 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Horizontal_TabDown" H 4200 7275 50  0001 C CIN
F 3 "http://www.fairchildsemi.com/ds/LM/LM7805.pdf" H 4200 7000 50  0001 C CNN
	1    4200 7050
	1    0    0    -1  
$EndComp
$Comp
L Relay:G6K-2 K1
U 1 1 5E0624F3
P 5800 3750
F 0 "K1" H 6430 3796 50  0000 L CNN
F 1 " G6K-2F-Y" H 6250 3500 50  0000 L CNN
F 2 "Relay_SMD:Relay_DPDT_Omron_G6K-2F-Y" H 5800 3750 50  0001 L CNN
F 3 "http://omronfs.omron.com/en_US/ecb/products/pdf/en-g6k.pdf" H 5800 3750 50  0001 C CNN
	1    5800 3750
	1    0    0    -1  
$EndComp
$Comp
L MicroSwitchSimbol:5-1437565-0 SW_UP1
U 1 1 5E0773DA
P 4900 1650
F 0 "SW_UP1" H 4900 1800 50  0000 C CNN
F 1 " " H 4900 1829 50  0000 C CNN
F 2 "PulsanteDipSwitch:PULSANTE_DIP_SWITCH" H 4900 1650 50  0001 L BNN
F 3 "5-1437565-0" H 4900 1650 50  0001 L BNN
F 4 "https://www.te.com/usa-en/product-5-1437565-0.html?te_bu=Cor&te_type=disp&te_campaign=seda_glo_cor-seda-global-disp-prtnr-fy19-seda-model-bom-cta_sma-317_1&elqCampaignId=32493" H 4900 1650 50  0001 L BNN "Field4"
	1    4900 1650
	1    0    0    -1  
$EndComp
$Comp
L MicroSwitchSimbol:5-1437565-0 SW_DOWN1
U 1 1 5E0785B1
P 4900 2450
F 0 "SW_DOWN1" H 4900 2600 50  0000 C CNN
F 1 " " H 4900 2629 50  0000 C CNN
F 2 "PulsanteDipSwitch:PULSANTE_DIP_SWITCH" H 4900 2450 50  0001 L BNN
F 3 "5-1437565-0" H 4900 2450 50  0001 L BNN
F 4 "https://www.te.com/usa-en/product-5-1437565-0.html?te_bu=Cor&te_type=disp&te_campaign=seda_glo_cor-seda-global-disp-prtnr-fy19-seda-model-bom-cta_sma-317_1&elqCampaignId=32493" H 4900 2450 50  0001 L BNN "Field4"
	1    4900 2450
	1    0    0    -1  
$EndComp
$Comp
L MicroSwitchSimbol:5-1437565-0 SW_OK1
U 1 1 5E078C60
P 4900 2050
F 0 "SW_OK1" H 4900 2200 50  0000 C CNN
F 1 " " H 4900 2229 50  0000 C CNN
F 2 "PulsanteDipSwitch:PULSANTE_DIP_SWITCH" H 4900 2050 50  0001 L BNN
F 3 "5-1437565-0" H 4900 2050 50  0001 L BNN
F 4 "https://www.te.com/usa-en/product-5-1437565-0.html?te_bu=Cor&te_type=disp&te_campaign=seda_glo_cor-seda-global-disp-prtnr-fy19-seda-model-bom-cta_sma-317_1&elqCampaignId=32493" H 4900 2050 50  0001 L BNN "Field4"
	1    4900 2050
	1    0    0    -1  
$EndComp
$Comp
L MicroSwitchSimbol:5-1437565-0 SW_RIGHT1
U 1 1 5E07932D
P 5600 2050
F 0 "SW_RIGHT1" H 5600 2200 50  0000 C CNN
F 1 " " H 5600 2229 50  0000 C CNN
F 2 "PulsanteDipSwitch:PULSANTE_DIP_SWITCH" H 5600 2050 50  0001 L BNN
F 3 "5-1437565-0" H 5600 2050 50  0001 L BNN
F 4 "https://www.te.com/usa-en/product-5-1437565-0.html?te_bu=Cor&te_type=disp&te_campaign=seda_glo_cor-seda-global-disp-prtnr-fy19-seda-model-bom-cta_sma-317_1&elqCampaignId=32493" H 5600 2050 50  0001 L BNN "Field4"
	1    5600 2050
	1    0    0    -1  
$EndComp
$Comp
L MicroSwitchSimbol:5-1437565-0 SW_LEFT1
U 1 1 5E07974E
P 4200 2050
F 0 "SW_LEFT1" H 4200 2200 50  0000 C CNN
F 1 " " H 4200 2229 50  0000 C CNN
F 2 "PulsanteDipSwitch:PULSANTE_DIP_SWITCH" H 4200 2050 50  0001 L BNN
F 3 "5-1437565-0" H 4200 2050 50  0001 L BNN
F 4 "https://www.te.com/usa-en/product-5-1437565-0.html?te_bu=Cor&te_type=disp&te_campaign=seda_glo_cor-seda-global-disp-prtnr-fy19-seda-model-bom-cta_sma-317_1&elqCampaignId=32493" H 4200 2050 50  0001 L BNN "Field4"
	1    4200 2050
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x03 J9
U 1 1 5E0881DD
P 7100 3700
F 0 "J9" H 7180 3742 50  0000 L CNN
F 1 " " H 7180 3651 50  0000 L CNN
F 2 "TerminalBlock_4Ucon:TerminalBlock_4Ucon_1x03_P3.50mm_Horizontal" H 7100 3700 50  0001 C CNN
F 3 "~" H 7100 3700 50  0001 C CNN
	1    7100 3700
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J10
U 1 1 5E1A57F0
P 2900 7250
F 0 "J10" H 2900 7050 50  0000 L CNN
F 1 "12V" H 3000 7200 50  0000 L CNN
F 2 "TerminalBlock_4Ucon:TerminalBlock_4Ucon_1x02_P3.50mm_Horizontal" H 2900 7250 50  0001 C CNN
F 3 "~" H 2900 7250 50  0001 C CNN
	1    2900 7250
	-1   0    0    1   
$EndComp
$Comp
L Device:CP_Small C16
U 1 1 5E1A71BA
P 3300 7200
F 0 "C16" H 3350 7250 50  0000 L CNN
F 1 "100uf" H 3300 7150 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x5.9" H 3300 7200 50  0001 C CNN
F 3 "~" H 3300 7200 50  0001 C CNN
	1    3300 7200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C17
U 1 1 5E1A7970
P 3650 7200
F 0 "C17" H 3450 7150 50  0000 L CNN
F 1 "100nf" H 3400 7300 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3688 7050 50  0001 C CNN
F 3 "~" H 3650 7200 50  0001 C CNN
	1    3650 7200
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR011
U 1 1 5E1AA79D
P 4200 7450
F 0 "#PWR011" H 4200 7200 50  0001 C CNN
F 1 "GND" H 4205 7277 50  0000 C CNN
F 2 "" H 4200 7450 50  0001 C CNN
F 3 "" H 4200 7450 50  0001 C CNN
	1    4200 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 7350 4200 7450
Wire Wire Line
	3100 7150 3150 7150
Wire Wire Line
	3150 7150 3150 7100
Wire Wire Line
	3150 7100 3300 7100
Wire Wire Line
	3300 7100 3450 7100
Wire Wire Line
	3450 7100 3450 7050
Wire Wire Line
	3450 7050 3650 7050
Connection ~ 3300 7100
Wire Wire Line
	3650 7050 3900 7050
Connection ~ 3650 7050
Wire Wire Line
	3100 7250 3150 7250
Wire Wire Line
	3150 7250 3150 7300
Wire Wire Line
	3150 7300 3300 7300
Wire Wire Line
	3300 7300 3450 7300
Wire Wire Line
	3450 7300 3450 7350
Wire Wire Line
	3450 7350 3650 7350
Connection ~ 3300 7300
Wire Wire Line
	3650 7350 4200 7350
Connection ~ 3650 7350
Connection ~ 4200 7350
$Comp
L Device:CP_Small C20
U 1 1 5E1E2B19
P 4650 7150
F 0 "C20" H 4700 7200 50  0000 L CNN
F 1 "100uf" H 4650 7100 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x5.9" H 4650 7150 50  0001 C CNN
F 3 "~" H 4650 7150 50  0001 C CNN
	1    4650 7150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C21
U 1 1 5E1E2F0B
P 5000 7150
F 0 "C21" H 4800 7100 50  0000 L CNN
F 1 "100nf" H 4750 7250 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5038 7000 50  0001 C CNN
F 3 "~" H 5000 7150 50  0001 C CNN
	1    5000 7150
	-1   0    0    1   
$EndComp
Wire Wire Line
	4500 7050 4650 7050
Wire Wire Line
	4650 7050 4750 7050
Wire Wire Line
	4750 7050 4750 7000
Wire Wire Line
	4750 7000 5000 7000
Connection ~ 4650 7050
Wire Wire Line
	4200 7350 4650 7350
Wire Wire Line
	4650 7350 4650 7250
Wire Wire Line
	4650 7350 5000 7350
Wire Wire Line
	5000 7350 5000 7300
Connection ~ 4650 7350
$Comp
L power:+5V #PWR017
U 1 1 5E207685
P 4750 6950
F 0 "#PWR017" H 4750 6800 50  0001 C CNN
F 1 "+5V" H 4765 7123 50  0000 C CNN
F 2 "" H 4750 6950 50  0001 C CNN
F 3 "" H 4750 6950 50  0001 C CNN
	1    4750 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 7000 4750 6950
Connection ~ 4750 7000
$Comp
L Device:CP_Small C18
U 1 1 5E212641
P 3750 5700
F 0 "C18" H 3800 5750 50  0000 L CNN
F 1 "100uf" H 3750 5650 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x5.9" H 3750 5700 50  0001 C CNN
F 3 "~" H 3750 5700 50  0001 C CNN
	1    3750 5700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C19
U 1 1 5E2129C3
P 4100 5700
F 0 "C19" H 4215 5746 50  0000 L CNN
F 1 "1uf" H 4215 5655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4138 5550 50  0001 C CNN
F 3 "~" H 4100 5700 50  0001 C CNN
	1    4100 5700
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR07
U 1 1 5E2130A6
P 3450 7000
F 0 "#PWR07" H 3450 6850 50  0001 C CNN
F 1 "+12V" H 3465 7173 50  0000 C CNN
F 2 "" H 3450 7000 50  0001 C CNN
F 3 "" H 3450 7000 50  0001 C CNN
	1    3450 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 7050 3450 7000
Connection ~ 3450 7050
$Comp
L power:+12V #PWR08
U 1 1 5E21D92A
P 3750 5500
F 0 "#PWR08" H 3750 5350 50  0001 C CNN
F 1 "+12V" H 3765 5673 50  0000 C CNN
F 2 "" H 3750 5500 50  0001 C CNN
F 3 "" H 3750 5500 50  0001 C CNN
	1    3750 5500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5E21E616
P 4100 6100
F 0 "#PWR010" H 4100 5850 50  0001 C CNN
F 1 "GND" H 4105 5927 50  0000 C CNN
F 2 "" H 4100 6100 50  0001 C CNN
F 3 "" H 4100 6100 50  0001 C CNN
	1    4100 6100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR019
U 1 1 5E21EACD
P 4900 6100
F 0 "#PWR019" H 4900 5850 50  0001 C CNN
F 1 "GND" H 4905 5927 50  0000 C CNN
F 2 "" H 4900 6100 50  0001 C CNN
F 3 "" H 4900 6100 50  0001 C CNN
	1    4900 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 5850 4400 6050
Wire Wire Line
	4400 6050 4900 6050
Wire Wire Line
	4900 6050 4900 6100
Connection ~ 4900 6050
Wire Wire Line
	4400 6050 4100 6050
Wire Wire Line
	4100 6050 4100 5850
Connection ~ 4400 6050
Wire Wire Line
	4100 6100 4100 6050
Connection ~ 4100 6050
Wire Wire Line
	4400 5650 4400 5550
Wire Wire Line
	4400 5550 4100 5550
Wire Wire Line
	3750 5600 3750 5550
Wire Wire Line
	3750 5800 3750 6050
Wire Wire Line
	3750 6050 4100 6050
Wire Wire Line
	4100 5550 3750 5550
Connection ~ 4100 5550
Connection ~ 3750 5550
Wire Wire Line
	3750 5550 3750 5500
$Comp
L power:GND #PWR023
U 1 1 5E29B29E
P 5600 6200
F 0 "#PWR023" H 5600 5950 50  0001 C CNN
F 1 "GND" H 5605 6027 50  0000 C CNN
F 2 "" H 5600 6200 50  0001 C CNN
F 3 "" H 5600 6200 50  0001 C CNN
	1    5600 6200
	1    0    0    -1  
$EndComp
$Comp
L Diode:MBR340 D4
U 1 1 5E29998B
P 5600 6000
F 0 "D4" V 5554 6079 50  0000 L CNN
F 1 "MBR360" V 5645 6079 50  0000 L CNN
F 2 "Diode_SMD:D_2010_5025Metric" H 5600 5825 50  0001 C CNN
F 3 "http://www.onsemi.com/pub_link/Collateral/MBR340-D.PDF" H 5600 6000 50  0001 C CNN
	1    5600 6000
	0    1    1    0   
$EndComp
$Comp
L Device:L_Small L1
U 1 1 5E2B2A8D
P 5800 5850
F 0 "L1" V 5985 5850 50  0000 C CNN
F 1 "100uH" V 5894 5850 50  0000 C CNN
F 2 "Inductor_THT:L_Axial_L7.0mm_D3.3mm_P12.70mm_Horizontal_Fastron_MICC" H 5800 5850 50  0001 C CNN
F 3 "~" H 5800 5850 50  0001 C CNN
	1    5800 5850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5400 5850 5600 5850
Wire Wire Line
	5600 5850 5700 5850
Connection ~ 5600 5850
$Comp
L Device:CP_Small C22
U 1 1 5E2C94C4
P 6100 6000
F 0 "C22" H 6150 6050 50  0000 L CNN
F 1 "330uf" H 6150 5900 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x5.9" H 6100 6000 50  0001 C CNN
F 3 "~" H 6100 6000 50  0001 C CNN
	1    6100 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 6150 5600 6200
$Comp
L Device:C C23
U 1 1 5E340520
P 6450 6000
F 0 "C23" H 6565 6046 50  0000 L CNN
F 1 "100nf" H 6565 5955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6488 5850 50  0001 C CNN
F 3 "~" H 6450 6000 50  0001 C CNN
	1    6450 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 5850 6100 5850
Wire Wire Line
	6100 5850 6100 5900
Wire Wire Line
	6100 5850 6450 5850
Connection ~ 6100 5850
Wire Wire Line
	6450 6150 6100 6150
Wire Wire Line
	6100 6150 6100 6100
Wire Wire Line
	6100 6150 5600 6150
Connection ~ 6100 6150
Connection ~ 5600 6150
$Comp
L Device:R_US R6
U 1 1 5E36EFA9
P 6450 5650
F 0 "R6" H 6518 5696 50  0000 L CNN
F 1 "2.2K" H 6518 5605 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6490 5640 50  0001 C CNN
F 3 "~" H 6450 5650 50  0001 C CNN
	1    6450 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 5850 6450 5800
Connection ~ 6450 5850
Wire Wire Line
	6450 5500 5400 5500
Wire Wire Line
	5400 5500 5400 5650
$Comp
L power:+4V #PWR024
U 1 1 5E387F08
P 6850 5850
F 0 "#PWR024" H 6850 5700 50  0001 C CNN
F 1 "+4V" H 6865 6023 50  0000 C CNN
F 2 "" H 6850 5850 50  0001 C CNN
F 3 "" H 6850 5850 50  0001 C CNN
	1    6850 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 5850 6850 5850
$Comp
L Device:R_US R7
U 1 1 5E394826
P 6800 5500
F 0 "R7" V 6700 5600 50  0000 L CNN
F 1 "1K" V 6700 5400 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6840 5490 50  0001 C CNN
F 3 "~" H 6800 5500 50  0001 C CNN
	1    6800 5500
	0    1    1    0   
$EndComp
Wire Wire Line
	6650 5500 6450 5500
Connection ~ 6450 5500
$Comp
L power:GND #PWR025
U 1 1 5E3A152B
P 7050 6150
F 0 "#PWR025" H 7050 5900 50  0001 C CNN
F 1 "GND" H 7055 5977 50  0000 C CNN
F 2 "" H 7050 6150 50  0001 C CNN
F 3 "" H 7050 6150 50  0001 C CNN
	1    7050 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 5500 7050 5500
Wire Wire Line
	7050 5500 7050 6150
$Comp
L power:GND #PWR09
U 1 1 5E3D72C1
P 3900 2100
F 0 "#PWR09" H 3900 1850 50  0001 C CNN
F 1 "GND" H 3905 1927 50  0000 C CNN
F 2 "" H 3900 2100 50  0001 C CNN
F 3 "" H 3900 2100 50  0001 C CNN
	1    3900 2100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR014
U 1 1 5E3D77DD
P 4600 2100
F 0 "#PWR014" H 4600 1850 50  0001 C CNN
F 1 "GND" H 4605 1927 50  0000 C CNN
F 2 "" H 4600 2100 50  0001 C CNN
F 3 "" H 4600 2100 50  0001 C CNN
	1    4600 2100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR021
U 1 1 5E3D7BBB
P 5300 2100
F 0 "#PWR021" H 5300 1850 50  0001 C CNN
F 1 "GND" H 5305 1927 50  0000 C CNN
F 2 "" H 5300 2100 50  0001 C CNN
F 3 "" H 5300 2100 50  0001 C CNN
	1    5300 2100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 5E3D81F2
P 4600 2500
F 0 "#PWR015" H 4600 2250 50  0001 C CNN
F 1 "GND" H 4605 2327 50  0000 C CNN
F 2 "" H 4600 2500 50  0001 C CNN
F 3 "" H 4600 2500 50  0001 C CNN
	1    4600 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR013
U 1 1 5E3D879F
P 4600 1700
F 0 "#PWR013" H 4600 1450 50  0001 C CNN
F 1 "GND" H 4605 1527 50  0000 C CNN
F 2 "" H 4600 1700 50  0001 C CNN
F 3 "" H 4600 1700 50  0001 C CNN
	1    4600 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 3550 2500 3550
Text Label 2350 3550 0    50   ~ 0
UP
Wire Wire Line
	2000 3650 2500 3650
Text Label 2350 3650 0    50   ~ 0
DOWN
Wire Wire Line
	2000 3750 2500 3750
Text Label 2350 3750 0    50   ~ 0
RIGHT
Wire Wire Line
	2000 3850 2500 3850
Text Label 2350 3850 0    50   ~ 0
LEFT
Wire Wire Line
	4600 1650 4600 1700
Wire Wire Line
	3900 2050 3900 2100
Wire Wire Line
	4600 2050 4600 2100
Wire Wire Line
	5300 2050 5300 2100
Wire Wire Line
	4600 2450 4600 2500
Wire Wire Line
	5200 1650 5350 1650
Text Label 5250 1650 0    50   ~ 0
UP
Wire Wire Line
	5900 2050 6100 2050
Text Label 5900 2050 0    50   ~ 0
RIGHT
Wire Wire Line
	5200 2050 5200 1900
Text Label 5200 1950 0    50   ~ 0
OK
Wire Wire Line
	5200 2450 5200 2650
Text Label 5200 2600 0    50   ~ 0
DOWN
Wire Wire Line
	4500 2050 4500 2300
Wire Wire Line
	4500 2300 4250 2300
Text Label 4250 2300 0    50   ~ 0
LEFT
$Comp
L Device:R_US R4
U 1 1 5E528F9F
P 4850 4450
F 0 "R4" V 4950 4400 50  0000 L CNN
F 1 "4.7K" V 4750 4400 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4890 4440 50  0001 C CNN
F 3 "~" H 4850 4450 50  0001 C CNN
	1    4850 4450
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R5
U 1 1 5E52AB1F
P 5100 4700
F 0 "R5" H 5150 4700 50  0000 L CNN
F 1 "4.7K" V 5000 4650 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5140 4690 50  0001 C CNN
F 3 "~" H 5100 4700 50  0001 C CNN
	1    5100 4700
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR020
U 1 1 5E52AEAF
P 5100 4900
F 0 "#PWR020" H 5100 4650 50  0001 C CNN
F 1 "GND" H 5105 4727 50  0000 C CNN
F 2 "" H 5100 4900 50  0001 C CNN
F 3 "" H 5100 4900 50  0001 C CNN
	1    5100 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 4550 5100 4450
Wire Wire Line
	5100 4450 5000 4450
Wire Wire Line
	4700 4450 4400 4450
Wire Wire Line
	5100 4900 5100 4850
Wire Wire Line
	5400 4650 5400 4900
Wire Wire Line
	5400 4900 5100 4900
Connection ~ 5100 4900
$Comp
L power:+5V #PWR022
U 1 1 5E5F0A8D
P 5400 3350
F 0 "#PWR022" H 5400 3200 50  0001 C CNN
F 1 "+5V" H 5415 3523 50  0000 C CNN
F 2 "" H 5400 3350 50  0001 C CNN
F 3 "" H 5400 3350 50  0001 C CNN
	1    5400 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 3350 5400 3400
Wire Wire Line
	5400 4050 5400 4150
Wire Wire Line
	5800 4050 5800 4250
Wire Wire Line
	5800 4250 6700 4250
Wire Wire Line
	6700 4250 6700 3700
Wire Wire Line
	6700 3700 6900 3700
Wire Wire Line
	6900 3600 6900 3200
Wire Wire Line
	6900 3200 5700 3200
Wire Wire Line
	5700 3200 5700 3450
Wire Wire Line
	6900 3800 6750 3800
Wire Wire Line
	6750 3800 6750 3350
Wire Wire Line
	6750 3350 5900 3350
Wire Wire Line
	5900 3350 5900 3450
$Comp
L Device:D_Small D3
U 1 1 5E642B0F
P 4950 3700
F 0 "D3" V 4900 3550 50  0000 L CNN
F 1 "1N4148" V 5050 3400 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" V 4950 3700 50  0001 C CNN
F 3 "~" V 4950 3700 50  0001 C CNN
	1    4950 3700
	0    1    1    0   
$EndComp
Wire Wire Line
	4950 3600 4950 3400
Wire Wire Line
	4950 3400 5400 3400
Connection ~ 5400 3400
Wire Wire Line
	5400 3400 5400 3450
Wire Wire Line
	4950 3800 4950 4150
Wire Wire Line
	4950 4150 5400 4150
Connection ~ 5400 4150
Wire Wire Line
	5400 4150 5400 4250
$Comp
L Relay:G6K-2 K2
U 1 1 5E66AE21
P 8900 4800
F 0 "K2" H 9530 4846 50  0000 L CNN
F 1 " G6K-2F-Y" H 9300 4550 50  0000 L CNN
F 2 "Relay_SMD:Relay_DPDT_Omron_G6K-2F-Y" H 8900 4800 50  0001 L CNN
F 3 "http://omronfs.omron.com/en_US/ecb/products/pdf/en-g6k.pdf" H 8900 4800 50  0001 C CNN
	1    8900 4800
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x03 J11
U 1 1 5E66AE2D
P 10200 4750
F 0 "J11" H 10280 4792 50  0000 L CNN
F 1 " " H 10280 4701 50  0000 L CNN
F 2 "TerminalBlock_4Ucon:TerminalBlock_4Ucon_1x03_P3.50mm_Horizontal" H 10200 4750 50  0001 C CNN
F 3 "~" H 10200 4750 50  0001 C CNN
	1    10200 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R8
U 1 1 5E66AE33
P 7950 5500
F 0 "R8" V 8050 5450 50  0000 L CNN
F 1 "4.7K" V 7850 5450 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7990 5490 50  0001 C CNN
F 3 "~" H 7950 5500 50  0001 C CNN
	1    7950 5500
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R9
U 1 1 5E66AE39
P 8200 5750
F 0 "R9" H 8250 5750 50  0000 L CNN
F 1 "4.7K" V 8100 5700 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 8240 5740 50  0001 C CNN
F 3 "~" H 8200 5750 50  0001 C CNN
	1    8200 5750
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR026
U 1 1 5E66AE3F
P 8200 5950
F 0 "#PWR026" H 8200 5700 50  0001 C CNN
F 1 "GND" H 8205 5777 50  0000 C CNN
F 2 "" H 8200 5950 50  0001 C CNN
F 3 "" H 8200 5950 50  0001 C CNN
	1    8200 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 5600 8200 5500
Wire Wire Line
	8200 5500 8100 5500
Wire Wire Line
	8200 5950 8200 5900
Wire Wire Line
	8500 5700 8500 5950
Wire Wire Line
	8500 5950 8200 5950
Connection ~ 8200 5950
$Comp
L power:+5V #PWR027
U 1 1 5E66AE4C
P 8500 4400
F 0 "#PWR027" H 8500 4250 50  0001 C CNN
F 1 "+5V" H 8515 4573 50  0000 C CNN
F 2 "" H 8500 4400 50  0001 C CNN
F 3 "" H 8500 4400 50  0001 C CNN
	1    8500 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 4400 8500 4450
Wire Wire Line
	8500 5100 8500 5200
Wire Wire Line
	8900 5100 8900 5300
Wire Wire Line
	8900 5300 9800 5300
Wire Wire Line
	9800 5300 9800 4750
Wire Wire Line
	9800 4750 10000 4750
Wire Wire Line
	10000 4650 10000 4250
Wire Wire Line
	10000 4250 8800 4250
Wire Wire Line
	8800 4250 8800 4500
Wire Wire Line
	10000 4850 9850 4850
Wire Wire Line
	9850 4850 9850 4400
Wire Wire Line
	9850 4400 9000 4400
Wire Wire Line
	9000 4400 9000 4500
$Comp
L Device:D_Small D5
U 1 1 5E66AE5F
P 8050 4750
F 0 "D5" V 8000 4600 50  0000 L CNN
F 1 "1N4148" V 8150 4450 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" V 8050 4750 50  0001 C CNN
F 3 "~" V 8050 4750 50  0001 C CNN
	1    8050 4750
	0    1    1    0   
$EndComp
Wire Wire Line
	8050 4650 8050 4450
Wire Wire Line
	8050 4450 8500 4450
Connection ~ 8500 4450
Wire Wire Line
	8500 4450 8500 4500
Wire Wire Line
	8050 4850 8050 5200
Wire Wire Line
	8050 5200 8500 5200
Connection ~ 8500 5200
Wire Wire Line
	8500 5200 8500 5300
Wire Wire Line
	7800 5500 7300 5500
Text Label 7350 5500 0    50   ~ 0
OUT2
Text Label 4450 4450 0    50   ~ 0
OUT1
$Comp
L Microfono:CMA-6542PF MK1
U 1 1 5E9ECDFD
P 7850 1000
F 0 "MK1" H 7720 954 50  0000 R CNN
F 1 "MIK" H 7720 1045 50  0000 R CNN
F 2 "Microfono:CUI_CMA-6542PF" H 7850 1000 50  0001 L BNN
F 3 "CUI INC" H 7850 1000 50  0001 L BNN
F 4 "1.02" H 7850 1000 50  0001 L BNN "Field4"
F 5 "Manufacturer recommendations" H 7850 1000 50  0001 L BNN "Field5"
	1    7850 1000
	-1   0    0    1   
$EndComp
Wire Wire Line
	7100 1200 7550 1200
Wire Wire Line
	7100 800  7550 800 
Wire Wire Line
	7550 900  7550 800 
Connection ~ 7550 800 
Wire Wire Line
	7550 800  8200 800 
Wire Wire Line
	7550 1100 7550 1200
Connection ~ 7550 1200
Wire Wire Line
	7550 1200 8200 1200
$Comp
L BC547:BC547 T1
U 1 1 5EAF8F74
P 5300 4450
F 0 "T1" H 5444 4496 50  0000 L CNN
F 1 "BC547" H 5444 4405 50  0000 L CNN
F 2 "Transistor TO-92:TO92" H 5300 4450 50  0001 L BNN
F 3 "" H 5300 4450 50  0001 C CNN
	1    5300 4450
	1    0    0    -1  
$EndComp
$Comp
L BC547:BC547 T2
U 1 1 5EAFA3AA
P 8400 5500
F 0 "T2" H 8544 5546 50  0000 L CNN
F 1 "BC547" H 8544 5455 50  0000 L CNN
F 2 "Transistor TO-92:TO92" H 8400 5500 50  0001 L BNN
F 3 "" H 8400 5500 50  0001 C CNN
	1    8400 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 4450 5100 4450
Connection ~ 5100 4450
Wire Wire Line
	8300 5500 8200 5500
Connection ~ 8200 5500
$Comp
L Connector:Conn_01x02_Male ING1
U 1 1 5ECC2811
P 2050 650
F 0 "ING1" V 2000 700 50  0000 R CNN
F 1 " " H 2022 533 50  0000 R CNN
F 2 "TerminalBlock_4Ucon:TerminalBlock_4Ucon_1x02_P3.50mm_Horizontal" H 2050 650 50  0001 C CNN
F 3 "~" H 2050 650 50  0001 C CNN
	1    2050 650 
	0    -1   1    0   
$EndComp
$Comp
L Connector:Conn_01x02_Male ING2
U 1 1 5ECC377D
P 2350 650
F 0 "ING2" V 2300 700 50  0000 R CNN
F 1 " " H 2322 533 50  0000 R CNN
F 2 "TerminalBlock_4Ucon:TerminalBlock_4Ucon_1x02_P3.50mm_Horizontal" H 2350 650 50  0001 C CNN
F 3 "~" H 2350 650 50  0001 C CNN
	1    2350 650 
	0    -1   1    0   
$EndComp
$Comp
L Connector:Conn_01x02_Male ING3
U 1 1 5ECC3BD3
P 2650 650
F 0 "ING3" V 2600 700 50  0000 R CNN
F 1 " " H 2622 533 50  0000 R CNN
F 2 "TerminalBlock_4Ucon:TerminalBlock_4Ucon_1x02_P3.50mm_Horizontal" H 2650 650 50  0001 C CNN
F 3 "~" H 2650 650 50  0001 C CNN
	1    2650 650 
	0    -1   1    0   
$EndComp
$Comp
L power:GND #PWR0121
U 1 1 5ECC3E7D
P 2150 950
F 0 "#PWR0121" H 2150 700 50  0001 C CNN
F 1 "GND" H 2155 777 50  0000 C CNN
F 2 "" H 2150 950 50  0001 C CNN
F 3 "" H 2150 950 50  0001 C CNN
	1    2150 950 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0122
U 1 1 5ECC4062
P 2450 950
F 0 "#PWR0122" H 2450 700 50  0001 C CNN
F 1 "GND" H 2455 777 50  0000 C CNN
F 2 "" H 2450 950 50  0001 C CNN
F 3 "" H 2450 950 50  0001 C CNN
	1    2450 950 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0123
U 1 1 5ECC4222
P 2750 950
F 0 "#PWR0123" H 2750 700 50  0001 C CNN
F 1 "GND" H 2755 777 50  0000 C CNN
F 2 "" H 2750 950 50  0001 C CNN
F 3 "" H 2750 950 50  0001 C CNN
	1    2750 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 850  2150 950 
Wire Wire Line
	2450 850  2450 950 
Wire Wire Line
	2750 850  2750 950 
Wire Wire Line
	2050 850  2050 2350
Wire Wire Line
	2050 2350 2000 2350
Wire Wire Line
	2350 850  2350 1250
Wire Wire Line
	2350 1250 2150 1250
Wire Wire Line
	2150 1250 2150 2450
Wire Wire Line
	2650 850  2650 1550
Wire Wire Line
	2000 1550 2650 1550
Wire Wire Line
	2000 3350 2450 3350
Text Label 2300 3350 0    50   ~ 0
TXD
$Comp
L Device:R_US R10
U 1 1 5EFE72B9
P 3000 3800
F 0 "R10" V 2900 3800 50  0000 C CNN
F 1 "8,2K" V 3100 3800 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3040 3790 50  0001 C CNN
F 3 "~" H 3000 3800 50  0001 C CNN
	1    3000 3800
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R11
U 1 1 5EFE8C05
P 3450 3950
F 0 "R11" V 3350 4000 50  0000 C CNN
F 1 "10K" V 3550 3950 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3490 3940 50  0001 C CNN
F 3 "~" H 3450 3950 50  0001 C CNN
	1    3450 3950
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0124
U 1 1 5EFE9042
P 3450 4250
F 0 "#PWR0124" H 3450 4000 50  0001 C CNN
F 1 "GND" H 3455 4077 50  0000 C CNN
F 2 "" H 3450 4250 50  0001 C CNN
F 3 "" H 3450 4250 50  0001 C CNN
	1    3450 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 3450 2700 3800
Wire Wire Line
	2700 3800 2850 3800
Wire Wire Line
	2000 3450 2700 3450
Wire Wire Line
	3150 3800 3450 3800
Wire Wire Line
	3450 4100 3450 4250
Wire Wire Line
	3450 3800 3900 3800
Connection ~ 3450 3800
Text Label 3800 3800 0    50   ~ 0
RXD
$Comp
L TPA6211A1DGN:TPA6211A1DGN U4
U 1 1 5E50739D
P 2100 5450
F 0 "U4" H 2100 6115 50  0000 C CNN
F 1 "TPA6211A1DGN" H 2100 6024 50  0000 C CNN
F 2 "ModelloTPA6211A1:SOP65P490X110-9N" H 2100 5450 50  0001 L BNN
F 3 "" H 2100 5450 50  0001 L BNN
F 4 "IPC 7351B" H 2100 5450 50  0001 L BNN "Field4"
F 5 "0.65" H 2100 5450 50  0001 L BNN "Field5"
F 6 "0.05" H 2100 5450 50  0001 L BNN "Field6"
F 7 "3.1" H 2100 5450 50  0001 L BNN "Field7"
F 8 "2.9" H 2100 5450 50  0001 L BNN "Field8"
F 9 "" H 2100 5450 50  0001 L BNN "Field9"
F 10 "0.4" H 2100 5450 50  0001 L BNN "Field10"
F 11 "5.05" H 2100 5450 50  0001 L BNN "Field11"
F 12 "1.43" H 2100 5450 50  0001 L BNN "Field12"
F 13 "2.9" H 2100 5450 50  0001 L BNN "Field13"
F 14 "" H 2100 5450 50  0001 L BNN "Field14"
F 15 "3.0" H 2100 5450 50  0001 L BNN "Field15"
F 16 "0.315" H 2100 5450 50  0001 L BNN "Field16"
F 17 "3.1" H 2100 5450 50  0001 L BNN "Field17"
F 18 "" H 2100 5450 50  0001 L BNN "Field18"
F 19 "" H 2100 5450 50  0001 L BNN "Field19"
F 20 "Texas Instruments" H 2100 5450 50  0001 L BNN "Field20"
F 21 "" H 2100 5450 50  0001 L BNN "Field21"
F 22 "" H 2100 5450 50  0001 L BNN "Field22"
F 23 "0.38" H 2100 5450 50  0001 L BNN "Field23"
F 24 "" H 2100 5450 50  0001 L BNN "Field24"
F 25 "" H 2100 5450 50  0001 L BNN "Field25"
F 26 "1.76" H 2100 5450 50  0001 L BNN "Field26"
F 27 "3.0" H 2100 5450 50  0001 L BNN "Field27"
F 28 "" H 2100 5450 50  0001 L BNN "Field28"
F 29 "" H 2100 5450 50  0001 L BNN "Field29"
F 30 "" H 2100 5450 50  0001 L BNN "Field30"
F 31 "0.7" H 2100 5450 50  0001 L BNN "Field31"
F 32 "1.1" H 2100 5450 50  0001 L BNN "Field32"
F 33 "1.1" H 2100 5450 50  0001 L BNN "Field33"
F 34 "" H 2100 5450 50  0001 L BNN "Field34"
F 35 "" H 2100 5450 50  0001 L BNN "Field35"
F 36 "1.1" H 2100 5450 50  0001 L BNN "Field36"
F 37 "" H 2100 5450 50  0001 L BNN "Field37"
F 38 "4.9" H 2100 5450 50  0001 L BNN "Field38"
F 39 "E" H 2100 5450 50  0001 L BNN "Field39"
F 40 "8.0" H 2100 5450 50  0001 L BNN "Field40"
F 41 "0.55" H 2100 5450 50  0001 L BNN "Field41"
F 42 "0.25" H 2100 5450 50  0001 L BNN "Field42"
F 43 "4.75" H 2100 5450 50  0001 L BNN "Field43"
	1    2100 5450
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R12
U 1 1 5E5631FE
P 1200 5250
F 0 "R12" V 1300 5200 50  0000 L CNN
F 1 "100K" V 1100 5200 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1240 5240 50  0001 C CNN
F 3 "~" H 1200 5250 50  0001 C CNN
	1    1200 5250
	0    1    1    0   
$EndComp
Wire Wire Line
	1500 5250 1350 5250
Wire Wire Line
	1050 5250 1050 4700
Text Label 1050 4700 0    50   ~ 0
OFF_AMPLI
$Comp
L power:GND #PWR02
U 1 1 5E5893AD
P 2800 5950
F 0 "#PWR02" H 2800 5700 50  0001 C CNN
F 1 "GND" H 2805 5777 50  0000 C CNN
F 2 "" H 2800 5950 50  0001 C CNN
F 3 "" H 2800 5950 50  0001 C CNN
	1    2800 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 5950 2800 5950
Connection ~ 9500 3800
Wire Wire Line
	10200 3800 10450 3800
Connection ~ 10200 3800
Connection ~ 9700 3800
Wire Wire Line
	10100 3800 10200 3800
Connection ~ 10100 3800
Wire Wire Line
	9950 900  10050 900 
Wire Wire Line
	10050 900  10450 900 
Connection ~ 10050 900 
Wire Wire Line
	10000 3800 10100 3800
Connection ~ 10000 3800
Wire Wire Line
	9300 3800 9400 3800
Wire Wire Line
	9400 3800 9500 3800
Connection ~ 9400 3800
Wire Wire Line
	9900 3800 10000 3800
Connection ~ 9900 3800
Wire Wire Line
	9500 3800 9600 3800
Wire Wire Line
	9600 3800 9700 3800
Connection ~ 9600 3800
Wire Wire Line
	9700 3800 9800 3800
Wire Wire Line
	9800 3800 9900 3800
Connection ~ 9800 3800
$Comp
L simcom:SIM800C U3
U 1 1 5E02C7D0
P 9700 2300
F 0 "U3" H 9700 3881 50  0000 C CNN
F 1 "SIM800C" H 9700 3790 50  0000 C CNN
F 2 "SIM800C:LCC110P1570X1760X250-42N" H 9700 2300 50  0001 L BNN
F 3 "Simcom" H 9700 2300 50  0001 L BNN
F 4 "None" H 9700 2300 50  0001 L BNN "Field4"
F 5 "6.39 USD" H 9700 2300 50  0001 L BNN "Field5"
F 6 "Warning" H 9700 2300 50  0001 L BNN "Field6"
F 7 "SIM800C" H 9700 2300 50  0001 L BNN "Field7"
F 8 "Module: GSM/Bluetooth; GPRS; 2G; 1800MHz, 900MHz; 85.6kbps; SMD" H 9700 2300 50  0001 L BNN "Field8"
	1    9700 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C13
U 1 1 5E61C4E8
P 3050 5100
F 0 "C13" H 3200 5050 50  0000 L CNN
F 1 "0.1uf" H 3100 5200 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3088 4950 50  0001 C CNN
F 3 "~" H 3050 5100 50  0001 C CNN
	1    3050 5100
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x02_Male J5
U 1 1 5E5AE13A
P 3200 5850
F 0 "J5" H 3308 6031 50  0000 C CNN
F 1 "SPK2" H 3308 5940 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3200 5850 50  0001 C CNN
F 3 "~" H 3200 5850 50  0001 C CNN
	1    3200 5850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2700 5450 3300 5450
Wire Wire Line
	3300 5450 3300 5650
Wire Wire Line
	2700 5550 3200 5550
Wire Wire Line
	3200 5550 3200 5650
$Comp
L Device:CP_Small C14
U 1 1 5E673D95
P 3450 5100
F 0 "C14" H 3500 5150 50  0000 L CNN
F 1 "10uf" H 3500 5050 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x5.9" H 3450 5100 50  0001 C CNN
F 3 "~" H 3450 5100 50  0001 C CNN
	1    3450 5100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5E6742A6
P 3300 5250
F 0 "#PWR04" H 3300 5000 50  0001 C CNN
F 1 "GND" H 3305 5077 50  0000 C CNN
F 2 "" H 3300 5250 50  0001 C CNN
F 3 "" H 3300 5250 50  0001 C CNN
	1    3300 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 5250 3300 5250
Wire Wire Line
	3450 5200 3450 5250
Wire Wire Line
	3450 5250 3300 5250
Connection ~ 3300 5250
Wire Wire Line
	3450 5000 3450 4950
Wire Wire Line
	3450 4950 3050 4950
Wire Wire Line
	3050 4950 2700 4950
Wire Wire Line
	2700 4950 2700 5050
Connection ~ 3050 4950
$Comp
L power:+5V #PWR03
U 1 1 5E6BAE21
P 3050 4850
F 0 "#PWR03" H 3050 4700 50  0001 C CNN
F 1 "+5V" H 3065 5023 50  0000 C CNN
F 2 "" H 3050 4850 50  0001 C CNN
F 3 "" H 3050 4850 50  0001 C CNN
	1    3050 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 4950 3050 4850
$Comp
L Device:C C10
U 1 1 5E6CF4B8
P 900 6350
F 0 "C10" H 1050 6300 50  0000 L CNN
F 1 "33pf" H 950 6450 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 938 6200 50  0001 C CNN
F 3 "~" H 900 6350 50  0001 C CNN
	1    900  6350
	-1   0    0    1   
$EndComp
$Comp
L Device:C C11
U 1 1 5E6CFB05
P 1250 6350
F 0 "C11" H 1050 6300 50  0000 L CNN
F 1 "33pf" H 1000 6450 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1288 6200 50  0001 C CNN
F 3 "~" H 1250 6350 50  0001 C CNN
	1    1250 6350
	-1   0    0    1   
$EndComp
$Comp
L Device:R_US R3
U 1 1 5E6CFF7C
P 900 5850
F 0 "R3" V 1000 5800 50  0000 L CNN
F 1 "18K" V 800 5800 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 940 5840 50  0001 C CNN
F 3 "~" H 900 5850 50  0001 C CNN
	1    900  5850
	-1   0    0    1   
$EndComp
$Comp
L Device:R_US R13
U 1 1 5E6D0897
P 1250 5850
F 0 "R13" V 1350 5800 50  0000 L CNN
F 1 "18K" V 1150 5800 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1290 5840 50  0001 C CNN
F 3 "~" H 1250 5850 50  0001 C CNN
	1    1250 5850
	-1   0    0    1   
$EndComp
$Comp
L Device:C C12
U 1 1 5E6EC0E7
P 1500 6050
F 0 "C12" H 1300 6000 50  0000 L CNN
F 1 "0.1uf" H 1250 6150 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1538 5900 50  0001 C CNN
F 3 "~" H 1500 6050 50  0001 C CNN
	1    1500 6050
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5E6EC5FF
P 1800 6200
F 0 "#PWR01" H 1800 5950 50  0001 C CNN
F 1 "GND" H 1805 6027 50  0000 C CNN
F 2 "" H 1800 6200 50  0001 C CNN
F 3 "" H 1800 6200 50  0001 C CNN
	1    1800 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 6200 1800 6200
Wire Wire Line
	1500 5900 1500 5750
Wire Wire Line
	1250 5700 1250 5550
Wire Wire Line
	1250 5550 1500 5550
Wire Wire Line
	900  5700 900  5450
Wire Wire Line
	900  5450 1500 5450
Wire Wire Line
	900  6200 900  6000
Wire Wire Line
	1250 6200 1250 6000
Wire Wire Line
	900  6500 900  6850
Wire Wire Line
	1250 6500 1250 6850
Text Label 900  6850 0    50   ~ 0
SPKP
Text Label 1250 6850 0    50   ~ 0
SPKN
$EndSCHEMATC
