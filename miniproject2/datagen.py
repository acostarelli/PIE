import math
import random

PAN_MIN = 50
PAN_MAX = 120
TILT_MIN = 75
TILT_MAX = 165

def sinterp(x0, xm, y0, ym):
    def ret(x):
        slope = (ym - y0) / (xm - x0)
        return math.sin(slope * (x - x0) + y0)

    return ret

panterp = sinterp(PAN_MIN , PAN_MAX , 0, math.pi)
tilterp = sinterp(TILT_MIN, TILT_MAX, 0, math.pi)

def sensor(pan, tilt):
    return 100 * panterp(pan) * tilterp(tilt)

    # use sin to determine strength
    # and inequalities to determine if its in range

if __name__ == "__main__":
    with open("data.txt", "w") as f:
        for pan in range(PAN_MIN, PAN_MAX, 5):
            for tilt in range(TILT_MAX, TILT_MIN, -1):
                f.write(f"{pan} {tilt} {sensor(pan, tilt)}\n")