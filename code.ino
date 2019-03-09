#include <Timers.h>
#include <LiquidCrystal.h>
#include <Keypad.h>


float czas=1000000;
//lcd
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(2,3,4,5,6,7);
int poz = 0;
int stan = 1;
int win = 0;
float start;  
//Klawiatura
const byte rows = 4; 
const byte cols = 3; 
float dz = 0.001;
char keys[rows][cols] = {
  {'#','0','*'},
  {'9','8','7'},
  {'6','5','4'},
  {'3','2','1'}
};
byte rowPins[rows] = {8, 9, 10, 11}; 
byte colPins[cols] = {12, 13, A0}; 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );
int alarm_poz = 1;
char pin_1 = '1';
char pin_2 = '2';
char pin_3 = '3';
char pin_4 = '7';

char b_1 = '1';
char b_2 = '2';
char b_3 = '3';
char b_4 = '4';
char b_5 = '5';
char b_6 = '6';
char b_7 = '7';
char b_8 = '8';
char b_9 = '9';
char b_10 = '*';
char b_11 = '#';
Timer timer;

void setup() {
  timer.begin(500);
  Serial.begin(9600);
  pinMode(A2, OUTPUT);
  digitalWrite(A2, HIGH);
  lcd.begin(16, 2);
  lcd.print("Czas:");
  lcd.setCursor(0,1);
  lcd.print("Kod:");
}

void loop() {
  char key = keypad.getKey(); 
  if(stan == 3 && stan != 1){
    start = millis();
  }
  switch(stan) {
    case 1:
      if(key) {
        lcd.setCursor(5,0);
        lcd.print(key);
        Serial.print("Key:["+String(key)+"]\n");
        delay(500);
        if(key == b_1) {
            czas = 1*60019;
        } else if(key == b_2) {
            czas = 2*60019;
        } else if(key == b_3) {
            czas = 3*60019;
        } else if(key == b_4) {
            czas = 4*60019;
        } else if(key == b_5) {
            czas = 5*60019;
        } else if(key == b_6) {
            czas = 6*60019;
        } else if(key == b_7) {
            czas = 7*60019;
        } else if(key == b_8) {
            czas = 8*60019;
        } else if(key == b_9) {
            czas = 9*60019;
        } else if(key == b_10) {
            czas = 15*60019;
        } else if(key == b_11) {
            czas = 20*60019;
        } 
        stan = 3;
        break;
      }
    case 3:
    if (key) {
          
          if (alarm_poz == 1 && key == pin_1) {
            lcd.setCursor(5,1);
            lcd.print(key);
            alarm_poz++; 
          } else if (alarm_poz == 2 && key == pin_2) {
            lcd.setCursor(6,1);
            lcd.print(key);
            alarm_poz++;          
          } else if (alarm_poz == 3 && key == pin_3) {
            lcd.setCursor(7,1);
            lcd.print(key);
            alarm_poz++;         
          } else if (alarm_poz == 4 && key == pin_4) { 
              lcd.setCursor(8,1);
              lcd.print(key);
              stan = 2;     
          } else {
             stan = 4; 
          }
    }
         break;
    case 2:
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.write("Wygranko!");
        lcd.setCursor(4,1);
        lcd.write("DOBRZE :D");
        pinMode(A2, INPUT);
        delay(5000000);
        break;
    case 4:
        pinMode(A2, OUTPUT);
        digitalWrite(A2, LOW);
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.write("Przegranko");
        lcd.setCursor(4,1);
        lcd.write("CIOTY :P");
        delay(5000000);
        break;
  
  }
  if((stan != 4 || stan != 2) && stan != 1) { 
    lcd.setCursor(5,0);
    double licznik = (czas/1000)-(millis()/1000);
    lcd.print(licznik,1);
    if (licznik <= 0) {
     stan = 4;
  }
  }
  Serial.print("Czas["+String(czas)+"]\n");
  Serial.print("Start["+String(start)+"]");
  
  if(stan == 3){
    digitalWrite(A2, LOW); 
    if (timer.available()){
        digitalWrite(A2, HIGH);
        timer.restart();
    }
  }

}
