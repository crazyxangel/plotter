#importing modules
import serial
from time import sleep

ser = serial.Serial("COM17",115200,timeout = 0) #starting up the serial communication

step_rev = 200                                  #steps for nema 17 to complete a revolution
size = 300                                      #size of the plotter drawing area
pulley_diameter = 15                            #diameter of the pulley

factor = size/100                               #factor to translate the coordinates which are in % to the size of the drawing area
mm_rev = pulley_diameter*3.14   
mmstep = mm_rev/step_rev/100

#x and y lists for coordinates and steps
x_coords = []
x_steps = []
y_coords = []
y_steps = []

thickness = []                                  #thickness list currently gets data but has no use

#dummy list for testing
x_dummy = [10,20,10,20]
y_dummy = [10,20,10,20]

loop = True                                     #boolean for loop

#reading the file
data = open("data.txt","r")                     #open the file and put it in data variable
string = data.read()                            #create a string from the data
string = string.replace(';', ',')               #replace ; with , for easier splitting

#writing to new file unnescesairy but usefull for debugging
output = open("changedforsplit.txt","w")        #open file and if file doesnt exist create one
output.write(string)                            #write the string to the file
output.close()                                  #close the file
values = string.split(',')                      #split the string into smaller strings and put them into a list

#2 variables used while looping trough the list while splitting it into parts of 3 elements
x = 0                                           #X is used as a refference point in the double entry checker
z = 0                                           #Z splits into X Y and Thickness at 0, 1 and 2 respectively

for y in values:                                #loops trough entire values list
    try:
        if z == 0:                              # X
            z +=1
            if x < 5:                                                                                           #first coordinate cant be checked by previous one
                x_coords.append(float(values[x]))                                                               #appends the coordinal value 
                x_steps.append(round(((float(values[x])/mmstep)*factor)))                                       #appends the step value
            elif not float(values[x]) == float(values[x-3]) and not float(values[x+1]) == float(values[x-2]):   #compares this row of x and y to the previous one to prevent duplicate coordinates
                x_coords.append(float(values[x]))
                x_steps.append(round(((float(values[x])/mmstep)*factor)))
        elif z == 1:                            # Y
            z +=1
            if x < 5: 
                y_coords.append(float(values[x]))
                y_steps.append(round(((float(values[x])/mmstep)*factor)))
            elif not float(values[x]) == float(values[x-3]) and not float(values[x-1]) == float(values[x-4]):
                y_coords.append(float(values[x]))
                y_steps.append(round(((float(values[x])/mmstep)*factor)))
        elif z == 2:                            #thickness
            z = 0
            thickness.append(float(values[x]))
        x += 1
    except:
        None

#opens or creates a file to write down all the X coordinates
output = open("x.txt","w")
output.write(str(x_coords))
output.close()
#opens or creates a file to write down all the Y coordinates
output = open("y.txt","w")
output.write(str(y_coords))
output.close()

#opens or creates a file to write down all the X Steps
output = open("xsteps.txt","w")
output.write(str(x_steps))
output.close()
#opens or creates a file to write down all the y steps
output = open("ysteps.txt","w")
output.write(str(y_steps))
output.close()  

ser.write("test".encode())                      #sends a test string trough the serial connection
response = str(ser.readline())                  #reads the first line in the serial buffer
while 'Ready' not in response:                  #waits until it gets a "ready" from the microcontroller
    response = str(ser.readline())

print("ready")
dataout = '/'+str(x_steps[0])+'x'+'/'+str(y_steps[0])+'y.'  #creates the text for the first serial write this happens again in the upcoming loop but this ensures the first coordinate is fully and correctly received
# dataout = '/'+str(x_dummy[0])+'x'+'/'+str(y_dummy[0])+'y.'

ser.write(dataout.encode())                     #sends out above mentioned text
i = 0                                           #creates a variable for upcoming loop

prev = ''                                       #creates a blank string(diffirent from NULL/nothing) for future comparison
while loop:
    # inputstring = input()                      #uncomment to manually enter serial data to send
    # ser.write(inputstring.encode())            #writes above mentioned data
    # while i < len(y_dummy):                    # uncomment to send dummy data for easy testing
    while i <= len(y_steps):                    # uncomment to send actual file data
        response = str(ser.readline())
        sleep(.010)                             #halts the program for a short moment to give serial data coming back some time
        if response != prev :                   #checks if serial buffer is not equal to the previous message
            print(response)                     #prints response to console for debugging use
            prev = response                     #sets the current message as previous reference
        if 'N' in response:                     #checks if microcontroller has send a N to comfirm its ready for next set of coordinates
            dataout = '/'+str(x_steps[i])+'x'+'/'+str(y_steps[i])+'y.'  #forms the outgoing string
            # dataout = '/'+str(x_dummy[i])+'x'+'/'+str(y_dummy[i])+'y.'
            print(dataout)                      #prints the string to console for debugging use
            ser.write(dataout.encode())         #serially writes the string
            i += 1
