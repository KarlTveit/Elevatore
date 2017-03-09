#pragma once

#include <stdio.h>
#include <stdbool.h>

void ev_floorSensorActive(int floorx);
void ev_start(int direction);
void ev_elevatorRequested(int direction, int floor);
void ev_stopbuttonPressed(int floor);
void ev_timesOut(void);
