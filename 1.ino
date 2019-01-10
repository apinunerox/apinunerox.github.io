#include<SPI.h>
#include"nRF24L01.h"
#include"RF24.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);// PCF8574A =  0x3F

RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

int msg[1];
int LED1 = 4;
int LED2 = 5;
int LED3= 6;
int LED4 = 7;

int Time1 = 0;
int Time2 = 0;
int Time3 = 0;
int Time4 = 0;

int TimeA = 0;
int TimeB = 0;
int TimeC = 0;
int TimeD = 0;




void setup(void)
{
    lcd.begin();
    lcd.home();
    Serial.begin(9600);
    radio.begin();
    radio.openReadingPipe(1,pipe);
    radio.startListening();
    
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);

lcd.setCursor(1,0);  lcd.print("Time =       ms");   
lcd.setCursor(1,1);  lcd.print("Time =       ms");     
}


void loop(void){
if(radio.available()){
bool done = false;
while(!done){
done = radio.read(msg, 1);
Serial.println(msg[0]);

if(msg[0] == 1 )   //   ระดับที่ 1 
    { 
      Time1++;
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      delay(1000);  
      lcd.setCursor(10,0);  lcd.print(Time1);    
      
         
    }
else if(msg[0] == 2)  
    { 
      TimeA = Time1 * 2 ;
      int A = ( TimeA + ( 0.1 * TimeA )); 
   
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
      digitalWrite(LED1, LOW);
      lcd.setCursor(10,1);  lcd.print(A);    
      
      Time2++; 

      delay(1000);  
lcd.setCursor(1,0);  lcd.print("Time =       ms");         
      lcd.setCursor(10,0);  lcd.print(Time2);      

    //  TimeD = Time4 * 0.5 ; 
    //  int D = ( TimeD + (0.1 * TimeD)); 
    //  lcd.setCursor(0,0);  lcd.print("                 "); 
     // lcd.setCursor(8,0);  lcd.print(D); 

      
    }
else if(msg[0] == 3) 
    { 
      Time4++;
      delay(1000);  
      
      digitalWrite(LED3, HIGH);
      digitalWrite(LED4, LOW);
      digitalWrite(LED2, LOW);
      
      TimeB = Time2 * 0.5 ; 
      int B = ( TimeB + (0.1 * TimeB));  
lcd.setCursor(1,1);  lcd.print("Time =       ms");        
      lcd.setCursor(10,1);  lcd.print(B);    
  
  //    TimeC = Time3 * 2 ;
  //    int C = ( TimeC + ( 0.1 * TimeC ));     
   //   lcd.setCursor(8,1);  lcd.print(C); 
lcd.setCursor(1,0);  lcd.print("Time =       ms");   
    lcd.setCursor(10,0);  lcd.print(Time4); 
      
    }    
else if(msg[0] == 4) 
    { 
      Time4 = 0;
      Time3++;
       delay(1000);  
      digitalWrite(LED4, HIGH);
      digitalWrite(LED3, LOW);

   
 lcd.setCursor(0,0);  lcd.print("                  ");     
 lcd.setCursor(0,1);  lcd.print("                  ");  
  lcd.setCursor(7,0);  lcd.print("FULL");     
    
   //   lcd.setCursor(10,0);  lcd.print(Time3);   


    }

//------------------------------------------
delay(10);}}
else
{
   digitalWrite(LED1, LOW);
  Serial.println("boş");
}

}
