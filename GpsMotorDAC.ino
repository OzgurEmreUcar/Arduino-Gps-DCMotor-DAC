#include <LiquidCrystal.h>
LiquidCrystal lcd(28, 30, 32, 34, 36, 38);
byte onceki, simdi, data[37], counter, saat, dakika, saniye, enlemDerece, enlemDakika, enlemSaniye,oncekiSaniye;
bool sayiyorum = 0;
unsigned long int zaman;
bool ayarlama = 0;
bool ayarButonBasildi = 0;
bool arttirButonBasildi = 0;
byte sayici = 0;
bool saatDegistir;

int in1 = 4; 
int in2 = 5;
int EnA = 45;
int hiz;
bool yon;
#define butonAyar 2
#define butonArttir 3
#define omega 1.57
int sinyal,bit0,bit1,bit2,bit3,bit4,bit5,bit6,bit7;


void setup() {
pinMode(A8,OUTPUT);
pinMode(A9,OUTPUT);
pinMode(A10,OUTPUT);
pinMode(A11,OUTPUT);
pinMode(A12,OUTPUT);
pinMode(A13,OUTPUT);
pinMode(A14,OUTPUT);
pinMode(A15,OUTPUT);
  for(int i =4 ; i<=13;i++){
  pinMode(i,OUTPUT);
  }
  lcd.begin(8,2);
  
  zaman=millis();
  Serial.begin(230400);
  Serial1.begin(9600);
  onceki = 0;
  pinMode(butonAyar, INPUT);
  pinMode(butonArttir, INPUT);
  
  
  
}

