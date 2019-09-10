import serial
serialA = serial.serial('/dev/ttyACM0',115200)
serialA.open()

serialA.write("hola desde raspi")
try:
     while 1:
        response = serilA.readLine()
        print(response)

except KeyboardInterrupt:
    serialA.close()

