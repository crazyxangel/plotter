import serial
from time import sleep
ser = serial.Serial("COM17",115200)
while True:
    inputstring = input()
    ser.write(inputstring.encode())
