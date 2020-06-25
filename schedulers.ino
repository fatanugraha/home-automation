typedef void (*func_t)(); 

#define NUM_SCHEDULES 2

const byte SCHEDULE_TIME[NUM_SCHEDULES][3] = {{5, 30, 0}, {17, 30, 0}};
func_t SCHEDULE_ACTIONS[NUM_SCHEDULES] = {light_bulb_on, light_bulb_off};

void scheduler_tick(byte* time_parts) {
  for (int j = 0; j < NUM_SCHEDULES; j++) {
    bool valid = true;
  
    for (int i = 0; i < 3 && valid; i++) {
      if (time_parts[i] != SCHEDULE_TIME[j][i]) {
        valid = false;      
      }
    }

    if (valid) {
      SCHEDULE_ACTIONS[j]();
    }
  }
}
