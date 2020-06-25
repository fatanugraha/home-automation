

int hours, minutes, seconds, normalized_time;

void setup() {
  Serial.begin(9600);
  lcd_begin();
  bulb_switch_begin(D5, D6);
}


byte* time_parts = NULL;

void loop() {  
  // update time
  if (!time_parts) {
    time_sync();
  }
  time_tick();
  
  time_parts = time_tick();
  if (!time_parts && time_sync()) {
    time_parts = time_tick();
  }
  
  if (!time_parts) {
    goto END;
  }

  lcd_update_time(time_parts[0], time_parts[1]);
  scheduler_tick(time_parts);
END:
  delay(60000); // 1m
}
