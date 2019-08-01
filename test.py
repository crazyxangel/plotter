import serial
from time import sleep
ser = serial.Serial("COM17",115200,timeout = 0)
step_rev = 200          #steps for nema 17 to complete a revolution
size = 300              #size of the plotter drawing area
pulley_diameter = 15    #diameter of the pulley

factor = size/100       #factor to translate the coordinates which are in % to the size of the drawing area
mm_rev = pulley_diameter*3.14
mmstep = mm_rev/step_rev/100

log = []

x_coords = []
x_steps = []

y_coords = []
y_steps = []

x_dummy = [10,20,10,20]
y_dummy = [10,20,10,20]

loop = True

thickness = []

data = open("data.txt","r")
string = data.read()
string = string.replace(';', ',')
output = open("changedforsplit.txt","w")
output.write(string) 
output.close()
values = string.split(',')
x = 0
z = 0
for y in values:
    try:
        if z == 0:
            z +=1
            if x < 5: 
                x_coords.append(float(values[x]))
                x_steps.append(round(((float(values[x])/mmstep)*factor)))
            elif not float(values[x]) == float(values[x-3]) and not float(values[x-2]) == float(values[x-5]):
                x_coords.append(float(values[x]))
                x_steps.append(round(((float(values[x])/mmstep)*factor)))
        elif z == 1:
            z +=1
            if x < 5: 
                y_coords.append(float(values[x]))
                y_steps.append(round(((float(values[x])/mmstep)*factor)))
            elif not float(values[x]) == float(values[x-3]) and not float(values[x-1]) == float(values[x-4]):
                y_coords.append(float(values[x]))
                y_steps.append(round(((float(values[x])/mmstep)*factor)))
        elif z == 2:
            z = 0
            thickness.append(float(values[x]))
        x += 1
    except:
        None

output = open("x.txt","w")
output.write(str(x_coords))
output.close()
output = open("y.txt","w")
output.write(str(y_coords))
output.close()

output = open("xsteps.txt","w")
output.write(str(x_steps))
output.close()
output = open("ysteps.txt","w")
output.write(str(y_steps))
output.close()  

ser.write("test".encode())
response = str(ser.readline())
while 'Ready' not in response:
    response = str(ser.readline())

print("ready")
dataout = '/'+str(x_steps[0])+'x'+'/'+str(y_steps[0])+'y.'
# dataout = '/'+str(x_dummy[0])+'x'+'/'+str(y_dummy[0])+'y.'

ser.write(dataout.encode())
i = 0
prev = ''
while loop:
    # inputstring = input()
    # ser.write(inputstring.encode())
    # while i < len(y_dummy):           # uncomment to send dummy data for easy testing
    while i <= len(y_steps):           # uncomment to send actual file data
        response = str(ser.readline())
        sleep(.010)
        if response != prev :
            print(response)
            prev = response
        if 'N' in response:
            dataout = '/'+str(x_steps[i])+'x'+'/'+str(y_steps[i])+'y.'
            # dataout = '/'+str(x_dummy[i])+'x'+'/'+str(y_dummy[i])+'y.'
            print(dataout)
            ser.write(dataout.encode())
            i += 1
