#include <IRremote.h>
int RECV_PIN = 2;

unsigned int mode = 0;
unsigned int preMode = 0;
bool update = true;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
      
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
      if(mode != preMode){
        update = true;
        preMode = mode;
      }
      irrecv.resume(); // Receive the next value
  }


  if(update){
    Serial.println(mode);
    update = false;
  }
}
