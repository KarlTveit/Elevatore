#include "sm.h"
#include "elev.h"




void ev_start(void){

    if (elev_get_floor_sensor_signal() == -1) {
        elev_set_motor_direction(-1);

        if (elev_get_floor_sensor_signal() != -1) {
            elev_set_motor_direction(0);
        }
    }
    else    elev_set_motor_direction(0);
}

int ev_floorSensorActive(int floor){

  elev_set_floor_indicator(floor);

    return true;

  }

int ev_elevatorRequested(int dir, int floor){

  if (elev_get_button_signal(BUTTON_UP1, 0)) {
    elev_set_button_lamp(BUTTON_UP1, 0, 1);
  }   else if (elev_get_button_signal(BUTTON_UP2, 1)) {
    elev_set_button_lamp(BUTTON_UP2, 1, 1);
  }   else if (elev_get_button_signal(BUTTON_DOWN2, 1)) {
    elev_set_button_lamp(BUTTON_DOWN2, 1, 1);
  }   else if (elev_get_button_signal(BUTTON_UP3, 2)) {
    elev_set_button_lamp(BUTTON_UP3, 2, 1);
  }   else if (elev_get_button_signal(BUTTON_DOWN3, 2)) {
    elev_set_button_lamp(BUTTON_DOWN3, 2, 1);
  }   else if (elev_get_button_signal(BUTTON_DOWN4, 3)) {
    elev_set_button_lamp(BUTTON_DOWN4, 2, 1);
  }   else if (elev_get_button_signal(BUTTON_COMMAND1, 0)) {
    elev_set_button_lamp(BUTTON_COMMAND1, 0, 1);
  }   else if (elev_get_button_signal(BUTTON_COMMAND2, 1)) {
    elev_set_button_lamp(BUTTON_COMMAND2, 1, 1);
  }   else if (elev_get_button_signal(BUTTON_COMMAND3, 2)) {
    elev_set_button_lamp(BUTTON_COMMAND3, 2, 1);
  }   else if (elev_get_button_signal(BUTTON_COMMAND4, 3)) {
    elev_set_button_lamp(BUTTON_COMMAND4, 3, 1);
  }
qu_setQueue(dir, floor);


}
