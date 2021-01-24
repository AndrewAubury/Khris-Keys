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
  Serial.begin(9600);

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
  Serial.println("READY!");
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
    if (acceptInput) {
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
      Serial.println("=== LOCKED INPUT ===");
      Serial.println("V: " + String(lockV));
      Serial.println("H: " + String(lockH));
      Serial.println("M: " + String(modifier));
    }
  }

curV++;
}

int getModifier(){
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  
  if(digitalRead(A3) == LOW){
    digitalWrite(10, HIGH);
    //return 1;
    //Serial.println("MOD 1 CLICKED");
  }
  
  if(digitalRead(A4) == LOW){
    digitalWrite(11, HIGH);
    //return 2;
    //Serial.println("MOD 2 CLICKED");
  }
  
  if(digitalRead(A5) == LOW){
    digitalWrite(12, HIGH);
    //return 3;
    //Serial.println("MOD 3 CLICKED");
  }
  return 0;
}

void resetVPins() {
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(vPins[i], HIGH);
  }
}
