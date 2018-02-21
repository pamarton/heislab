#include "floor_handler.h"
int floor_get_update(void){
	int current_possition = elev_get_floor_sensor_signal();
	if(current_possition >= 0 && current_possition < N_FLOORS){
		elev_set_floor_indicator(current_possition);
	}
	return current_possition;
}

