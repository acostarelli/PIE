from math import cos, exp, pi, radians, sin

import matplotlib.pyplot as plt
import numpy as np
import serial

from pprint import pprint

"""Constants
Port for serial communication, baud, and radius of the IR sensor from the center
of the scanner (in cm).
"""
PORT = "COM7"
BAUD = 9600
PAN_NAUGHT  = 100
TILT_NAUGHT = 105
DIST_THRESH = 4

def transfer(s):
    """Converts sensor reading to distance."""
    a = 134.391
    b = -0.00427218
    return a * exp(b * s)


def poltocart(angle_pan, angle_tilt, hypot):
    """Converts polar to cartesian."""
    #x = hypot * sin(angle_pan  - PAN_NAUGHT)
    #y = hypot * sin(angle_tilt - TILT_NAUGHT)
    x = hypot * cos(angle_pan)
    y = hypot * cos(angle_tilt)

    return (x, y)

def graph(X, Y):
    """Create plot. """
    fig, ax = plt.subplots()
    ax.scatter(X, Y, s=1, alpha=0.5)
    plt.show()

def usesample():
    with open("sample.txt", "r") as f:
        data = f.read()

    data = data.split()
    for i in range(0, len(data), 3):
        yield [int(data[i]), int(data[i+1]), int(data[i+2])]

if __name__ == "__main__":
    data = []

    """
    with serial.Serial(PORT, BAUD) as ser:
        while True:
            try:
                angle_pan, angle_tilt, voltage = map(int, ser.readline().split())
                data.append(
                    poltocart(
                        radians(angle_pan), radians(angle_tilt), transfer(voltage)
                    )
                )
            except ValueError:
                break
    """
    with serial.Serial(PORT, BAUD) as ser:
        while True:
            angle_pan, angle_tilt, sensor = map(int, ser.readline().split())
            print(angle_pan, angle_tilt)
            if angle_pan == 120 and angle_tilt == 75:
                break

            angle_pan  = radians(angle_pan)
            angle_tilt = radians(angle_tilt)
            sensor     = transfer(sensor)
            x, y = poltocart(angle_pan, angle_tilt, sensor)
            data.append([x, y, sensor])

    data = [[pt[0], p[1]] for pt in data]#if pt[2] < DIST_THRESH]

    graph(*zip(*data))