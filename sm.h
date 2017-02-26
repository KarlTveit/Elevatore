
#define sm_h

#include <stdio.h>
#include "elev.h"

int ev_floorSensorActive(int floor);
void ev_start(void);
int ev_elevatorRequested(int dir, int floor);
