import api
import math
import matplotlib.pyplot as plt
import pprint
import sys
import time

PORT = "COM4"

def transfer(s):
    """Converts sensor reading to distance."""

    a = 134.391
    b = -0.00427218
    return a * math.exp(b * s)

def spheretocart(angle_pan, angle_tilt, hypot):
    """Converts spherical to cartesian."""

    x = hypot * math.sin(angle_tilt) * math.sin(angle_pan)
    y = hypot * math.sin(angle_tilt) * math.cos(angle_pan)
    z = hypot * math.cos(angle_tilt)

    return (x, y, z)

def graph(data):
    data = [
        spheretocart(math.radians(p[0]), math.radians(p[1]), transfer(p[2]))
        for p
        in data
    ]
    X, Y, Z = zip(*data)

    fig = plt.figure()
    ax = fig.add_subplot(projection="3d")
    ax.scatter(X, Y, Z)
    plt.show()

if __name__ == "__main__":
    data = api.getdata(PORT) if sys.argv[1] != "load" else api.getdata(sys.argv[2])
    graph(data)

    if sys.argv[1] == "save":
        with open(f"{round(time.time())}.pickle", "wb") as f:
            data = {(p[0], p[1]): p[2] for p in data}
            pickle.dump(data, f, pickle.HIGHEST_PROTOCOL)