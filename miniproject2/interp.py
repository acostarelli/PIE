import math

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