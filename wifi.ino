#include <ESP8266WiFi.h>

// 30s connection timeout
#define WIFI_DELAY 500
#define WIFI_MAX_RETRIES 60 

bool wifi_connect(String ssid, String password) {
  WiFi.begin(ssid, password);
  lcd_update_progress("Connecting...");
  
  int retries = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    retries += 1;
    delay(500);

    if (retries == WIFI_MAX_RETRIES) {
      lcd_update_progress("E: WiFi Timeout");
      return false;
    }
  }

  lcd_clear_progress();
  return true;
}

void wifi_disconnect() {
  WiFi.disconnect();
}
