#include <IRremote.h>
#include <Adafruit_NeoPixel.h>
int RECV_PIN = 2;
int NUMPIXELS = 18;
int PIN = 3;
int del;

int LED[18] = {255, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned long int preDelay = 0;


Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


int mode = 1;
int preMode = -1;
bool update = true;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pixels.begin();
  pixels.clear();
}

void loop() {
  if (irrecv.decode(&results)) {  // read of remote
      
      if(results.value == 0x926D12ED){
        mode = 0;
      }
      else if(results.value == 0x926D629D){
        mode = 1;
      }
      else if(results.value == 0x926D22DD){
        mode = 2;
      }
      else if(results.value == 0x926D40BF){
        mode = 3;
      }
      else if(results.value == 0x926DA25D){
        mode = 4;
      }
      irrecv.resume(); // Receive the next value
  }
  
  
  if(mode != preMode){         //mode initialisation
     Serial.print(preMode);
     Serial.println(mode);
     
     
     if(mode == 0){
        del = 100;
     }

     
     else if(mode == 1){
        del = 1000;
        for(int i = 0; i < 18; i++){
          if(i % 4 == 0){
            LED[i] = 255;
            continue;
          }
          LED[i] = 0;
        }
     }
     preMode = mode;
  }
  
  if(millis() - preDelay > del){
    update = true;
    preDelay = millis();
    if(mode == 0){
      for(int i = 0; i < 18; i++){
        LED[i] = 0;
      }
    }
    else if(mode == 1){
      for(int i = 17; i > 0; i--){
        LED[i] = LED[i - 1];
      }
      LED[0] = LED[4];
    }
  }
  
  


  if(update){                  // ledUpdata
    for(int i = 0; i < 18; i++){
      pixels.setPixelColor(i, pixels.Color(LED[i], LED[i], LED[i]));
      pixels.show();
    }
    update = false;
  }
}
