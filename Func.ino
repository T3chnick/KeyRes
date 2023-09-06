
void disupd(void){
   DispPage = constrain(DispPage,0,5);
   
 switch (DispPage){
   
   case 0: {  trip = (odometrPulses - tripreset)/24000.0;
              if(trip < 10.00){x = 47;} 
              else if(trip < 100.00){x = 42;} else if(trip < 1000.00){x = 36;} else if(trip < 10000.00){x = 28;} else if(trip < 100000.00){x = 21;}
              //display.setFont(&FreeSans12pt7b);
              PrintMsg(47,20,1000,"trip",clr,nupd);        
              PrintNumF(x,50,trip,1,nclr,upd);  
         
              break; } 
 
   case 1: {  odometr = odometrPulses/24000;
              //display.setFont(&FreeSans12pt7b);
              PrintMsg(49,20,1000,"km",clr,nupd);
              PrintNumI(25,50,odometr,nclr,upd);   
              break; }   
      
   case 3: {  if(th < 7000){
              if(th < 10){x = 57;} else if(th < 100){x = 50;} else if(th < 1000){x = 44;} else if(th < 10000){x = 36;}
              }
              //display.setFont(&FreeSans12pt7b);
              PrintMsg(40,20,200,"taho",clr,nupd);
              PrintNumI(x,50,th,nclr,upd); 
              break; }

   case 2: {  sp = constrain(sp,0,300);
              if(sp < 10){x = 57;} else if(sp < 100){x = 50;} else if(sp < 301){x = 44;} 
              //display.setFont(&FreeSans12pt7b);
              PrintMsg(33,20,200,"speed",clr,nupd);
              PrintNumI(x,50,sp,nclr,upd);
              break; }

   case 4: {  interval = 500;
              display.clearDisplay();
              display.drawBitmap(48, 1,  batt, 32, 32, WHITE);
    
          //    display.setFont(&DSEG14_Classic_Regular_12);
              PrintNumF(35,54,volt(),2,nclr,upd);
              break; }

   case 5: { //display.setFont(&FreeSans12pt7b);
             PrintMsg(2,18,100,"avg",clr,nupd);  PrintNumI(50,18,avg,nclr,nupd);
             PrintMsg(2,40,100,"wkr",nclr,nupd); PrintNumI(50,40,analogRead(wkR_pin),nclr,nupd);
             PrintMsg(2,62,100,"wkl",nclr,nupd); PrintNumI(50,62,analogRead(wkL_pin),nclr,upd); 
             break; } 
}} 


void PrintMsg(uint8_t x, uint8_t y, uint16_t del, const char *msg, boolean clr, boolean upd){
      if(clr) {display.clearDisplay();} 
      
      display.setCursor(x,y);
      display.print(msg);
      if(upd){display.display(); }
      dispupdTime = millis();
      interval = del;
 }

void PrintNumI(uint8_t x, uint8_t y, uint32_t num, boolean clr, boolean upd){
      if(clr) {display.clearDisplay();} 
      display.setCursor(x,y);
      display.print(num);
      if(upd){display.display(); }
      dispupdTime = millis();   
 }

void PrintNumF(uint8_t x, uint8_t y, float num, uint8_t d, boolean clr, boolean upd){
      if(clr) {display.clearDisplay();} 
      display.setCursor(x,y);
      display.print(num,d);
      if(upd){display.display(); }
      dispupdTime = millis();
 }

void initDisplay(void){
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setFont(&FreeSans12pt7b);
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
}

float volt(){
 float v = ReadVolt[0];
 for(uint8_t i = 1; i < 50; i++) {v+= ReadVolt[i];  }
 return(v/50);
}

void SetupPins(void){
  DDRC  |=B01000000;                         // Assign led_pin as output
  pinMode(encA, INPUT_PULLUP);               // Assign enc_A as input Include pull-up resistor
  pinMode(encB, INPUT_PULLUP);               // Assign enc_B as input Include pull-up resistor
  PORTE |=B01000000;                         // Кнопка энкодера
  PORTB |=B00010000;                         // Кнопка Power
  DDRB  |=B00100000; PORTB |=B00100000;      // Выход Power на планшет 
  DDRB  |=B00000010; PORTB &=B11111101;      // Включение блоков питания
  PORTD |=B00011100;  
  pinMode(wkL_pin, INPUT_PULLUP);            // Include pull-up resistor for left key block on steering wheel
  pinMode(wkR_pin, INPUT_PULLUP);            // Include pull-up resistor for rigt key block on steering wheel
  pinMode(asr_pin, INPUT_PULLUP);
}

void avd(void){
    
   display.clearDisplay();
   display.display();
   tabpwpress; delay(20); tabpwrel;
   flag = 1;
   EEPROM.write(18,avg);
   uint8_t i = 0;
   while(i < 15) { i++; Tablet.vol_down(); }
   Tablet.stop();
}


void GoSleep(void){
   tabOFF;
   display.clearDisplay();
   display.display();
} 

void StartTablet(void){
  tabON;
  tabpwpress; pwbtwait = millis();
}

boolean keyWK(uint16_t Val,uint16_t keyVal){
  if(Val>(keyVal-avg)&& Val<(keyVal+avg)) { return 1;} else {return 0;} 
}

 void tahometr(void){                                    //измеряем частоту на входе тахометра по прерыванию
 if(!tt){micros_th = micros();}
 else   {th = (30000000/(micros() - micros_th));}
 tt = !tt;
 tz = 100;
 }

void speedometr(){                               //измеряем частоту на входе спидометра по прерыванию
  if(!st){micros_sp = micros();}
  else   {sp = (150000/(micros() - micros_sp));}
  st = !st;
  sz = 1000;
  odometrPulses ++;
}
