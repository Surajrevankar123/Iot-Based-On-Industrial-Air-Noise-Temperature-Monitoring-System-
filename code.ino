#include <LiquidCrystal_I2C.h>       
LiquidCrystal_I2C lcd(0x27,16,2);   //for 16x2 lcd display
int buzzer1 = 13;
int GASA0 = A0;
int gasvalue1;
int buzzer2 = 13;
int GASA1 = A1;
int gasvalue2;
int num_Measure = 128 ; // Set the number of measurements   
int pinSignal = A0; // pin connected to pin O module sound sensor  
int redLed = 5; 
long Sound_signal;    // Store the value read Sound Sensor   
long sum = 0 ; // Store the total value of n measurements   
long level = 0 ; // Store the average value   
int soundlow = 40;
int soundmedium = 500;
#define LM35PIN A0
int adcValue;
float milliVolt;
float tempInC;
float tempInF;
byte degree_symbol[8] =
{
  0b00111,
  0b00101,
  0b00111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
void setup() {
  lcd.init();       //initiute the lcd1                     
 lcd.init();
 lcd.backlight(); 
 pinMode(buzzer1, OUTPUT); 
 lcd.setCursor(2,0);
 lcd.print("LPG LEAKAGE1"); 
 lcd.setCursor(1,1);
 lcd.print("LEVEL DETECTOR1"); 
 delay(5000);
 lcd.init();     // initiate the lcd                  
 lcd.init();
 lcd.backlight(); 
 Serial.begin(9600);
 pinMode(buzzer2, OUTPUT); 
 lcd.setCursor(3,0);
 lcd.print("welcome to"); 
 lcd.setCursor(1,1);
 lcd.print("JOSH ARDUINO"); 
 delay(5000);
 lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("LM35 Temperature");
  lcd.setCursor(0,1);
  lcd.print("Sensor - Arduino");
  lcd.createChar(1, degree_symbol);
  delay(2000);
  lcd.clear();
}
void loop() {
  int analogSensor1 = analogRead(GASA0);
  int gasvalue1=(analogSensor1-50)/25;         //gas module sensitivity
  lcd.setCursor(0,0);
  lcd.print("LPG LEVEL1:");
  lcd.setCursor(10,0);
  lcd.print(gasvalue1);
  lcd.setCursor(12,0);
  lcd.print("%");
   //check if it has reached the threshold value 
  if (gasvalue1 >= 40)                      //gas percentage alert
  {
  lcd.setCursor(0,1);
  lcd.print("DANGER1");
  tone(buzzer1, 5000, 3000);
  }
  else
  {
  lcd.setCursor(0,1);
  lcd.print("NORMAL1");
  noTone(buzzer1);
  }
  delay(500);
  lcd.clear();
  int analogSensor2 = analogRead(GASA1);
  int gasvalue2=(analogSensor2-50)/35;       //gas module sensitivity
  lcd.setCursor(0,0);
  lcd.print("GAS Level2:");
  lcd.setCursor(10,0);
  lcd.print(gasvalue2);
  lcd.setCursor(12,0);
  lcd.print("%");
  // Checks if it has reached the threshold value
  if (gasvalue2 >= 10)              //gas percentage alert
  {
    lcd.setCursor(0,1);
   lcd.print("DANGER2");
    tone(buzzer2, 1000, 10000);
  }
  else
  {
  lcd.setCursor(0,1);
  lcd.print("NORMAL2");
    noTone(buzzer2);
   }
  delay(500);
  lcd.clear();
  // Performs 128 signal readings   
  for ( int i = 0 ; i <num_Measure; i ++)  
  {  
   Sound_signal = analogRead (pinSignal);  
    sum =sum + Sound_signal;  
  } 
  level = sum / num_Measure; // Calculate the average value   
  Serial.print("Sound Level: ");
  lcd.print("Sound Level= ");
  Serial.println (level-33);  
  lcd.print(level-33);
  if(level-33<soundlow)
  {
    lcd.setCursor(0,2);
    lcd.print("Intensity= Low");
     digitalWrite(redLed,LOW);
  }
  if(level-33>soundlow && level-33<soundmedium)
  {
    lcd.setCursor(0,2);
    lcd.print("Intensity=Medium"); 
     digitalWrite(redLed,LOW); 
  }
  if(level-33>soundmedium)
  {
    lcd.setCursor(0,2);
    lcd.print("Intensity= High");   
    digitalWrite(redLed,HIGH); 
  }
  sum = 0 ; // Reset the sum of the measurement values  
  delay(200);
  lcd.clear();
  adcValue = analogRead(LM35PIN);
  milliVolt = ((adcValue * 4870.0) / 1024);
  tempInC = milliVolt/10; /* Temperature in Degree Celsius */
  tempInF = ((tempInC * 9/5) + 32); /* Temperatue in Degree Fahrenheit */ 
  lcd.setCursor(0,0);
  lcd.print("Temp = ");
  lcd.setCursor(7,0);
  lcd.print(tempInC);
  lcd.write(1);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Temp = ");
  lcd.setCursor(7,1);
  lcd.print(tempInF);
  lcd.write(1);
  lcd.print("F");
  delay(500);
  }

