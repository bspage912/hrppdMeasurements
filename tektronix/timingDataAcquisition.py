# mdo simple plot
# python v3.x, pyvisa v1.8
# should work with MSO70k, DPO7k, MSO5k, MDO4k, MDO3k, and MSO2k series
# 5/6 Series MSO 

# incompatible with TDS2k and TBS1k series (see tbs simple plot)

import time # std module
import pyvisa as visa # http://github.com/hgrecco/pyvisa
import sys

progstart = time.perf_counter()

oscilloscope_address = 'TCPIP::192.168.60.88::INSTR'

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
scope.write('DATA:SOURCE CH1,CH5')
preamble = scope.query('WFMOutpre?')
print(preamble)

# Trigger Setup
scope.write('TRIGGER:A:TYPE EDGE')
scope.write('TRIGGER:A:EDGE:SOURCE CH1')
scope.write('TRIGGER:A:LOWERTHRESHOLD:CH1 -0.080')
scope.write('TRIGGER:A:EDGE:SLOPE FALL')

# Channel 1 Setup
scope.write('CH1:SCALE 100E-3')
scope.write('CH1:BANDWIDTH 10E+9')
scope.write('CH1:TERMINATION 50.0E+0')

# Channel 5 Setup
scope.write('CH5:SCALE 10E-3')
scope.write('CH5:BANDWIDTH 10E+9')
scope.write('CH5:TERMINATION 50.0E+0')

# Set Horizontal Parameters
scope.write('HORIZONTAL:MODE MANUAL')
scope.write('HORIZONTAL:MODE:SAMPLERATE 50E+9')
scope.write('HORIZONTAL:MODE:RECORDLENGTH 2000')
scope.write('HORIZONTAL:POSITION 10')
scope.write('HORIZONTAL:MODE:SCALE 4E-9')

# Acquisition
scope.write('CLEAR')
#scope.write('ACQUIRE:STATE 0') # stop
scope.write('ACQUIRE:MODE SAMPLE') # continuous
scope.write('ACQUIRE:STATE 1') # start
scope.write('DISPLAY:WAVEFORM OFF')
#scope.write('DISPLAY:WAVEFORM ON')

# Parse comman line arguments: run directory and required statistics;
qdir="C:/Users/Tek_Local_Admin/Tektronix/TekScope/Event/Brian/" + sys.argv[1]
stat=sys.argv[2]

# Set to Act on Trigger
scope.write('ACTONEVENT:ENABLE 1')
scope.write('ACTONEVENT:LIMIT 1')
scope.write('ACTONEVENT:LIMITCOUNT ' + stat)
scope.write('SAVEONEVENT:FILEDEST ' + '\"' + qdir + '\"')
scope.write('FILESystem:MKDir ' + '\"' + qdir + '\"')
scope.write('SAVEONEVENT:FILENAME \"elmoTektronixData\"')
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
