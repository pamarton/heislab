#include "door_handler.h"

int timer_get_timestamp(int wait_time){
	return time(NULL) + wait_time;
}

int timer_compare(int timestamp){
	if(timestamp <= time(NULL)){
		return 1;	
	}
	return 0;
}

int door_status = 0;

void door_open(void){
	door_status = timer_get_timestamp(WAIT_TIME);
	elev_set_door_open_lamp(1);
}

int door_close(void){
	//IF OBSTRUCTION RETURN 0 AND door_open() :)
	if(timer_compare(door_status)){		
		elev_set_door_open_lamp(0);
		return 1;
	}
	return 0;
}
