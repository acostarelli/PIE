import math
import random

def j(n, mn=-1, mx=1):
    return n + random.randint(mn, mx)

def sensor(pan, tilt):
    return 100 * panterp(pan) * tilterp(tilt)

    # use sin to determine strength
    # and inequalities to determine if its in range

if __name__ == "__main__":
    with open("data.txt", "w") as f:
        for pan in range(PAN_MIN, PAN_MAX, 5):
            for tilt in range(TILT_MAX, TILT_MIN, -1):
                f.write(f"{j(pan)} {j(tilt)} {j(sensor(pan, tilt))}\n")