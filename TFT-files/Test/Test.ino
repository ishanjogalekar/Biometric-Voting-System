#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>
#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"
#include<EEPROM.h>
int vote1, vote2, vote3;
String msg  ;
#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin
#define TS_MINX 125
#define TS_MINY 85
#define TS_MAXX 965
#define TS_MAXY 905
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4
#define REDBAR_MINX 80
#define GREENBAR_MINX 130
#define BLUEBAR_MINX 180
#define BAR_MINY 30
#define BAR_HEIGHT 250
#define BAR_WIDTH 30
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
#define BLACK   0x0000
int BLUE = tft.color565(50, 50, 255);
#define DARKBLUE 0x0010
#define VIOLET 0x8888
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREY   tft.color565(64, 64, 64);
#define GOLD 0xFEA0
#define BROWN 0xA145
#define SILVER 0xC618
#define LIME 0x07E0
FPS_GT511C3 fps(11, 12); // (Arduino SS_RX = pin 4, Arduino SS_TX = pin 5)
void drawHome()
{
  tft.fillScreen(WHITE);
  tft.drawRoundRect(0, 0, 319, 240, 8, WHITE);   //Page border
  tft.fillRoundRect(10, 70, 220, 50, 8, GOLD);
  tft.drawRoundRect(10, 70, 220, 50, 8, WHITE);  //Vote
  tft.fillRoundRect(10, 160, 220, 50, 8, GOLD);
  tft.drawRoundRect(10, 160, 220, 50, 8, WHITE);  //Enroll
  tft.fillRoundRect(10, 250, 220, 50, 8, GOLD);   //Result
  tft.drawRoundRect(10, 250, 220, 50, 8, WHITE);
  tft.setCursor(65, 5);
  tft.setTextSize(3);
  tft.setTextColor(CYAN);
  tft.print("Voting");
  tft.setCursor(57, 29);
  tft.print("Machine");
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.setCursor(25, 82);
  tft.print("Candidate 1");
  tft.setCursor(25, 172);
  tft.print("Candidate 2");
  tft.setCursor(25, 262);
  tft.print("Candidate 3");
}
int oldcolor, currentcolor, currentpcolour;
void setup(void) {
  tft.reset();
  tft.begin(tft.readID());
  tft.setRotation(2);
  Serial.begin(9600); 
  Serial.println();
  Serial.print("reading id...");
  delay(500);
  //Serial.println(tft.readID(), HEX);
  tft.fillScreen(BLACK);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.setCursor(50, 140);
  tft.print("Loading...");
  for (int i; i < 250; i++)
  {
    tft.fillRect(BAR_MINY - 10, BLUEBAR_MINX, i, 10, RED);
    delay(0.000000000000000000000000000000000000000000000000001);
  }
  tft.fillScreen(BLACK);
  drawHome();
  pinMode(13, OUTPUT);
  result();
}
#define MINPRESSURE 10
#define MAXPRESSURE 1000
void loop()
{
  digitalWrite(13, HIGH);
  digitalWrite(13, LOW);
  TSPoint p = ts.getPoint();
  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  //pinMode(XP, OUTPUT);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  //pinMode(YM, OUTPUT);
  if (p.z > ts.pressureThreshhold)
    {
      p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
      p.y = map(p.y, TS_MAXY, TS_MINY, 0, 240);
      //Serial.print("X:");  // I used this to get the accurate touch points for X and Y axis
      //Serial.print(p.x);
      //Serial.print("\n");
      //Serial.print("Y:");
      //Serial.print(p.y);
      
     if (p.x > 70 && p.x < 120 && p.y > 10 && p.y < 220  && p.z > MINPRESSURE && p.z < MAXPRESSURE)
      {
       Serial.println("Candidate 1");
       fps.Open();         //send serial command to initialize fps
       fps.SetLED(true);   //turn on LED so fps can see fingerprint
       screen();
       delay(3000);
       if (fps.IsPressFinger())
      {
        fps.CaptureFinger(false);
        int id = fps.Identify1_N();
        if (id < 200) 
        {
          msg = "Candidate 1";
          Serial.println(msg);
          vote1++;
          EEPROM.write(0, vote1);
          Serial.print("Verified ID:");
          Serial.println(id);
         // delay(2000);
          tft.setCursor(42, 170);
          tft.print("Thank You");
          delay(3000);
          drawHome();
        }
       else  
       {
        screen1();
      }
      }
       }
      if (p.x > 160 && p.x < 210 && p.y > 10 && p.y < 230)
      {
       Serial.println("Candidate 2");
       fps.Open();         //send serial command to initialize fps
       fps.SetLED(true);   //turn on LED so fps can see fingerprint
       screen();
       delay(3000);
       if (fps.IsPressFinger())
      {
        fps.CaptureFinger(false);
        int id = fps.Identify1_N();
        if (id <200) 
        {
          msg = "Candidate 2";
          Serial.println(msg);
          vote2++;
          EEPROM.write(1, vote2);
          Serial.print("Verified ID:");
          Serial.println(id);
         // delay(2000);
          tft.setCursor(42, 170);
          tft.print("Thank You");
          delay(3000);
          drawHome();
        }
       else
       {
        screen1();
       }
      }
      }
      if (p.x > 260 && p.x < 300 && p.y > 10 && p.y < 220)
      {
       Serial.println("Candidate 3");
       fps.Open();         //send serial command to initialize fps
       fps.SetLED(true);   //turn on LED so fps can see fingerprint
       screen();
       delay(3000);
       if (fps.IsPressFinger())
      {
        fps.CaptureFinger(false);
        int id = fps.Identify1_N();
        if (id <200) 
        {
          msg = "Candidate 3";
          Serial.println(msg);
          vote3++;
          EEPROM.write(2, vote3);
          Serial.print("Verified ID:");
          Serial.println(id);
        //  delay(2000);
          tft.setCursor(42, 170);
          tft.print("Thank You");
          delay(3000);
          drawHome();
        }
       else
       {
        screen1();
       }
      }
      }
    }
  } 
void screen()
{
  tft.fillScreen(BLACK);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.setCursor(20, 40);
  tft.print("Please Scan");
  tft.setCursor(20, 90);
  tft.print("Your Finger");
  Serial.println("Please press finger");
}
void screen1()
{
  Serial.println("Finger not found");
  tft.fillScreen(BLACK);
  tft.setCursor(20, 40);
  tft.print("Sorry You");
  tft.setCursor(20, 90);
  tft.print("Can't Vote");
  delay(3000);
  drawHome();
}
void result()
{ 
  vote1=EEPROM.read(0);
  vote2=EEPROM.read(1);
  vote3=EEPROM.read(2);
  int vote=vote1+vote2+vote3;
  Serial.println(vote1);
  Serial.println(vote2);
  Serial.println(vote3);
 if(vote)
           {
            if((vote1 > vote2 && vote1 > vote3))
            {
             Serial.print("Candidate 1 Wins");
             delay(2000);
            }
            else if(vote2 > vote1 && vote2 > vote3)
            {
             Serial.print("Candidate 2 Wins");
             delay(2000);
            }
            else if((vote3 > vote1 && vote3 > vote2))
            {
             Serial.print("Candidate 3 Wins");
             delay(2000);
            }
           else
           {
             Serial.print("Tie Up Or");
             Serial.print("No Result");
             delay(1000);
           }
          }      
           else 
           {
             Serial.print("No Voting....");
             delay(1000);
           }
  }
