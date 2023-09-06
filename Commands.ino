
void keypress(uint8_t key){
  Keyboard.write(key);
  Keyboard.releaseAll();
}
volatile void volup(uint8_t del){
  if( millis() - commdelayV > del){
     if(DispPage == 5){avg++;} else 
    {Tablet.vol_up();Tablet.clear(); } 
    commdelayV = millis();
}}
volatile void voldn(uint8_t del){
  if( millis() - commdelayV > del){
    if(DispPage == 5){avg--;} else
  {Tablet.vol_down();Tablet.clear(); }
  commdelayV = millis();
}}
void fwd(uint8_t del){
  if( millis() - commdelay > del){
  Tablet.forward(); Tablet.clear(); commdelay = millis();} 
}
void rew(uint8_t del){
  if( millis() - commdelay > del){
  Tablet.rewind(); Tablet.clear();  commdelay = millis();}
}
void next(){
  Tablet.next();  Tablet.clear();
}
void prew(){
  Tablet.previous(); Tablet.clear();
}
