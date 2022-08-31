#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_TFTLCD.h>
#include <pin_magic.h>
#include <registers.h>
#include <Adafruit_Fingerprint.h>
#include <TouchScreen.h>
#include <Adafruit_Fingerprint.h>
#include "SoftwareSerial.h"
#include<EEPROM.h>

SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
LiquidCrystal_I2C lcd(0x27,20,4);

void setup()
{
 
  Serial.begin(9600);
  finger.begin(57600);
  lcd.init();                     
  lcd.init();
  lcd.backlight();
  while (!Serial);
  delay(100);
  Serial.println("\n\nVoting System");
  lcd.setCursor(2,0);
  lcd.print("Voting System");
  lcd.setCursor(2,1);
  lcd.print("TARP Project");
  delay(5000);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Made by");
  lcd.setCursor(1,1);
  lcd.print("Sid,Ishan,Rishi");
  delay(5000);
  lcd.clear();
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Finger print found");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }
  finger.getTemplateCount();
    if (finger.templateCount == 0) {
    Serial.print("No candidates registered");
  } 
  else {
    Serial.println("Waiting for valid fingerprints for candiadtes...");
    Serial.print("Voting Machines contains"); 
    Serial.print(finger.templateCount); 
    Serial.println("\ncandidate's data");
    lcd.setCursor(0,0);
    lcd.print("No.of Candidates\n");
    lcd.setCursor(2,1);
    lcd.print(finger.templateCount);
    lcd.setCursor(4,1);
    lcd.print("\nregistered");
    delay(5000);
    lcd.clear();   
  }
}
void loop()                     
{
  getFingerprintIDez();
  delay(50);            
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  Serial.print("Candidtes"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); 
  //Serial.println(finger.confidence); 

  return finger.fingerID;
}
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  
  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  
  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  
  return -1;

  /*if(voted[finger.fingerID] != 0)
  return -1;*/
  
  boolean flag = 0;
  if(flag == 0){
    Serial.print("Candidate\n\n"); Serial.print(finger.fingerID); 
    Serial.print("\n\n vote recorded"); 
    lcd.setCursor(0,0);
    lcd.print("Candidate - ");
    lcd.setCursor(13,0);
    lcd.print(finger.fingerID);
    Serial.println(finger.fingerID);
    lcd.setCursor(0,1);
    lcd.print("vote recorded");
    delay(3000);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Thank you for");
    lcd.setCursor(2,1);
    lcd.print("Voting");
    delay(1000);
    lcd.clear();
    flag = 1;
    //voted[finger.fingerID] = 1;
    return finger.fingerID;
  }
}
