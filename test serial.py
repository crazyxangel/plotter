import serial
from time import sleep
ser = serial.Serial("COM17",115200,timeout = 0)

while True:
    inputstring = input()
    ser.write(inputstring.encode())
    # if 'Next' in str(ser.readline()):
    #     print("banana")
    print(str(ser.readline()))        
    
 