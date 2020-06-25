#include <Servo.h>

#define SERVO_NEUTRAL 70
#define SERVO_UP SERVO_NEUTRAL + 16
#define SERVO_DOWN SERVO_NEUTRAL - 24

int status = 1;

Servo servo;

unsigned long _last_fired = 0;
void ICACHE_RAM_ATTR handle_interrupt() {
  unsigned long now = millis();
  
  if (now - _last_fired > 1000) {
    light_bulb_toggle();
    _last_fired = now;
  }
}

void bulb_switch_begin(int pin, int button_pin) {
  servo.attach(pin);
  
  pinMode(button_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button_pin), handle_interrupt, RISING);

  // test drive, default is on
  light_bulb_on();
  delay(1000);
  light_bulb_off();
  delay(1000);
  light_bulb_on();
}

void light_bulb_toggle() {
  if (status) {
    light_bulb_off();
  } else {
    light_bulb_on();
  }
}

void light_bulb_on() {
  if (status) {
    return;
  }

  lcd_update_bulb_status(true);
  servo.write(SERVO_UP);
  status = true;
}

void light_bulb_off() {
  if (!status) {
    return;
  }

  lcd_update_bulb_status(false);
  servo.write(SERVO_DOWN);
  status = false;
}
