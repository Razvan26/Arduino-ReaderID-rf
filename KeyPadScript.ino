#include <Keypad.h>

const byte numRows = 4;

const byte numCols = 4;

int pinLed = A0;

char keymap[numRows][numCols] = {{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}};

byte rowPin[numRows] = {2,3,4,5};

byte rowCols[numCols] = {6,7,8,9};

Keypad myKeypad = Keypad(makeKeymap(keymap), rowPin, rowCols, numRows, numCols);

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(pinLed, OUTPUT);
}
char pressedKeys[4];
int numerOfPress = 0;
void loop() {
  // put your main code here, to run repeatedly:
  char keypressed = myKeypad.getKey();
  
  
  
  if (keypressed != NO_KEY && numerOfPress < 4) {
    Serial.println(keypressed);
    numerOfPress += 1;
    pressedKeys[numerOfPress] = keypressed;
    Serial.print("Key : ");
    Serial.println(numerOfPress);
  }
  
  if (numerOfPress >= 4) {
    for (int i = 0; i <= 4; ++i) {
      Serial.print("This is your password : ");
      Serial.print(pressedKeys[i]);
      delay(100);
      numerOfPress = 0;
      
    }

    if (pressedKeys[1] == '1' && pressedKeys[2] == '2' && pressedKeys[3] == '3')
    {
      analogWrite(pinLed, 1000);
      delay(1000);
      Serial.println("Code is correct!");    
    }
   
  }
  
  
}
