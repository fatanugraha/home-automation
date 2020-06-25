#include <ESP8266HTTPClient.h>

// Asia/Jakarta UTC+7000
#define TIMEZONE_OFFSET_SECS 25200

unsigned long _prev_millis = 0;
unsigned long _unix_timestamp_ms = 0;
byte _time_part[3] = {0, 0, 0};

byte* time_tick() {
  // returns null when whether we should re-sync the time due to millis() overflow
  
  unsigned long now = millis();
  if (now < _prev_millis) {
    return NULL;
  }

  _unix_timestamp_ms += now - _prev_millis;
  if (_unix_timestamp_ms > 86400000) {
    _unix_timestamp_ms -= 86400000;
  }

  unsigned long timestamp = _unix_timestamp_ms / 1000 + TIMEZONE_OFFSET_SECS;
  
  _time_part[0] = timestamp / 3600;
  _time_part[1] = (timestamp / 60) % 60;
  _time_part[2] = timestamp % 60;

  _prev_millis = now;
  return _time_part;
}

bool time_sync() { 
  if (!wifi_connect(ssid, password)) {
    return false;
  }

  lcd_update_progress("Syncing time...");
  HTTPClient http;  
  http.begin("http://worldtimeapi.org/api/timezone/Asia/Jakarta.txt");
  int status_code = http.GET();

  if (status_code != 200) {
    lcd_update_progress("E: Unreachable");
    return false;
  }
  
  String payload = http.getString();
  _prev_millis = millis();
  // unixtime: 1588435785
  int idx = payload.indexOf("unixtime: ") + 10;
  // only take hours part
  _unix_timestamp_ms = payload.substring(idx, idx+10).toInt() % 86400;
  _unix_timestamp_ms *= 1000;

  lcd_clear_progress();
  wifi_disconnect();
}
