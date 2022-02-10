import serial
import time
import sys

setBootDelay        = 'A'
setImpulseLength    = 'B'
getSettings         = 'C'
startGlitch         = 'D'   


#initialize serial port
try:
    print("STATUS: try to open glitcher port!")
    teensy_port = serial.Serial(port = '/dev/ttyACM0', baudrate = 115200, timeout = 3)
    time.sleep(2)
    print("STATUS: glitcher is ready to use!")

except:
    print("ERROR: cannot open glitcher port!")
    sys.exit(1)


def send_data(out_data):
    try:
        int(out_data)                       # add non numeric character to 
        out_data = f"{out_data}\n"          # speed up Serial.parseInt()
    
    except:
        None
    
    teensy_port.write(bytes(out_data, 'utf8'))
    time.sleep(.05)


def receive_data():                 
    in_data = teensy_port.readline()        
    in_data = in_data[:-2].decode('utf8')   # remove "\r\n" from string
    return in_data


def check_if_glitch_succeed():
    return False                          # implement your own check function


while (True):
    for boot_delay in range (200, 300, 1):      # delta_boot in milliseconds
        for impuls_length in range (5, 10, 1):   # delta_impuls

            send_data(setBootDelay)
            send_data(boot_delay)

            send_data(setImpulseLength)
            send_data(impuls_length)
            
            send_data(getSettings)
            print(f"STATUS: settings -> {receive_data()}")
            
            send_data(startGlitch)
            time.sleep(.3)

            if check_if_glitch_succeed():
                print("STATUS: glitched successfully!")
                teensy_port.close()
                sys.exit(0)