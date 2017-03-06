
#pragma once
#include <stdio.h>

void qu_setQueue(int dir, int floor);
int qu_readQueue(int dir, int curr_floor);
void qu_update(int dir, int floor);
void qu_deleteQueue();
