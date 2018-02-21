#ifndef __INCLUDE_DOOR_HANDLER_H__
#define __INCLUDE_DOOR_HANDLER_H__

#include <time.h>
#include <stdio.h>
#include "common.h"
#include "elev.h"
#define WAIT_TIME 3//CHANGE THIS TO 3!!!!!!!!!!!!!!!!!!

int 	timer_get_timestamp(int wait_time);
int 	timer_compare(int timestamp);
void 	door_open(void);
int 	door_close(void);

#endif //__INCLUDE_DOOR_HANDLER_H__
