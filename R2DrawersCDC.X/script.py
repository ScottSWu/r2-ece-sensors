import serial
import time
import io
import sys
import R2Protocol

timeout = time.time() + 60*2 # record data for two minutes
start = time.time()
now = time.time()
#port = '/dev/tty.usbmodem143121'
port = "/dev/tty.usbmodem141111"
baudrate = 9600
ser = serial.Serial(port, baudrate, timeout=1, write_timeout=5)
#request1 = b'G00SNUCDDRAWERT0PCG01'
request1 = R2Protocol.encode("NUC", "DRAWER1", "I", "C")
#request2 = R2Protocol.encode("NUC", "DRAWER1", "", "C")
print (request1)
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

##f = open('C:\Users\emily\Documents\GitHub\cs-r2bot2\R2Bot\templates\ultrasoundData.txt', 'w')
ctr = 0

while True:
    ser.write(request1)
    print ("sent request 1")
    indata = ser.read(200)
    indexFront = indata.find(b'G00')
    indexEnd = indata.find(b'G01')
    if indexFront < indexEnd and indexFront != -1 and indexEnd != -1:
        indata = indata[indexFront:indexEnd+3]
        #print (indata)
    else:
        indata = None
    if (indata != None):
        decodedData = R2Protocol.decode(indata)
        print (R2Protocol.decode(indata))
        #f.write(decodedData['source'] + "," decodedData['data'] + "\n")
    ctr+=1
    time.sleep(3)