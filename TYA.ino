#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

byte data_count = 0;
char Data[13] = "0";
char customKey;
int RunMass = 0;
int intData = 0;
int state;
int stosta = 0;

int PPKg = 500;
int maxKg = 15;

const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {19, 18, 5, 17};
byte colPins[COLS] = {16, 4, 14, 12};
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void clearData(){
  while(data_count != 0){
    Data[data_count--] = 0;
  }
  return;
}
void dating(){
  if ((((customKey) == '1') or ((customKey) == '2') or ((customKey) == '3') or ((customKey) == '4') or ((customKey) == '5') or ((customKey) == '6') or ((customKey) == '7') or ((customKey) == '8') or ((customKey) == '9') or ((customKey) == '0')) and stosta == 0){
      Data[data_count] = customKey;
      data_count++;
      if ((RunMass)>=(maxKg)){
        clearData();
        lcd.clear();
         lcd.setCursor(0, 2);
         lcd.print("Cannot Exceed");
  }
    }
  if ((customKey) == 'A') {
    clearData();
    
    lcd.setCursor(0, 0);
    lcd.print("Price");
    lcd.setCursor(19, 1);
    lcd.print("N");
    state == 0;
  }
  if ((customKey) == 'D') {
    clearData();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Weight");
    lcd.setCursor(18, 1);
    lcd.print("Kg");
    state == 1;
  }
  if ((customKey) == 'C'){
    clearData();
    lcd.clear();
    stosta = 0;
  }
  if ((customKey) == 'B') {
    lcd.setCursor(0, 2);
    lcd.print("Buying");
    stosta = 1;
  }
}
void setup(){
  lcd.backlight();
  lcd.init();
}
void loop(){
  intData = atoi(Data);
  lcd.setCursor(0, 1);
  lcd.print(intData);
   customKey = customKeypad.getKey();
   dating();
   if (state == 0){
    RunMass = ((intData)/PPKg);
   }
   if (state == 1){
    RunMass = intData;
   }
}
