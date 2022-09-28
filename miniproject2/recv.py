import atexit
from math import cos, exp, pi, radians, sin

import matplotlib.pyplot as plt
import numpy as np
import pickle
import serial

from interp import *
#ser = serial.Serial('COM4')

from pprint import pprint
from time import time_ns

"""Constants
Port for serial communication, baud, and radius of the IR sensor from the center
of the scanner (in cm).
"""
PORT = "COM6"
BAUD = 9600
PAN_NAUGHT  = 100
TILT_NAUGHT = 105
DIST_THRESH = 80

def transfer(s):
    """Converts sensor reading to distance."""
    a = 134.391
    b = -0.00427218
    return a * exp(b * s)

def poltocart(angle_pan, angle_tilt, hypot):
    """Converts polar to cartesian."""
    #x = hypot * sin(angle_pan  - PAN_NAUGHT)
    #y = hypot * sin(angle_tilt - TILT_NAUGHT)
    #x = hypot * interp.panterp(angle_pan)
    #y = hypot * interp.tilterp(angle_tilt)
    #x = hypot * cos(angle_pan)
    #y = hypot * cos(angle_tilt)
    #x = hypot * panterp(angle_pan)
    #y = hypot * tilterp(angle_tilt)
    #print(y)

    angle_pan = angle_pan - PAN_MID
    angle_tilt  = angle_tilt - TILT_MID
    xs = hypot * math.sin(angle_tilt) * math.sin(angle_pan)
    ys = hypot * math.sin(angle_tilt) * math.cos(angle_pan)
    zs = hypot * math.cos(angle_tilt)

    return (xs, ys, zs)

def graph(X, Y, Z):
    """Create plot. """
    #fig, ax = plt.subplots()
    #m = max(Z)
    #ax.scatter(X, Y, alpha=[(m-z)/m for z in Z])
    #plt.show()
    fig = plt.figure()
    ax = fig.add_subplot(projection="3d")
    ax.scatter(X, Y, Z)
    plt.show()

def fromfile():
    with open("data.txt", "r") as f:
        yield from f.read().split("\n")

def fromserial():
    ser = serial.Serial(PORT, BAUD, timeout=1000)

    while True:
        try:
            yield ser.readline()
        except:
            ser.close()
            break

if __name__ == "__main__":
    data = []#{}

    for line in fromserial():
        try:
            angle_pan, angle_tilt, sensor = map(float, line.split())
            print(angle_pan, angle_tilt, sensor)
            if angle_pan == PAN_MAX and angle_tilt == TILT_MIN:
                break
        except:
            continue

        angle_pan = radians(angle_pan)
        angle_tilt = radians(angle_tilt)
        sensor = transfer(sensor)
        x, y, z = poltocart(angle_pan, angle_tilt, sensor)
        data.append([x, y, z])
        #data[(x, y)] = sensor

    #with open("data3.pickle", "wb") as f:
    #    pickle.dump(data, f, pickle.HIGHEST_PROTOCOL)
    #pprint(data)
    graph(*zip(*data))