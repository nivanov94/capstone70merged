# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\rdeiaco\Documents\PSoC Creator\capstone70merged\capsenseled.cydsn\capsenseled.cyprj
# Date: Sat, 25 Feb 2017 01:03:40 GMT
#set_units -time ns
create_clock -name {ADC_SAR_Seq_1_intClock(FFB)} -period 500 -waveform {0 250} [list [get_pins {ClockBlock/ff_div_6}]]
create_clock -name {Clock_PWM(FFB)} -period 2000 -waveform {0 1000} [list [get_pins {ClockBlock/ff_div_7}] [get_pins {ClockBlock/ff_div_9}] [get_pins {ClockBlock/ff_div_10}]]
create_clock -name {Clock_1(FFB)} -period 10000 -waveform {0 5000} [list [get_pins {ClockBlock/ff_div_8}]]
create_clock -name {CyRouted1} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyWCO} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/wco}]]
create_clock -name {CyLFCLK} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyECO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/eco}]]
create_clock -name {CyIMO} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFCLK} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySYSCLK} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {ADC_SAR_Seq_1_intClock} -source [get_pins {ClockBlock/hfclk}] -edges {1 25 49} [list]
create_generated_clock -name {Clock_PWM} -source [get_pins {ClockBlock/hfclk}] -edges {1 97 193} [list]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/hfclk}] -edges {1 481 961} [list]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for C:\Users\rdeiaco\Documents\PSoC Creator\capstone70merged\capsenseled.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\rdeiaco\Documents\PSoC Creator\capstone70merged\capsenseled.cydsn\capsenseled.cyprj
# Date: Sat, 25 Feb 2017 01:03:35 GMT
