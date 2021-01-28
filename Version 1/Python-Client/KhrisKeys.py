import warnings
warnings.filterwarnings("ignore")
import serial
from pyautogui import press, typewrite, hotkey
import pyautogui

port = "/dev/tty.usbserial-142320"
keyList = ["f13","f14","f15","f16",
           "f17","f18","f19","f20",
           "f21","f22","f23","f24",
           "m","n","o","p"]

alwaysApply = ["win","command"]
modKey1 = "capslock"
modKey2 = "numlock"
modKey3 = "scrolllock"

debug = False

serialPort = serial.Serial(port , baudrate=115200, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)

serialString = ""                           # Used to hold data coming over UART

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
    for key in hotkeyArgs:
        pyautogui.keyDown(key)
        printDebug("Pressing: "+key)
    for key in hotkeyArgs[::-1]:
        pyautogui.keyUp(key)
        printDebug("Lifting: "+key)

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

while(True):
    # Wait until there is data waiting in the serial buffer
    if(serialPort.in_waiting > 0):
        # Read data out of the buffer until a carraige return / new line is found
        serialString = serialPort.read(1) #.encode('bin')
        inputInt = serialString[0];
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
