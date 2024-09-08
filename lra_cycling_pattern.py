import time
import board
import busio
import adafruit_drv2605
from math import pow

i2c = busio.I2C(board.SCL, board.SDA)
drv = adafruit_drv2605.DRV2605(i2c)

drv.use_LRM()
drv.realtime_value = 0
drv.mode = adafruit_drv2605.MODE_REALTIME

#minVal = 30
#maxVal = 64

stepCount  = 30
step = 1/stepCount
counter = 0

min_sleep = 0.08
max_sleep = 0.3

forward = True
start_time = time.time()

while True:
        
    sleep = min_sleep + pow(counter * step, 2) * (max_sleep - min_sleep)

    drv.realtime_value = 40
    time.sleep(0.01)
    drv.realtime_value = 0
    time.sleep(sleep)
    
    print((sleep,))

    if forward:
        if counter < stepCount - 1:
            counter += 1
        else:
            forward = False
            time.sleep(1)
    else:
        if counter > 0:
            counter -= 1
        else:
            forward = True
            time.sleep(1)
