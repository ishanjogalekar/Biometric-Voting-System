import serial
import time
import os

ser = serial.Serial(port='COM7', baudrate=9600, timeout=.1)
line = 'rded'
voted = 'recorded'
with open("out.txt", 'r+') as f:
    f.truncate(0)

if __name__ == '__main__':
    while True:
        data = ''
        while ser.inWaiting()>0:
            data += ser.readline().decode('Utf-8')
        # if data:
        #     print ('Got:', data)

        if line in data:
            os.system('python window_app.py')
            