import serial

port = "/dev/tty.usbserial-142320"
serialPort = serial.Serial(port , baudrate=115200, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)

serialString = ""                           # Used to hold data coming over UART

while(1):
    # Wait until there is data waiting in the serial buffer
    if(serialPort.in_waiting > 0):
        # Read data out of the buffer until a carraige return / new line is found
        serialString = serialPort.read(1) #.encode('bin')
        inputInt = serialString[0];
        binRep = "{0:b}".format(inputInt)
        button = int((inputInt >> 3));
        mod = int(inputInt&7);
        print("Button: "+ str(button))
        print("  X: "+str(button%4))
        print("  Y: "+str(int(button/4)))
        print("Mod: " + str(mod))
        print("")
        print("")
