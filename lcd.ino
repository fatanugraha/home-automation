#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte clockChar[] = {0x00, 0x00, 0x0E, 0x15, 0x17, 0x11, 0x0E, 0x00};
byte bulbChar[] = {0x0E, 0x11, 0x11, 0x11, 0x0A, 0x0E, 0x0A, 0x04};

void lcd_begin() { 
  lcd.begin();
  lcd.noBacklight();
  lcd.createChar(1, clockChar);
  lcd.createChar(2, bulbChar);
}

void lcd_update_time(byte hour, byte minute) {
  lcd.setCursor(0, 1);
  lcd.write(1);
  
  if (hour < 10) {
    lcd.print(0);
  }
  lcd.print(hour);
  lcd.print(':');
  
  if (minute < 10) {
    lcd.print(0);
  }
  lcd.print(minute);
}

void lcd_update_bulb_status(bool status) {
  lcd.setCursor(15, 1);
  if (status) {
    lcd.write(2);
  } else {
    lcd.print(' ');
  }
}

void lcd_clear_progress() {
  lcd.setCursor(0, 0);
  for (int i = 0; i < 16; i++) {
    lcd.print(' ');
  }
  lcd.setCursor(0, 0);
}
void lcd_update_progress(char* progress) {
  lcd_clear_progress();
  lcd.print(progress);
}
