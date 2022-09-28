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
    #x = hypot * sin(angle_pan - PAN_MID)
    #y = hypot * sin(angle_tilt - TILT_MID)
    #x = pinterp(angle_pan)
    #y = tinterp(angle_tilt)
    x = panterp(angle_pan)
    y = tilterp(angle_tilt)

    return (x, y)

def graph(X, Y, Z):
    """Create plot. """
    fig, ax = plt.subplots()
    m = max(Z)
    ax.scatter(X, Y, alpha=[(m-z)/m for z in Z])
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
    with open("data.pickle", "rb") as f:
        p = pickle.load(f)

    data = []

    for pt in p:
        angle_pan, angle_tilt, sensor = pt

        #angle_pan  = radians(angle_pan)
        #angle_tilt = radians(angle_tilt)
        sensor     = transfer(sensor)
        x, y = poltocart(angle_pan, angle_tilt, sensor)
        data.append([x, y, sensor])

    graph(*zip(*data))