import serial
import serial.tools.list_ports
ser = serial.Serial("COM3", 9600)
while True:
     cc=str(ser.readline())
     val=cc[2:][:-5]
     print(val)
 
