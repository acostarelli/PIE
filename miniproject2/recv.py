from math import abs, exp, pi, sin

import matplotlib.pyplot as plt
import serial

"""Constants
Port for serial communication, baud, and radius of the IR sensor from the center
of the scanner (in cm).
"""
PORT = ""
BAUD = 115200
R_IR = 10


def degtorad(d):
    return (d / 180) * pi


def transfer(v):
    """Converts voltage to distance."""
    a = 3.7619
    b = -0.0308017
    c = 0.467849
    return a * exp(v * b) + c


def poltocart(angle_pan, angle_tilt, radius):
    """Convert polar to cartesian."""
    d = radius * abs(sin(angle_tilt))
    d = R_IR - d

    return (0, 0, 0)


def graph(X, Y, Z):
    fig = plt.figure()
    ax = fig.add_subplot(projection="3d")

    ax.plot_surface(X, Y, Z)
    plt.show()


if __name__ == "__main__":
    data = []

    with serial.Serial(PORT, BAUD) as ser:
        while True:
            try:
                angle_pan, angle_tilt, voltage = map(int, ser.readline().split())
                data.append(
                    poltocart(
                        degtorad(angle_pan), degtorad(angle_tilt), transfer(voltage)
                    )
                )
            except ValueError:
                break

    graph(zip(*data))