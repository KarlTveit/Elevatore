//
//  sm.c
//  tetsteHeis
//
//  Created by Aleksander Asp on 22.02.17.
//  Copyright © 2017 Aleksander Asp. All rights reserved.
//



#include "sm.h"
#include "qu.h"
#include "timer.h"
#include "elev.h"


int target_floor = 0;
int curr_floor = 0;
int dir = 0;

void ev_start(void){
printf("are u serious?");
    while (elev_get_floor_sensor_signal() == -1) {
        elev_set_motor_direction(1);
    }
    elev_set_motor_direction(0);
    timer_start(3);


}

void ev_floorSensorActive(int floor){

    curr_floor = floor;
    elev_set_floor_indicator(floor);
    target_floor = qu_readQueue(dir, curr_floor);
    //dir=target_floor[1];
    while (target_floor!= -1) {
      if (elev_get_floor_sensor_signal() != -1) {
        curr_floor = elev_get_floor_sensor_signal();
      }

    if (target_floor < curr_floor){
      dir = -1;
      elev_set_motor_direction(-1);
    }

    else if (target_floor > curr_floor) {
      dir = 1;
      elev_set_motor_direction(1);
    }
    else if (target_floor == curr_floor) {

      elev_set_motor_direction(0);

      if ((dir == 1)&&(curr_floor !=3)) {
        elev_set_button_lamp(BUTTON_CALL_UP, curr_floor, 0);
        elev_set_button_lamp(BUTTON_COMMAND, curr_floor, 0);
      }    if (curr_floor == 3) {
            elev_set_button_lamp(BUTTON_CALL_DOWN, curr_floor, 0);
          }


      if ((dir == -1)&&(curr_floor != 0)) {
        elev_set_button_lamp(BUTTON_CALL_DOWN, curr_floor, 0);
        elev_set_button_lamp(BUTTON_COMMAND, curr_floor, 0);
      }
          if (curr_floor == 0) {
            elev_set_button_lamp(BUTTON_CALL_UP, curr_floor, 0);
          }


      timer_start(3);
      while (timer_isTimeOut() != true){
      elev_set_door_open_lamp(1);
      }
      timer_stop();
      elev_set_door_open_lamp(0);
      qu_update(dir, curr_floor);

        break;
    }
  }
}


void ev_elevatorRequested(int direction, int floor){

    qu_setQueue(direction, floor);

    if (direction==0) {
      elev_set_button_lamp(BUTTON_CALL_UP,floor,1);
    }
    if (direction==1) {
      elev_set_button_lamp(BUTTON_COMMAND,floor,1);
    }
    if (direction==2) {
      elev_set_button_lamp(BUTTON_CALL_DOWN,floor,1);
    }
}

void ev_stopbuttonPressed(){
printf("når vi fram hit?\n");
  qu_deleteQueue();
  elev_set_motor_direction(DIRN_STOP);
  if (elev_get_floor_sensor_signal !=-1) {
    timer_start(3);
    while (!&timer_isTimeOut) {
        elev_set_door_open_lamp(1);
    }
  }


}
