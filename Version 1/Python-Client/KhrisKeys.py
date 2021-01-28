import warnings
warnings.filterwarnings("ignore")
import serial
from serial.tools import list_ports
from pyautogui import press, typewrite, hotkey
import pyautogui
from time import sleep
import time, sys
import traceback


keyList = ["f9","f10","f11","f12"
           "f13","f14","f15","f16",
           "f17","f18","f19","f20",
           "f21","f22","f23","f24"]

alwaysApply = ["command","shift"] #MAC PREFIX
#alwaysApply = ["win","shift"] #WINDOWS PREFIX

modKey1 = "capslock"
modKey2 = "numlock"
modKey3 = "scrolllock"

debug = True

# DO NOT EDIT BELOW THIS POINT UNLESS YOU KNOW WHAT YOUR DOING

baudrate = 115200
port = "" # This is no longer manually set. The code will check for comports and auto assign once confrimed using "Identification Byte 11111111"
serialPort = None;#serial.Serial(port , baudrate, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)
serialString = ""                           # Used to hold data coming over UART
portConfirmed = False;
shouldShutdown = False;
def pressHotkeys(buttonId, modId):
    hotkeyArgs = alwaysApply.copy();
    useMod1 = shouldUseMod(modId, 1);
    useMod2 = shouldUseMod(modId, 2);
    useMod3 = shouldUseMod(modId, 3);
    if(useMod1):
        hotkeyArgs.append(modKey1)
    if(useMod2):
        hotkeyArgs.append(modKey2)
    if(useMod3):
        hotkeyArgs.append(modKey3)
    hotkeyArgs.append(keyList[buttonId])
    print(str(hotkeyArgs))
    hotkey(*hotkeyArgs)
    #for key in hotkeyArgs:
    #    pyautogui.keyDown(key, interval=0.05)
    #    printDebug("Pressing: "+key)
    #sleep(0.5)
    #for key in hotkeyArgs[::-1]:
    #    pyautogui.keyUp(key, interval=0.05)
    #    printDebug("Lifting: "+key)

def shouldUseMod(totalModId, checkId):
    mods = decodeModID(totalModId)
    return mods[checkId-1]

def decodeModID(modID):
    output = [False, False, False]
    if(modID == 0):
        return output
    if(modID == 1):
        output[0] = True
    if(modID == 2):
        output[1] = True
    if(modID == 3):
        output[2] = True
    if(modID == 4):
        output[0] = True
        output[1] = True
    if(modID == 5):
        output[0] = True
        output[2] = True
    if(modID == 6):
        output[1] = True
        output[2] = True
    if(modID == 7):
        output[0] = True
        output[1] = True
        output[2] = True
    return output

def printDebug(str):
    if(debug):
        print(str)

def runMain():
    global shouldShutdown
    if(serialPort.isOpen() == True):
        print("Connection Successful.")
        while(not shouldShutdown):
            # Wait until there is data waiting in the serial buffer
            if(serialPort.in_waiting > 0):
                # Read data out of the buffer until a carraige return / new line is found
                serialString = serialPort.read(1) #.encode('bin')
                inputInt = serialString[0];
                if(inputInt == 255):
                    printDebug("Ignoring! Identification byte found!")
                else:
                    binRep = "{0:b}".format(inputInt)
                    button = int((inputInt >> 3));
                    mod = int(inputInt&7);
                    printDebug("Byte: "+(str(binRep) + "("+str(int(binRep))+")"))
                    printDebug("Button: "+ str(button))
                    printDebug("  X: "+str(button%4))
                    printDebug("  Y: "+str(int(button/4)))
                    printDebug("Mod: " + str(mod))
                    #press('capslock')
                    #typewrite('I have just pressed button '+str(keyList[button])+' on my KhrisKeys!',interval=0)
                    pressHotkeys(button, mod)
                    printDebug("")
                    printDebug("")
    else:
        print("Serial Connection closed!")
        raise Exception("Connection to the KhrisKeys COM port was not successful.") 

def attemptPortFind():
    global serialPort
    global portConfirmed
    global port
    if(portConfirmed):
        return True
    from serial.tools.list_ports import comports
    ports = list(list_ports.comports())
    for portCheck in ports:
        portLoc = str(portCheck).split(" ")[0];
        if(portLoc.endswith('-')):
            portLoc = portLoc[:-1];
        #print(portLoc)
        #print(str(port))
        try:
            print("Attempting to connect: "+portLoc)
            startTime = int(time.time());
            #serialPort.close()
            serialPort = serial.Serial(portLoc , baudrate, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)
            while(((int(time.time()) - startTime) < 2) and not portConfirmed):
                
                if(serialPort.in_waiting > 0):
                        # Read data out of the buffer until a carraige return / new line is found
                        serialString = serialPort.read(1) #.encode('bin')
                        inputInt = serialString[0];
                        if(inputInt == 255):
                            print("Confirmed correct port!")
                            port = portLoc
                            portConfirmed = True
                            break
                        else:
                            print("Unable to confirm port!")
        except Exception as e:
            print("Error attepting to connect to: "+portLoc)
            track = traceback.format_exc()
            #print(track)
    return portConfirmed


def enteryPoint():
    global serialPort
    global shouldShutdown
    global portConfirmed
    portFound = attemptPortFind();

    if(not portFound):
        print("Unable to find correct port!")
        exit(-1)

    #print(ports)
    try:
        runMain()
    except OSError:
        print("Error Connecting Reattempting in 10 seconds.......")
        sleep(10)
        #global serialPort
        serialPort.close()
        serialPort = serial.Serial(port , baudrate, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)
        #serialPort.open()
        enteryPoint()
    except KeyboardInterrupt:
        print("Shutting down gracefully!")
        shouldShutdown = True
        if(serialPort.isOpen()):
            serialPort.close();
        sys.exit(0)
    except Exception as e:
        print("An unknown error occered! QUITING")
        track = traceback.format_exc()
        print(track)

enteryPoint()