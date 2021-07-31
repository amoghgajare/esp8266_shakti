import serial
import serial.tools.list_ports
import requests

#Example String - V14,V24,V34,V44,C3,T34,SOC60,SOH98
ser = serial.Serial("COM3", 9600)
while True:
     cc=str(ser.readline())
     val=cc[2:][:-5]
     string_list=val.split(',')
     v1=string_list[0].replace('V1','')
     v2=string_list[1].replace('V2','')
     v3=string_list[2].replace('V3','')
     v4=string_list[3].replace('V4','')
     curr=string_list[4].replace('C','')
     temp=string_list[5].replace('T','')
     soc=string_list[6].replace('SOC','')
     soh=string_list[7].replace('SOH','')
     result = requests.get('https://api.thingspeak.com/update?key=CXDZFGD1QQ8HYVTG&field1='+str(v1)+'&field2='+str(v2)+'&field3='+str(v3)+'&field4='+str(v4)+'&field5='+str(curr)+'&field6='+str(temp)+'&field7='+str(soc)+'&field8='+str(soh))
     if(result.status_code == 200): print("OK")
     

 
