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

    if (elev_get_floor_sensor_signal() == -1) {
        elev_set_motor_direction(-1);

        if (elev_get_floor_sensor_signal() != -1) {
            elev_set_motor_direction(0);
        }
    }
    else    elev_set_motor_direction(0);
}

void ev_floorSensorActive(int floor){

    curr_floor = floor;
    elev_set_floor_indicator(floor);
    target_floor = qu_readQueue(dir, curr_floor);
    while (target_floor!= -1) {
    if (target_floor < curr_floor){
      dir = -1;
      elev_set_motor_direction(-1);
    }

    if (target_floor > curr_floor) {
      dir = 1;
      elev_set_motor_direction(1);
    }

    if (target_floor== curr_floor){

        if (dir == 1) {
          elev_set_button_lamp(BUTTON_CALL_UP, curr_floor, 0);
          elev_set_button_lamp(BUTTON_COMMAND, curr_floor, 0);
            if (curr_floor == 3) {
              elev_set_button_lamp(BUTTON_CALL_DOWN, curr_floor, 0);
            }
        }

        if (dir == -1) {
          elev_set_button_lamp(BUTTON_CALL_DOWN, curr_floor, 0);
          elev_set_button_lamp(BUTTON_COMMAND, curr_floor, 0);
            if (curr_floor == 0) {
              elev_set_button_lamp(BUTTON_CALL_UP, curr_floor, 0);
            }
        }

      elev_set_motor_direction(0);
      timer_start(3);
      while (!&timer_isTimeOut){
      elev_set_door_open_lamp(1);
      }
      timer_stop();
      elev_set_door_open_lamp(0);
      qu_update(dir, curr_floor);
    }
  }
}

void ev_elevatorRequested(int dir, int floor){

    qu_setQueue(dir, floor);

    if (elev_get_button_signal(BUTTON_CALL_UP, 0)) {
        elev_set_button_lamp(BUTTON_CALL_UP, 0, 1);
    }   else if (elev_get_button_signal(BUTTON_CALL_UP, 1)) {
        elev_set_button_lamp(BUTTON_CALL_UP, 1, 1);
    }   else if (elev_get_button_signal(BUTTON_CALL_DOWN, 1)) {
        elev_set_button_lamp(BUTTON_CALL_DOWN, 1, 1);
    }   else if (elev_get_button_signal(BUTTON_CALL_UP, 2)) {
        elev_set_button_lamp(BUTTON_CALL_UP, 2, 1);
    }   else if (elev_get_button_signal(BUTTON_CALL_DOWN, 2)) {
        elev_set_button_lamp(BUTTON_CALL_DOWN, 2, 1);
    }   else if (elev_get_button_signal(BUTTON_CALL_DOWN, 3)) {
        elev_set_button_lamp(BUTTON_CALL_DOWN, 2, 1);
    }   else if (elev_get_button_signal(BUTTON_COMMAND, 0)) {
        elev_set_button_lamp(BUTTON_COMMAND, 0, 1);
    }   else if (elev_get_button_signal(BUTTON_COMMAND, 1)) {
        elev_set_button_lamp(BUTTON_COMMAND, 1, 1);
    }   else if (elev_get_button_signal(BUTTON_COMMAND, 2)) {
        elev_set_button_lamp(BUTTON_COMMAND, 2, 1);
    }   else if (elev_get_button_signal(BUTTON_COMMAND, 3)) {
        elev_set_button_lamp(BUTTON_COMMAND, 3, 1);
    }

}

void ev_stopbuttonPressed(){

  qu_deleteQueue();
  elev_set_motor_direction(DIRN_STOP);
  if (elev_get_floor_sensor_signal !=-1) {
    timer_start(3);
    while (!&timer_isTimeOut) {
        elev_set_door_open_lamp(1);
    }
  }


}
