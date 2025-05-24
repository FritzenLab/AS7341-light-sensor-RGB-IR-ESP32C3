#include <Adafruit_AS7341.h>
Adafruit_AS7341 as7341;


void setup() {
  Serial.begin(115200);

  // Wait for communication with the host computer serial monitor
  while (!Serial) {
    delay(1);
  }
  
  if (!as7341.begin()){
    Serial.println("Could not find AS7341");
    while (1) { delay(10); }
  }
  
  as7341.setATIME(50);
  as7341.setASTEP(499);
  as7341.setGain(AS7341_GAIN_256X);

  as7341.setLEDCurrent(4); // 4mA
  as7341.enableLED(true);
  delay(100);
}

void loop() {
  uint16_t readings[12];
  uint16_t flicker_freq = 0;

  flicker_freq = as7341.detectFlickerHz();

  if (!as7341.readAllChannels(readings)){
    Serial.println("Error reading all channels!");
    return;
  }

  Serial.print("ADC0/F1 415nm : ");
  Serial.println(readings[0]);
  Serial.print("ADC1/F2 445nm : ");
  Serial.println(readings[1]);
  Serial.print("ADC2/F3 480nm : ");
  Serial.println(readings[2]);
  Serial.print("ADC3/F4 515nm : ");
  Serial.println(readings[3]);
  Serial.print("ADC0/F5 555nm : ");

  /* 
  // we skip the first set of duplicate clear/NIR readings
  Serial.print("ADC4/Clear-");
  Serial.println(readings[4]);
  Serial.print("ADC5/NIR-");
  Serial.println(readings[5]);
  */
  
  Serial.println(readings[6]);
  Serial.print("ADC1/F6 590nm : ");
  Serial.println(readings[7]);
  Serial.print("ADC2/F7 630nm : ");
  Serial.println(readings[8]);
  Serial.print("ADC3/F8 680nm : ");
  Serial.println(readings[9]);
  Serial.print("ADC4/Clear    : ");
  Serial.println(readings[10]);
  Serial.print("ADC5/NIR      : ");
  Serial.println(readings[11]);

  if (flicker_freq == 0) {
      Serial.println("No flicker detected");
  }else if (flicker_freq == 1) {
      Serial.println("Flicker detected with unknown frequency");
  }else {
      Serial.print("Flicker detected at ");
      Serial.print(flicker_freq);
      Serial.println(" Hz");
  }

  Serial.println();
}
