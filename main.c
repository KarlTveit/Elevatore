#include <stdio.h>
#include "elev.h"
#include "sm.h"

int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    elev_set_motor_direction(DIRN_UP);

    while (1) {
        // Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }

        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }


while (1) {
// setter lys for nåværende etasje
  switch (elev_get_floor_sensor_signal(void)) {
    case 0:
        ev_floorSensorActive(0);
    case 1:
        ev_floorSensorActive(1);
    case 2:
        ev_floorSensorActive(2);
    case 3:
        ev_floorSensorActive(3);

      }
  if (elev_get_button_signal(BUTTON_UP1, 0)) {
    ev_elevatorRequested(2, 0);
  }
    else if (elev_get_button_signal(BUTTON_UP2, 1)) {
  ev_elevatorRequested(2, 1);
}   else if (elev_get_button_signal(BUTTON_DOWN2, 1)) {
  ev_elevatorRequested(0, 1);
}   else if (elev_get_button_signal(BUTTON_UP3, 2)) {
  ev_elevatorRequested(2, 2);
}   else if (elev_get_button_signal(BUTTON_DOWN3, 2)) {
  ev_elevatorRequested(0, 2);
}   else if (elev_get_button_signal(BUTTON_DOWN4, 3)) {
  ev_elevatorRequested(0, 3);
}   else if (elev_get_button_signal(BUTTON_COMMAND1, 0)) {
  ev_elevatorRequested(1, 0);
}   else if (elev_get_button_signal(BUTTON_COMMAND2, 1)) {
  ev_elevatorRequested(1, 1);
}   else if (elev_get_button_signal(BUTTON_COMMAND3, 2)) {
  ev_elevatorRequested(1, 2);
}   else if (elev_get_button_signal(BUTTON_COMMAND4, 3)) {
  ev_elevatorRequested(1, 3);
}

}

    return 0;
}
