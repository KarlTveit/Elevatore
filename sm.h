#pragma once

#include <stdio.h>
#include <stdbool.h>

void ev_floorSensorActive(int floor);
void ev_start(void);
void ev_elevatorRequested(int dir, int floor);
void ev_stopbuttonPressed();
