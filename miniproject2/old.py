from math import cos, exp, pi, radians, sin

import matplotlib.pyplot as plt
import numpy as np
import serial

from pprint import pprint
from time import time_ns

"""Constants
Port for serial communication, baud, and radius of the IR sensor from the center
of the scanner (in cm).
"""
PORT = "COM4"
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
    x = hypot * cos(angle_pan)
    y = hypot * cos(angle_tilt)

    return (x, y)

def graph(X, Y, Z):
    """Create plot. """
    fig, ax = plt.subplots()
    m = max(Z)
    ax.scatter(X, Y, alpha=[(m-z)/m for z in Z])
    plt.show()

class Serial:
    def __init__(self, port=PORT, baud=BAUD, timeout=1000):
        self._port = port
        self._baud = baud
        self._timeout = timeout
        self._ser = None

        self._connect()

    def _connect(self):
        print("Connecting...")
        while True:
            try:
                self._ser = serial.Serial(self._port, self._baud, timeout=self._timeout)
            except Exception as e:
                print(time_ns(), e)
                pass
        print("done.")

    def readline(self):
        try:
            return self._ser.readline()
        except:
            self._connect()
            return self.read()

    def close(self):
        return self._ser.close()

if __name__ == "__main__":
    data = []

    #ser = Serial()
    ser = serial.Serial(PORT, BAUD, timeout=1000)
    while True:
        print("looping")
        read = ser.readline()
        print(read)

        try:
            angle_pan, angle_tilt, sensor = map(int, read.split())
            if angle_pan == 120 and angle_tilt == 75:
                break
        except:
            continue

        angle_pan  = radians(angle_pan)
        angle_tilt = radians(angle_tilt)
        sensor     = transfer(sensor)
        x, y = poltocart(angle_pan, angle_tilt, sensor)
        data.append([x, y, sensor])

    graph(*zip(*data))

class Serial:
    def __init__(self, port=PORT, baud=BAUD, timeout=1000):
        self.ser = serial.Serial(PORT)#, BAUD, timeout=timeout)
        atexit.register(self.close)

    def readline():
        return self.ser.readline()

    def close(self):
        self.ser.close()