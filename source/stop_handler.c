#include "stop_handler.h"

void stop_emergency_stop(struct elevator_data * inputmap){
	if(inputmap->stop){
		elev_set_motor_direction(DIRN_STOP);//stop elevator
		for(int type = 0; type < N_BUTTONTYPES; type++){
			for(int floor = 0; floor < N_FLOORS; floor++){
				inputmap->orders[type][floor] = 0;//remove orders
			}	
		}
		panel_set_lights(*inputmap);//turn off the orders
		while(inputmap->stop){//wait while stop is held
			inputmap->stop = elev_get_stop_signal();
		}
		panel_set_lights(*inputmap);//turn off the stoplight
		if (inputmap->floor >= 0 && inputmap->floor < N_FLOORS){//if in a floor, open the door
			door_open();
			inputmap->state = state_door;
		}else{
/*			inputmap->dir *= -1;//go to previous floor*/
/*			while(floor_get_update() < 0){*/
/*				elev_set_motor_direction(inputmap->dir);*/
/*				inputmap->stop = elev_get_stop_signal();*/
/*				panel_set_lights(*inputmap);//turn off the orders	*/
/*				while(inputmap->stop){//wait while stop is held*/
/*					inputmap->stop = elev_get_stop_signal();*/
/*					elev_set_motor_direction(DIRN_STOP);//stop elevator*/
/*				}*/
/*				panel_set_lights(*inputmap);//turn off the orders*/
/*			}*/
/*			elev_set_motor_direction(DIRN_STOP);//stop elevator*/
/*			door_open();*/
			inputmap->stop_done = 1;
			inputmap->state = state_wait;
		}
	}
}
