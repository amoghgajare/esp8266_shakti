
while(1):
    gpio=input()
    gpio1=gpio.split(",")
    word=0
    for a in gpio1:
        word=word+(2**int(a))
    word=hex(word)
    if((len(word)-2)>8):
        print("invalid gpio number, number should be betweem 0 and 31")
    else:
        print("write_word(GPIO_DATA_REG,"+"0x"+word[2:].zfill(8)+");")



        
    
        
    
