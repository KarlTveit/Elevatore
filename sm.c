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
int timerActive = 0;
int stopPressed = 0;

void ev_start(int direction){

    elev_set_motor_direction(direction);

}

void ev_floorSensorActive(int floorx){

    curr_floor = floorx;

    elev_set_floor_indicator(floorx);
    target_floor = qu_readQueue(dir, curr_floor);

if (target_floor != -1){

    if (target_floor < curr_floor){
      dir = -1;
      elev_set_motor_direction(-1);

    }

     if (target_floor > curr_floor) {
      dir = 1;
      elev_set_motor_direction(1);

    }
    else if (target_floor == curr_floor) {

      elev_set_motor_direction(0);

        if ((curr_floor == 2)||(curr_floor == 1)) {
          elev_set_button_lamp(BUTTON_CALL_UP, curr_floor, 0);
          elev_set_button_lamp(BUTTON_COMMAND, curr_floor, 0);
          elev_set_button_lamp(BUTTON_CALL_DOWN, curr_floor, 0);
        }
        else if (curr_floor == 3){
          elev_set_button_lamp(BUTTON_COMMAND, curr_floor, 0);
          elev_set_button_lamp(BUTTON_CALL_DOWN, curr_floor, 0);
        }
        else if (curr_floor == 0){
          elev_set_button_lamp(BUTTON_COMMAND, curr_floor, 0);
          elev_set_button_lamp(BUTTON_CALL_UP, curr_floor, 0);
        }

      if (timerActive != 1) {

      timer_start(3);
      elev_set_door_open_lamp(1);
      timerActive = 1;
    }
    }
  }
}

void ev_timesOut(){

  timer_stop();
  elev_set_door_open_lamp(0);
  qu_update(curr_floor);
  timerActive = 0;


}


void ev_elevatorRequested(int direction, int floor){

    qu_setQueue(direction, floor);

    if (stopPressed == 1) {

       if ((floor<curr_floor)||((floor == curr_floor)&&(dir == 1))){
         elev_set_motor_direction(-1);
         stopPressed = 0;
       }

      else
        elev_set_motor_direction(1);
        stopPressed = 0;
  }

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

void ev_stopbuttonPressed(int floor){

  qu_deleteQueue();
  elev_set_button_lamp(BUTTON_CALL_UP, 0, 0);
  elev_set_button_lamp(BUTTON_CALL_UP, 1, 0);
  elev_set_button_lamp(BUTTON_CALL_UP, 2, 0);
  elev_set_button_lamp(BUTTON_COMMAND, 0, 0);
  elev_set_button_lamp(BUTTON_COMMAND, 1, 0);
  elev_set_button_lamp(BUTTON_COMMAND, 2, 0);
  elev_set_button_lamp(BUTTON_COMMAND, 3, 0);
  elev_set_button_lamp(BUTTON_CALL_DOWN,1, 0);
  elev_set_button_lamp(BUTTON_CALL_DOWN,2, 0);
  elev_set_button_lamp(BUTTON_CALL_DOWN,3, 0);
  elev_set_motor_direction(DIRN_STOP);

  stopPressed = 1;

  if (floor !=-1) {

    if (timerActive != 1) {

    timer_start(3);
    elev_set_door_open_lamp(1);
    timerActive = 1;

  }
  }


}
