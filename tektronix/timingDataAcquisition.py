# mdo simple plot
# python v3.x, pyvisa v1.8
# should work with MSO70k, DPO7k, MSO5k, MDO4k, MDO3k, and MSO2k series
# 5/6 Series MSO 

# incompatible with TDS2k and TBS1k series (see tbs simple plot)

import time # std module
import pyvisa as visa # http://github.com/hgrecco/pyvisa
import sys

progstart = time.perf_counter()

#oscilloscope_address = 'TCPIP::192.168.60.88::INSTR'
oscilloscope_address = 'TCPIP::192.168.60.99::INSTR'


rm = visa.ResourceManager('@py')
scope = rm.open_resource(oscilloscope_address)
scope.timeout = 10000 # ms
scope.encoding = 'latin_1'
scope.read_termination = '\n'
scope.write_termination = None
scope.write('*cls') # clear ESR

print(scope.query('*idn?'))

# Print Info
scope.write('HEADER 0')
scope.write('DATA:SOURCE CH1,CH2,CH3,CH4,CH5,CH6')
preamble = scope.query('WFMOutpre?')
print(preamble)

# Trigger Setup
scope.write('TRIGGER:A:TYPE EDGE')
scope.write('TRIGGER:A:EDGE:SOURCE CH1')
scope.write('TRIGGER:A:LOWERTHRESHOLD:CH1 -0.380')
scope.write('TRIGGER:A:EDGE:SLOPE FALL')

# Channel 1 Setup
scope.write('CH1:SCALE 200E-3')
scope.write('CH1:BANDWIDTH 8E+9')
scope.write('CH1:TERMINATION 50.0E+0')

# Channel 2 Setup
scope.write('CH2:SCALE 20E-3')
scope.write('CH2:BANDWIDTH 8E+9')
scope.write('CH2:TERMINATION 50.0E+0')

# Channel 3 Setup
#scope.write('CH3:SCALE 20E-3')
#scope.write('CH3:BANDWIDTH 5E+9')
#scope.write('CH3:TERMINATION 50.0E+0')

# Channel 4 Setup
#scope.write('CH4:SCALE 20E-3')
#scope.write('CH4:BANDWIDTH 8E+9')
#scope.write('CH4:TERMINATION 50.0E+0')

# Channel 5 Setup
#scope.write('CH5:SCALE 20E-3')
#scope.write('CH5:BANDWIDTH 5E+9')
#scope.write('CH5:TERMINATION 50.0E+0')

# Channel 6 Setup
#scope.write('CH6:SCALE 20E-3')
#scope.write('CH6:BANDWIDTH 5E+9')
#scope.write('CH6:TERMINATION 50.0E+0')

# Set Horizontal Parameters
scope.write('HORIZONTAL:MODE MANUAL')
scope.write('HORIZONTAL:MODE:SAMPLERATE 50E+9')
scope.write('HORIZONTAL:MODE:RECORDLENGTH 10000')
scope.write('HORIZONTAL:POSITION 8')
scope.write('HORIZONTAL:MODE:SCALE 20E-9')


# Acquisition
scope.write('CLEAR')
#scope.write('ACQUIRE:STATE 0') # stop
scope.write('ACQUIRE:MODE SAMPLE') # continuous
scope.write('ACQUIRE:STATE 1') # start
scope.write('DISPLAY:WAVEFORM OFF')
#scope.write('DISPLAY:WAVEFORM ON')

# Parse comman line arguments: run directory and required statistics;
qdir="C:/Users/Tek_Local_Admin/Tektronix/TekScope/Event/B-Field/" + sys.argv[1]
stat=sys.argv[2]

# Set to Act on Trigger
scope.write('ACTONEVENT:ENABLE 1')
scope.write('ACTONEVENT:LIMIT 1')
scope.write('ACTONEVENT:LIMITCOUNT ' + stat)
scope.write('SAVEONEVENT:FILEDEST ' + '\"' + qdir + '\"')
scope.write('FILESystem:MKDir ' + '\"' + qdir + '\"')
scope.write('SAVEONEVENT:FILENAME \"BFieldData\"')
scope.write('SAVEONEVENT:WAVEFORM:FILEFORMAT SPREADSHEET')
scope.write('SAVEONEVENT:WAVEFORM:SOURCE ALL')
#scope.write('ACTONEVENT:TRIGGER:ACTION:SRQ:STATE ON')
scope.write('ACTONEVENT:TRIGGER:ACTION:SAVEWAVEFORM:STATE ON')

# Keep Track of Acquisitions
i = 0
acqStart = time.perf_counter()
while i < int(stat):
    time.sleep(3.0)
    acq = scope.query('ACQUIRE:NUMACQ?')
    print(acq)
    i = int(acq)

scope.write('DISPLAY:WAVEFORM ON')
scope.write('ACQUIRE:STATE 0')
acqEnd = time.perf_counter()
print('Approximate Time: {} s'.format(acqEnd - acqStart))


scope.close()

print("\nEnd of Program")

