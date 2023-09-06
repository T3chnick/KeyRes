void wkl(void){ ///// Steering wheel left block /////
  uint16_t wkl = analogRead(wkL_pin);
  fwddel = map(millis()-eventL, 0, 30000, 100, 5);
 if(flagL != 7){
 if(wkl>1000) {eventL=millis();
         if(flagL == 3 || flagL == 8 ) {flagL = 0;} 
    else if(flagL == 2) { next(); flagL = 0; } 
    else if(flagL == 4) { prew(); flagL = 0; }
    else if(flagL == 5) { DispPage++; flagL = 0; disupd();}
    else if(flagL == 6) { DispPage--; flagL = 0; disupd();}
 }
 else if(millis()-eventL > 10 && millis()-eventL < 499) {
         if(keyWK(wkl,key1)) { flagL = 2; } //next
    else if(keyWK(wkl,key2)) { flagL = 4; } //prev 
    else if(keyWK(wkl,key3)) { flagL = 5; } //nav
    else if(keyWK(wkl,key4)) { flagL = 6; } //bk
 } 
 else if(millis()-eventL > 500 ) {
         if(keyWK(wkl,key1)) { fwd(fwddel); flagL = 3;} //fast forward
    else if(keyWK(wkl,key2)) { rew(fwddel); flagL = 3;} //Rewind 
    else if(keyWK(wkl,key4) && millis()-eventL > 2500) {
            flagL = 8; tripreset = odometrPulses; EEPROM.put(10, tripreset); //EEPROM.put(0,odometrPulses);
            PrintMsg(20,40,1000,"TRIP 0",clr,upd);
}
  }
  if(millis()-eventL > 30000) {flagL = 7;} //protect
 } //End
}

void wkr(void){ ///// Steering wheel right block /////
 uint16_t wkr = analogRead(wkR_pin);
 if(flagR != 7){  
 if(wkr>=1000) { eventR=millis();
         if(flagR == 1) {flagR = 0; Tablet.play_pause(); } 
    else if(flagR == 2) {flagR = 0; keypress(202);}  }
 else if(millis()-eventR > 10){
         if(keyWK(wkr,key1)) {volup(150);}
    else if(keyWK(wkr,key4)) {voldn(150);} 
    else if(keyWK(wkr,key2) && !flagR) { flagR = 1; } 
    else if(keyWK(wkr,key3) && !flagR) { flagR = 2; } 
 }   
  if(millis()-eventR > 30000) {flagR = 7;} //protect}
 }//End
}

void ASR(void){
  uint16_t asr = analogRead(asr_pin);
  if(asr < 700 && !asrF){
        if(asr < 35 ) {keypress(200); asrF = 1;}
   else if(asr > 35 && asr < 75 ) {keypress(201); asrF = 1;}
  } else if(asr > 1000){asrF = 0;}
 // Serial.println(asr);
}


void btnst(void){
   boolean btn = btnpin;
   if(btn) {bttime = millis();}
   if(millis()-bttime > 600 && millis()-bttime < 620 && !btn) 
     {nsst = !nsst; delay(22); (nsst)? led_High:led_Low; 
     }
       
   else if (acc && millis()-bttime > 2000 && millis()-bttime < 2040 && !btn)
     {nsst = !nsst;flagL = 0; flagR = 0; delay(40);}
}

void enc(void){
Epos = Epos << 2 | ((PINB & B00001100)>>2);
DoEnc();
}

void DoEnc(void){
   // Serial.println(Epos,HEX);
      if(Epos == 0x4B) {if(enckey && enckeyflag < 2)
        {prew(); enckeytime -= 1000; } else {voldn(0);} }
 else if(Epos == 0x87) {if(enckey && enckeyflag < 2)
        {next(); enckeytime -= 1000; } else {volup(0);}}

}

void Enckey(void){

 if(enckeyflag == 0 && millis() - enckeytime > 10 && enckey )   {enckeyflag = 1;}
 if(enckeyflag == 1 && millis() - enckeytime < 200 && !enckey ) {enckeyflag = 2;}
 if(enckeyflag == 2 && millis() - enckeytime < 400 && enckey )  {enckeyflag = 3;}  

  if(enckeyflag == 2 && millis() - enckeytime > 400 && !enckey )
    {enckeyflag = 0; Tablet.play_pause(); } 
      
  if(enckeyflag == 3 && millis() - enckeytime > 600 && millis() - enckeytime < 800 && !enckey )
    {enckeyflag = 0; Tablet.next();}
  
  if(enckeyflag == 3 && millis() - enckeytime > 800 && enckey)
    { fwd(fwddel); }
  
 if(enckeyflag != 0 && millis() - enckeytime > 1000 && !enckey ) {enckeyflag = 0;}
 if(!enckey && enckeyflag == 0) {enckeytime = millis();} 

}
