/**
 * Copyright © 2018 EBIO Lab. SNU. 
 * All Rights Reserved.
 *
 * \file ebionode.ino
 * \brief ebionode 의 메인
 */

//#define _DEBUG_

#include <node.h>
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
  lcd.print(enode.getdisplayvalue(0) / 10.0);
  lcd.setCursor(4,0);
  lcd.print("% ");
  lcd.setCursor(6,0);
  lcd.print(enode.getdisplayvalue(1) / 10.0);
  lcd.setCursor(10,0);
  lcd.print("C");
  
  lcd.setCursor(12,0);
  if (enode.getdisplayvalue(2) == 0)
    lcd.print("F");
  else
    lcd.print("T");
  lcd.setCursor(14,0);
  if (enode.getdisplayvalue(3) == 0)
    lcd.print("F");
  else
    lcd.print("T");
  
  lcd.setCursor(0,1);
  lcd.print(enode.getdisplayvalue(4));
  lcd.setCursor(2,1);
  lcd.print("% ");
  lcd.setCursor(4,1);
  if (enode.getdisplayvalue(5) == 0)
    lcd.print("S");
  else if (enode.getdisplayvalue(5) == 1)
    lcd.print("O");
  else
    lcd.print("C");
  
  lcd.setCursor(8,1);
  lcd.print(enode.getdisplayvalue(4));
  lcd.setCursor(10,1);
  lcd.print("% ");
  lcd.setCursor(12,1);
  if (enode.getdisplayvalue(5) == 0)
    lcd.print("S");
  else if (enode.getdisplayvalue(5) == 1)
    lcd.print("O");
  else
    lcd.print("C");  
}

void loop () {
  enode.process ();
  monitor();
  delay (1000);
}
