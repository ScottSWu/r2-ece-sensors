import serial
import time
import io
import sys
import R2Protocol

timeout = time.time() + 60*2 # record data for two minutes
start = time.time()
now = time.time()
portS = 'COM4'
baudrateS = 9600
portM = 'COM12'
baudrateM = 9600
ser = serial.Serial(portS, baudrateS, timeout=1)
serM = serial.Serial(portM, baudrateM, timeout=1)
motorRequest = R2Protocol.encode(b"PI", b"LOCOMOTION", b"", b"M10050M20050")
serM.write(motorRequest)
#print (openRequest)
#closeRequest = R2Protocol.encode("NUC", "FLAP", "RTx", "C")
#print (closeRequest)
##f = open(r'C:\Users\emily\Documents\GitHub\cs-r2bot2\R2Bot\sensorIO\headFlap.txt', 'r')
##
##while True:
##    indata = f.readline().strip()
##
##    if (indata is "0"):
##        ser.write(closeRequest)
##        print (indata)
##        
##    elif (indata is "1"):
##        ser.write(openRequest)
##        print (indata)
##    time.sleep(5)
##    
##ser.write(openRequest)
##time.sleep(5)
##ser.write(closeRequest)
##ctr = 0
##f = open('C:\Users\emily\Documents\GitHub\cs-r2bot2\R2Bot\templates\ultrasoundData.txt', 'w')
try:
    while True:
        indata = ser.read(200)
        if(b"G00" in indata and b"G01" in indata):
            while(R2Protocol.decode(indata) != None):
                decodedData = R2Protocol.decode(indata)
                print (R2Protocol.decode(indata))
                indexEnd = decodedData['read']
                indata = indata[indexEnd:]
                if (decodedData != None and decodedData['source'] == "U2SENSOR" and float(decodedData['data']) < 12):
                    motorRequest = R2Protocol.encode(b"PI", b"LOCOMOTION", b"", b"M10000M20000")
                else:
                    motorRequest = R2Protocol.encode(b"PI", b"LOCOMOTION", b"", b"M10050M20050")
            serM.write(motorRequest)
        time.sleep(.01)
except KeyboardInterrupt:
    f.close()