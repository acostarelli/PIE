import csv
from time import time

import serial

# Depends on serial port
ser = serial.Serial('COM7')

f = open("df.csv", "w")
writer = csv.writer(f, delimiter=',')

#print("here")
while True:
    print("looping")
    #print("looping")
    s = ser.readline()
    #print(s)
    #print(s)
    if s != "Done":
        #print("what")
        rows = [float(x) for x in s.split()]
        #print("okay")
        # Insert local time to list's first position


        writer.writerow(rows)

        print(rows)
        if rows[0] == 120 and rows[1] == 75:
            break
        #print("finished")
    else:
        break

print("done")
