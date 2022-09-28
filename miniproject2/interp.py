import math

PAN_MIN = 70#50
PAN_MAX = 110#120
TILT_MIN =50#50
TILT_MAX =110#140

PAN_MID  = ((PAN_MAX - PAN_MIN) / 2) + PAN_MIN
TILT_MID = ((TILT_MAX - TILT_MIN) / 2) + TILT_MIN

def interp(x0, xm, y0, ym):
    def ret(x):
        slope = (ym - y0) / (xm - x0)
        return slope * (x - x0) + y0

    return ret

def sinterp(x0, xm, y0, ym):
    def ret(x):
        slope = (ym - y0) / (xm - x0)
        return math.sin(slope * (x - x0) + y0)

    return ret
pinterp = interp(PAN_MIN , PAN_MAX , 0, math.pi)
tinterp = interp(TILT_MIN, TILT_MAX, 0, math.pi)

panterp = sinterp(PAN_MIN , PAN_MAX , -math.pi/2, math.pi)
tilterp = sinterp(TILT_MIN, TILT_MAX, -math.pi/2, math.pi/2)