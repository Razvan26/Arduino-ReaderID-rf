#include <Wiegand.h>

unsigned long x[100] = {4320128, 2878747, 2877628, 2934494, 2882093, 11144689}; //new 

int ledPin = 7;
int magnet = 8;
bool nextWrite = false;
WIEGAND wg;
WIEGAND wgTwo;

void setup() {
  Serial.begin(9600);  
  
  wg.begin(2,3);
  wgTwo.begin(4,5);
  pinMode(ledPin, OUTPUT);
  pinMode(magnet, INPUT);
}

void loop() {

  firstReader();
  secoundReader();
}

void firstReader () {
  if(wg.available())
  {
    Serial.print("Wiegand HEX = ");
    Serial.print(wg.getCode(),HEX);
    Serial.print(", DECIMAL = ");
    Serial.print(wg.getCode());
    Serial.print(", Type W");
    Serial.println(wg.getWiegandType());
    Serial.println(nextWrite); 
      
    for (int i = 0; i <= 100; ++i) {
      
      if (x[i] == wg.getCode()) {

        Serial.print("This is x code : ");
        Serial.println(x[i]);
        Serial.print("This is wg code : ");
        Serial.println(wg.getCode());
        digitalWrite(ledPin, HIGH);

        delay(1000);
        int magnetPosition = digitalRead(magnet);
        delay(900);
        if (magnetPosition == 1) {
          Serial.println("Door is close");
          delay(500);
          for (int l = 0; l <= 10; l++) {
            if (l % 2 == 0) {
              digitalWrite(ledPin, HIGH);
              delay(500);
            }
            else {
              digitalWrite(ledPin, LOW);
            delay(500);
            }
          }
        }
        else {
          Serial.println("Door is open");
          for (int l = 0; l <= 20; l++) {
            if (l % 2 == 0) {
              digitalWrite(ledPin, HIGH);
              delay(500);
            }
            else {
              digitalWrite(ledPin, LOW);
            delay(500);
            }
          }
          
        }
        if (wg.getCode() == 4320128 || wg.getCode() == 2934494) {
          Serial.println("This is master key!");
        }
      }
      
    }
    
    digitalWrite(ledPin, LOW);
    
   
  }
}
void secoundReader () 
{
  if (wgTwo.available()) {
    Serial.print("Wiegand HEX = ");
    Serial.print(wgTwo.getCode(),HEX);
    Serial.print(", DECIMAL = ");
    Serial.print(wgTwo.getCode());
    Serial.print(", Type W");
    Serial.println(wgTwo.getWiegandType());
    for (int j = 0; j <= 100; ++j) {
      if (x[j] == wgTwo.getCode()) {
        Serial.println("OUT!");
      }
    }
  }
}
