import serial
import time
import io
import sys
import R2Protocol

timeout = time.time() + 60*2 # record data for two minutes
start = time.time()
now = time.time()
port = 'COM10'
baudrate = 9600
ser = serial.Serial(port, baudrate, timeout=1)

"""while True:
    indata = f.readline().strip()

    if (indata is "0"):
        ser.write(closeRequest)
        print (indata)
        
    elif (indata is "1"):
        ser.write(openRequest)
        print (indata)
    time.sleep(5)
    """
while True:
    print (R2Protocol.decode(ser.read(ser.inWaiting())))
    

    
