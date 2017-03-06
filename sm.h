#pragma once

#include <stdio.h>

#define sm_h

#include <stdio.h>
#include "elev.h"

void ev_floorSensorActive(int floor);
void ev_start(void);
void ev_elevatorRequested(int dir, int floor);
void ev_stopbuttonPressed();
