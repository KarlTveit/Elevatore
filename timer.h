#pragma once
#include <stdbool.h>

void timer_start(double duration);
void timer_stop(void);
bool timer_isTimeOut(void);
