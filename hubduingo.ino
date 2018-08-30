
//www.elegoo.com
//2016.12.9

#include <LiquidCrystal.h>
#include <TimerOne.h>
int tempPin = 0;
String message = "WELCOME TO INNOVATION HUB,  WE ARE HAPPY YOU ARE HERE, PLEASE ENJOY :)!";
int iScroll=0;
//                BS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


//****************************************** Motor Section ********************************
#define ENABLE 5
#define DIRA 3
#define DIRB 4
int i;

void setup()
{
  lcd.begin(16, 2);

//**************** Intrupt timer one
  Timer1.initialize(500000);         // initialize timer1, and set a 1/2 second period
  Timer1.pwm(9, 512);                // setup pwm on pin 9, 50% duty cycle
  Timer1.attachInterrupt(display);  // attaches callback() as a timer overflow interrupt

  
//****************************************** Motor Section ********************************
    //---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  Serial.begin(9600);
}
void loop()
{



  //****************************************** Motor Section ********************************
  //---back and forth example
    Serial.println("One way, then reverse");
    digitalWrite(ENABLE,HIGH); // enable on
    for (i=0;i<5;i++) {
    digitalWrite(DIRA,HIGH); //one way
    digitalWrite(DIRB,LOW);
    delay(500);
    digitalWrite(DIRA,LOW);  //reverse
    digitalWrite(DIRB,HIGH);
    delay(500);

  }
  digitalWrite(ENABLE,LOW); // disable
  delay(2000);


  Serial.println("fast Slow example");
  //---fast/slow stop example
  digitalWrite(ENABLE,HIGH); //enable on
  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);
  delay(3000);
  digitalWrite(ENABLE,LOW); //slow stop
  delay(1000);
  digitalWrite(ENABLE,HIGH); //enable on
  digitalWrite(DIRA,LOW); //one way
  digitalWrite(DIRB,HIGH);
  delay(3000);
  digitalWrite(DIRA,LOW); //fast stop
  delay(2000);


  Serial.println("PWM full then slow");
  //---PWM example, full speed then slow
  analogWrite(ENABLE,255); //enable on
  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);
  delay(2000);
  analogWrite(ENABLE,180); //half speed
  delay(2000);
  analogWrite(ENABLE,128); //half speed
  delay(2000);
  analogWrite(ENABLE,50); //half speed
  delay(2000);
  analogWrite(ENABLE,128); //half speed
  delay(2000);
  analogWrite(ENABLE,180); //half speed
  delay(2000);
  analogWrite(ENABLE,255); //half speed
  delay(2000);
  digitalWrite(ENABLE,LOW); //all done
  delay(10000);
}

void display() {
  
//****************************************** temperature section
    int tempReading = analogRead(tempPin);
  // This is OK
  double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
  float tempC = tempK - 273.15;            // Convert Kelvin to Celcius
  float tempF = (tempC * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  /*  replaced
    float tempVolts = tempReading * 5.0 / 1024.0;
    float tempC = (tempVolts - 0.5) * 10.0;
    float tempF = tempC * 9.0 / 5.0 + 32.0;
  */
  // Display Temperature in C
  lcd.setCursor(0, 0);
  //lcd.print("Temp         C  ");
  // Display Temperature in F
  lcd.print("Temp         F  ");
  lcd.setCursor(6, 0);
  // Display Temperature in C
  //lcd.print(tempC);
  // Display Temperature in F
  lcd.print(tempF);
  

//***************************************** second line
  lcd.setCursor(0, 1);
  lcd.print(message.substring(iScroll,iScroll+16));
   Serial.println(message);
   Serial.println(message.substring(iScroll,iScroll+16));
   iScroll++;
   if (iScroll> message.length()) iScroll=0;
}
