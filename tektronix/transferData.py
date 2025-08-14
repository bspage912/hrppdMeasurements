# mdo simple plot
# python v3.x, pyvisa v1.8
# should work with MSO70k, DPO7k, MSO5k, MDO4k, MDO3k, and MSO2k series
# 5/6 Series MSO 

# incompatible with TDS2k and TBS1k series (see tbs simple plot)

import time # std module
import pyvisa as visa # http://github.com/hgrecco/pyvisa
#import matplotlib.pyplot as plt # http://matplotlib.org/
#import numpy as np # http://www.numpy.org/
from datetime import datetime

progstart = time.perf_counter()

#visa_address = 'USB0::0x0699::0x0456::C000660::INSTR'
oscilloscope_address = 'TCPIP::192.168.60.88::INSTR'

rm = visa.ResourceManager('@py')
#scope = rm.open_resource(visa_address)
scope = rm.open_resource(oscilloscope_address)
scope.timeout = 10000 # ms
scope.encoding = 'latin_1'
scope.read_termination = '\n'
scope.write_termination = None
scope.write('*cls') # clear ESR

print(scope.query('*idn?'))

# Goto Scope DIR
#scope.write('FILESystem:CWD \"C:/Users/Tek_Local_Admin/Tektronix/TekScope/Event/timingScan_2024-11-13\"')
# For AYK Transfer
#scope.write('FILESystem:CWD \"C:/Users/Tek_Local_Admin/Tektronix/TekScope/Event/run21\"')
# For PiLas Test 3/19/25
#scope.write('FILESystem:CWD \"C:/Users/Tek_Local_Admin/Tektronix/TekScope/Event/ElmoTest/run37\"')
#scope.write('FILESystem:CWD \"C:/Users/Tek_Local_Admin/Tektronix/TekScope/Event/noiseTest/run08\"')
#scope.write('FILESystem:CWD \"C:/Users/Tek_Local_Admin/Tektronix/TekScope/Event/test\"')
scope.write('FILESystem:CWD \"C:/Users/Tek_Local_Admin/Tektronix/TekScope/Event/Brian/run80044\"')

# Destination Path
destPath="data00csv/"
# For AYK Transfer
#destPath="/home/eic/ayk/Scope/data/run21/csv/"

# Query Files
filelist = scope.query('FILESystem:DIR?')
#print(filelist)

filelist = filelist.split(',')
#print(filelist)

i=0
for name in filelist:
    #print(name)

    stripName = name.strip('"')
    #print(stripName)

    outName = destPath + stripName

    # Read image file from instrument
    scope.write('FILESystem:READFile ' + name)
    fileData = scope.read_raw()

    # Save image data to local disk
    file = open(outName, "wb")
    file.write(fileData)
    file.close()

    a=i%1000
    if a == 0:
        print(f'\nProgress: {i} Files')

    i=i+1


print(f'\nTransfered {i} Files')
progend = time.perf_counter()
print('Program Time: {} s'.format(progend - progstart))

print("\nEnd of Program")

 
# Image data has been transferred to PC and saved. Delete image file from instrument's hard disk.

#scope.write('FILESystem:DELEte \"C:/Temp.png\"')

 
scope.close()

rm.close()
