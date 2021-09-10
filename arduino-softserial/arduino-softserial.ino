#include <SoftwareSerial.h>

SoftwareSerial espSerial(10,11); // RX, TX

void setup() {
  // put your setup code here, to run once:
  espSerial.begin(9600)
}

void loop() {
  // put your main code here, to run repeatedly:

}