void loop() {
  motorDondur();
  dacCalistir();
  if (Serial1.available() == 1) {
    simdi = Serial1.read();
   
    if (simdi == 65 && onceki == 71) {
      sayiyorum = 1;
      counter = 0;
   
    }
    else if (sayiyorum == 1) {
      data[counter] = simdi;
      counter++;
      if (counter == 37) {
        sayiyorum = 0;
        saat = 10 * (data[1] - 48) + (data[2] - 48)+3;
        dakika = 10 * (data[3] - 48) + (data[4] - 48);
        saniye = 10 * (data[5] - 48) + (data[6] - 48)-7;
        enlemDerece = 10 * (data[11] - 48) + data[12] - 48;
        enlemDakika = 10 * (data[13] - 48) + data[14] - 48;
        enlemSaniye = byte( 6 * (data[16] - 48) + 0.06 * float(data[17] - 48) + 0.006 * float(data[18] - 48) + 0.0006 * float(data[19] - 48) + 0.00006 * float(data[20] - 48));

  if(saat >= 24)
  saat = 0;
    while(1){


 if (millis()>=zaman+1000){
  zaman=millis();
  saniye++;
    if (saniye==60){
      saniye=0;
      dakika++;
      }
    if (dakika==60){
      dakika=0;
      saat++;
      }
    if (saat>=24){
      saat=0;}
  }
  lcd.setCursor(4, 0);
 if (saat<10)
  lcd.print("0");
  lcd.print(saat);
  lcd.print(":");
 if (dakika<10)
  lcd.print("0");
  lcd.print(dakika);
  lcd.print(":");
 if (saniye<10)
  lcd.print("0");
  lcd.print(saniye);  
  lcd.print("            ");
  
   
  ayarButonBasildi = digitalRead(butonAyar);  

  if(ayarButonBasildi == 1 ){
    delay(1000);
    
    sayici++; 
    ayarButonBasildi = digitalRead(butonAyar);  
     if(sayici == 3){
      lcd.clear();
      ayarlama =! ayarlama;
      sayici = 0;
      
  }  

 
  while(ayarlama == true){
  digitalWrite(13,HIGH);
   if (millis()>=zaman+1000){
  zaman=millis();
  saniye++;
    if (saniye==60){
      saniye=0;
     
      }
    if (dakika==60){
      dakika=0;
    
      }
    if (saat>=24){
      saat=0;}
  }
 lcd.setCursor(4, 0);
 if (saat>=24){
      saat=0;}
 if (saat<10)
  lcd.print("0");
  lcd.print(saat);
  lcd.print(":");
 if (dakika<10)
  lcd.print("0");
  lcd.print(dakika);
  lcd.print(":");
 if (saniye<10)
  lcd.print("0");
  lcd.print(saniye);
  lcd.print("            ");
  lcd.setCursor(0,1);
   
     ayarButonBasildi = digitalRead(butonAyar);  

  if(ayarButonBasildi == 1 ){
    delay(1000);
    
    sayici++; 
    ayarButonBasildi = digitalRead(butonAyar);  
    
     if(sayici == 3){
      ayarlama =! ayarlama;
      sayici = 0;  
     } 
     if(sayici == 1 ){
      saatDegistir =! saatDegistir;
      
      } 
    
    
    }
    
if(saatDegistir){
  
  arttirButonBasildi = digitalRead(butonArttir);
  if(arttirButonBasildi == 1){
    saat++;
    delay(500);
    if(saat >= 24)
      saat = 0;

    if (saniye==60){
      saniye=0;
     
      }  
    }
    
  
  }else{
    arttirButonBasildi = digitalRead(butonArttir);
  if(arttirButonBasildi == 1){
    dakika++;
    delay(500);
    if(dakika == 60)
      dakika = 0;

     if (saniye==60){
      saniye=0;
     
      }  
    }
    }



 
      }


  
    
    }

  
}    
        
}
        
        
        
        
        
        
        

     
      }
    
    onceki = simdi;
   
  }  }


















  void motorDondur(){
 

hiz = analogRead(A0);
hiz = hiz*0.2492668622;
Serial.println(hiz);
if(hiz == 127){
digitalWrite(in1, LOW); 
digitalWrite(in2, LOW);
analogWrite(EnA,0); 
digitalWrite(9, HIGH); 
digitalWrite(10, HIGH);

  }else if(hiz > 127){
yon = true;    
digitalWrite(in1, LOW); 
digitalWrite(in2, HIGH);
analogWrite(EnA,hiz-127); 
digitalWrite(9, LOW); 
digitalWrite(10, HIGH);
if(  hiz -127 > 40 && yon == true)
digitalWrite(11,HIGH);
else
digitalWrite(11,LOW);
if(hiz -127 > 80 && yon == true)
digitalWrite(12,HIGH);
else
digitalWrite(12,LOW);
if(hiz -127 > 120 && yon == true)
digitalWrite(13,HIGH);
else
digitalWrite(13,LOW);







    
    }else if(hiz < 127){
    
yon = false;
digitalWrite(in1, HIGH); 
digitalWrite(in2, LOW);
analogWrite(EnA,-(hiz-127)); 
digitalWrite(9, HIGH); 
digitalWrite(10, LOW);    
if(  -(hiz-127) > 40 && yon == false)
digitalWrite(8,HIGH);
else
digitalWrite(8,LOW);
if(-(hiz-127) > 80 && yon == false)
digitalWrite(7,HIGH);
else
digitalWrite(7,LOW);
if(-(hiz-127) > 120 && yon == false)
digitalWrite(6,HIGH);
else
digitalWrite(6,LOW);

    }
}

void dacCalistir(){
  sinyal = 127 + int(127.0*sin(omega*float(millis())));
  bit7 = sinyal/128;
  sinyal -= 128*bit7;
  bit6 = sinyal/64;
  sinyal -= 64*bit6;
  bit5 = sinyal/32;
  sinyal -= 32*bit5;
  bit4 = sinyal/16;
  sinyal -= 16*bit4;
  bit3 = sinyal/8;
  sinyal -= 8*bit3;
  bit2 = sinyal/4;
  sinyal -= 4*bit2;
  bit1 = sinyal/2;
  bit0 = sinyal - 2*bit1;

  digitalWrite(A15,bit7);
  digitalWrite(A14,bit6);
  digitalWrite(A13,bit5);
  digitalWrite(A12,bit4);
  digitalWrite(A11,bit3);
  digitalWrite(A10,bit2);
  digitalWrite(A9,bit1);
  digitalWrite(A8,bit0);
  }
