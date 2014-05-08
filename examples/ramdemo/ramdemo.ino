#include <SPI.h>
#include <Wire.h>
#include <Time.h>
#include <mcp7940.h>

void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Startup...");
  
  // Simple test
  // Clear 16bytes of RTC memory
  // Write a pattern
  // print the results
  Serial.println("Clear first 16bytes of RTC static ram, read back, write pattern/read back");
  writeRTCmem(0,16,0);
  printRTCmem(0,16);  
  writeRTCmem(0,16,-1);
  printRTCmem(0,16);  
}

void loop() {
  // put your main code here, to run repeatedly: 
  
}

// TODO: check RTC RD/WR timing and handling per specification and do more rigorous testing
void writeRTCmem(int addr, int len, int pattern) {
  uint8_t a = addr + 020;  // 
  Wire.beginTransmission(MCP7940_CTRL_ID);
  Wire.write(a);
  delay(1);
  byte b=0;
  if(pattern== -1) {
    for(int i=0; i<len; i++) {
      b = i;
      Wire.write(b);
      delay(1);
    }
  }else {
    b = pattern;
    for(int i=0; i<len; i++) {
      Wire.write(b);
      delay(1);
    }  
  }
  Wire.endTransmission();
}

//print len-bytes of RTCmemory beginning at relative address, addr
// TODO: check RD/WR timing and handling per specification and do more rigorous testing
void printRTCmem(int addr, int len) {
  uint8_t a = addr + 020;  // 
  Wire.beginTransmission(MCP7940_CTRL_ID);
  Wire.write(a);
  delay(1);
  Wire.endTransmission();
  delay(1);
  Wire.requestFrom(MCP7940_CTRL_ID, len);
  for(int i=0; i<len; i++) {
    while(Wire.available()) {
      byte b = Wire.read();
      if(b<0x10) Serial.print("0");
      Serial.print(b,HEX);
      Serial.print(" ");
    }
  }
  Wire.endTransmission();
  Serial.println();
}

