#include <Timers.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

bool first = false;
bool two = false;
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
String ustalonyczas;
byte rowPins[rows] = {8, 9, 10, 11}; 
byte colPins[cols] = {12, 13, A0}; 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );
int alarm_poz = 1;
char pin_1 = '1';
char pin_2 = '2';
char pin_3 = '3';
char pin_4 = '7';
Timer timer;
int minuty = 0;
float czasU = 0;
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
        czas = 60000;
        lcd.setCursor(5,0);
        ustalonyczas = String(key);
        Serial.print(key);
        lcd.print(ustalonyczas);
        stan = 5;
        break;
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
            Serial.print(alarm_poz);
          } else if (alarm_poz == 4 && key == pin_4) { 
              lcd.setCursor(8,1);
              lcd.print(key);
              stan = 2;
              break;
          } 
          else{  
            stan = 4;
          }
          
     }
     break;
    case 4:
        pinMode(A2, OUTPUT);
        digitalWrite(A2, LOW);
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.write("Przegranko");
        lcd.setCursor(4,1);
        lcd.write("Unlucky");
        delay(5000000);
        break;
    case 5: 
          if(key) {
            lcd.setCursor(6,0);
            String nowyustalonyczas = ustalonyczas + key;
            minuty = nowyustalonyczas.toInt() - 1;
            czasU = minuty;
            lcd.print(key);
            Serial.println(nowyustalonyczas);
            Serial.println(minuty);
            keypad.waitForKey();
            stan = 3;
            break;
          }
  }
  if((stan != 4 || stan != 2) && stan != 1 && stan != 5) { 
    int licznik = 1;
    int sekundy = ((int(czas/1000))-(int(millis()/1000)));
    if(minuty > 10)
    {
      lcd.setCursor(5,0);
      lcd.print(minuty);
    }
    else {
      lcd.setCursor(5,0);
      lcd.print("0");
      lcd.print(minuty);
    }
    lcd.setCursor(7,0);
    lcd.print(":");
    if(sekundy >= 10) {
      lcd.setCursor(8,0);
      lcd.print(sekundy);
    }
    else {
      lcd.setCursor(8,0);
      lcd.print("0");
      lcd.print(sekundy);
      lcd.print("          ");
    }
    if(sekundy == 0 && minuty > 0 ) {
      minuty--;
      licznik++;
      czas = licznik*60000;
    }
    else if (minuty == 0) {
      if(czasU > 0) {
        licznik++;
        Serial.print(czasU);
        czas = licznik*60000;
      }
      else if (czasU = 0) {
        czas = licznik*60000;
      }
      minuty = 0;
    }
    if (minuty <= 0 && sekundy <= 0) {
      stan = 4;
    }
    
  }  
  if(stan == 3){
    digitalWrite(A2, LOW); 
    if (timer.available()){
        digitalWrite(A2, HIGH);
        timer.restart();
    }
  }

}
