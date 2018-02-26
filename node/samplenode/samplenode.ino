/**
 * Copyright © 2018 EBIO Lab. SNU. 
 * All Rights Reserved.
 *
 * \file ebionode.ino
 * \brief ebionode 의 메인
 */

#define _DEBUG_

#include <node.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);


boolean runnable = false;
EbioNode enode(&Serial);

void setup () {
  Serial.begin (115200);  // for monitoring
  lcd.init(); 
  enode.setup();
}

void monitor () {
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("MT: ");
  lcd.setCursor(4,0);
  lcd.print(enode.getdisplayvalue(0));
  lcd.setCursor(6,0);
  lcd.print("% ");
  lcd.setCursor(8,0);
  if (enode.getdisplayvalue(1) == 0)
    lcd.print("STOP ");
  else if (enode.getdisplayvalue(1) == 1)
    lcd.print("OPEN ");
  else
    lcd.print("CLOSE");
  
  lcd.setCursor(0,1);
  lcd.print("SW:");
  lcd.setCursor(4,1);
  if (enode.getdisplayvalue(2) == 0)
    lcd.print("OFF");
  else
    lcd.print("ON ");
  lcd.setCursor(7,1);
  lcd.print(" SE: ");
  lcd.setCursor(11,1);
  lcd.print(enode.getdisplayvalue(3) / 10.0);
}

void loop () {
  enode.process ();
  monitor();
  delay (1000);
}
