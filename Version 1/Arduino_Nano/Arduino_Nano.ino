/*
  Author: Andrew Aubury
  Email: andrew@aubury.me
  Project: KhrisKeys
  Date: 24/01/2021
  Revision: 1.0.0 BETA
*/

#define BM1 1
#define BM2 2
#define BM3 3

bool acceptInput = true;
bool DEBUG = false; 

int hPins[] = {6, 7, 8, 9};
//int curH = 0; REMOVED IN FAVOR OF LOOP
int lockH = 0;

int vPins[] = {2, 3, 4, 5};
int curV = 0;
int lockV = 0; 

/*
  PIN State at the end of this function as follows:
  All VERTICAL pins are output and HIGH (5v)
  All HORIZONTAL pins are inputs with pullup resistors
*/

void setup() {
  Serial.begin(115200);

  pinMode(A3 , INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);

  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  
  for (int i = 0; i < 4; i++)
  {
    pinMode(hPins[i], INPUT_PULLUP);
    pinMode(vPins[i], OUTPUT);
    digitalWrite(vPins[i], HIGH);
  }
  if (DEBUG){
  Serial.println("READY!");
  }else{
    byte b = B11111111;
    Serial.write(b);
  }
}

//KEEP IN MIND BUTTON IS CLICKED WHEN LOW!

void loop() {
  resetVPins();
  //For now if we are NOT accepting an input check if button is still pressed, before exiting.
  if (!acceptInput) {
    curV = 0;
    digitalWrite(vPins[lockV], LOW);
    //Serial.println("Checking: "+String(lockV)+":"+String(lockH));
    //Serial.println(String(digitalRead(hPins[lockH])));
    bool isClicked  = (digitalRead(hPins[lockH]) == LOW);
    acceptInput = !isClicked;
    if (acceptInput && DEBUG) {
      Serial.println("== UNLOCKED INPUT ==");
      Serial.println(" ");
    }
    return;
  }

  int modifier = getModifier();

  if (curV > 4) {
    curV = 0;
  }

  digitalWrite(vPins[curV], LOW);

  for (int i = 0; i < 4; i++)
  {
    bool isClicked  = (digitalRead(hPins[i]) == LOW);
    if (isClicked) {
      acceptInput = false;
      lockV = curV;
      lockH = i;
      int realV = curV;
      if(i != 0){
       // if(curV == 0){realV = 3;}
       // if(curV == 1){realV = 2;}
       // if(curV == 2){realV = 1;}
       // if(curV == 3){realV = 0;}
       realV = curV - 3;
       if(realV < 0){ realV = realV * -1;}
      }

      int buttonNumber = (realV * 4) + lockH;
      if(DEBUG){
      Serial.println("=== LOCKED INPUT ===");
      Serial.println("V (W): " + String(lockV));
      Serial.println("V (R): " + String(realV));
      Serial.println("H: " + String(lockH));
      Serial.println("M: " + String(modifier));
      Serial.println(" ");
      Serial.println("  -  New System  -  ");

      
      byte dataByte = getDataByte(buttonNumber, modifier);
      int test = (int) dataByte;
      Serial.print("Byte out: ");
      Serial.println(getBinStr(dataByte));
      }else{
        
        
        //String clickCode = String(lockH)+":"+String(realV)+":"+String(modifier);
        //String clickCode  = String(buttonNumber)+":"+String(modifier);
        //Serial.println("CLICKED_"+clickCode);
        Serial.write(getDataByte(buttonNumber, modifier));
      }
    }
  }

curV++;
}

byte getDataByte(int btn, int mod){
  int tmpBtn = btn << 3;
  byte byteBtn = tmpBtn;
  byte byteMod = mod;

  int joinedInt = tmpBtn & mod;
  byte byteJoin = joinedInt;
  
  String btnBin = getBinStr(byteBtn);
  String modBin = getBinStr(byteMod);
  String allBin = joinBinStrings(btnBin, modBin);
  if(DEBUG){
  Serial.println("Byte BTN: "+btnBin);
  Serial.println("Byte MOD: "+modBin);
  Serial.println("Byte ALL: "+allBin);
  }
  byte x = 0b00000000;
  
   for (int bits = 7; bits > -1; bits--) {
     // Compare bits 7-0 in byte
     if (allBin[7-bits] == '1') {
       bitWrite(x, bits, 1);
      }
      else {
        bitWrite(x, bits, 0);
      }
    }
  //byte data[8] = {0,1,0,0,1,1,0,1};
  return x;

}
String getBinStr(int c){
    String tmp = "";
      for (int bits = 7; bits > -1; bits--) {
     // Compare bits 7-0 in byte
     if (c & (1 << bits)) {
       tmp = tmp + "1";
      }
      else {
        tmp = tmp + "0";
      }
    }
    return tmp;
}

String joinBinStrings(String v1, String v2){
      String tmp = "";
      for (int bits = 0; bits < 8; bits++) {
        if(v1[bits] == '1' || v2[bits] == '1'){
          tmp = tmp + "1";
        }else{
          tmp = tmp + "0";
        }
      }
      return tmp;
}

int getModifier(){

  /*
   * MOD 0: NO BUTTON
   * MOD 1: TOP BUTTON
   * MOD 2: MIDDLE BUTTON
   * MOD 3: BOTTOM BUTTON
   * MOD 4: TOP + MIDDLE BUTTON 
   * MOD 5: TOP + BOTTOM BUTTON
   * MOD 6: MIDDLE + BOTTOM BUTTON
   * MOD 7: TOP + MIDDLE + BOTTOM BUTTON
   */
  
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);

  bool tc = (digitalRead(A3) == LOW);
  bool mc = (digitalRead(A4) == LOW);
  bool bc = (digitalRead(A5) == LOW);
  
  if(tc){ digitalWrite(10, HIGH); }
  if(mc){ digitalWrite(11, HIGH); }
  if(bc){ digitalWrite(12, HIGH); }

  if(!tc && !mc && !bc){ return 0;}
  if(tc && !mc && !bc){ return 1;}
  if(!tc && mc && !bc){ return 2;}
  if(!tc && !mc && bc){ return 3;}
  if(tc && mc && !bc){ return 4;}
  if(tc && !mc && bc){ return 5;}
  if(!tc && mc && bc){ return 6;}
  if(tc && mc && bc){ return 7;}

  return 0;
}

void resetVPins() {
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(vPins[i], HIGH);
  }
}
