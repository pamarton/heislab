#include "panel_handler.h"
#define PRINTOUT 1
#if PRINTOUT
struct elevator_data is_updated;
#endif


int panel_get(struct elevator_data * inputmap){
	#if OBSTRUCTION
	inputmap->obstruct = elev_get_obstruction_signal();
	#endif
	inputmap->floor = elev_get_floor_sensor_signal();
	inputmap->stop = elev_get_stop_signal();
	if(inputmap->stop){
		inputmap->state = state_stop;		
		return 1;
	}

	int pressed = 0;//IS THIS NEEDED?
	for(int floor = 0; floor < N_FLOORS; floor++){
		if(elev_get_button_signal(BUTTON_COMMAND,floor) && !inputmap->orders[BUTTON_COMMAND][floor]){
			inputmap->orders[BUTTON_COMMAND][floor] = 1;
			pressed = 1;
		}
	}
	for(int floor = 0; floor < N_FLOORS-1; floor++){
		if(elev_get_button_signal(BUTTON_CALL_DOWN,floor+1) && !inputmap->orders[BUTTON_CALL_DOWN][floor+1]){
			inputmap->orders[BUTTON_CALL_DOWN][floor+1] = 1;
			pressed = 1;
		}
		if(elev_get_button_signal(BUTTON_CALL_UP,floor) && !inputmap->orders[BUTTON_CALL_UP][floor]){
			inputmap->orders[BUTTON_CALL_UP][floor] = 1;
			pressed = 1;
		}
	}
	return pressed;
}

void panel_set_lights(struct elevator_data inputmap){
	if(inputmap.floor >= 0 && inputmap.floor < N_FLOORS){
		elev_set_floor_indicator(inputmap.floor);
	}
	elev_set_stop_lamp(inputmap.stop);
	for(int floor = 0; floor < N_FLOORS; floor++){
		elev_set_button_lamp(BUTTON_COMMAND,floor,inputmap.orders[BUTTON_COMMAND][floor]);
	}
	for(int floor = 0; floor < N_FLOORS-1; floor++){
		elev_set_button_lamp(BUTTON_CALL_DOWN,floor+1,inputmap.orders[BUTTON_CALL_DOWN][floor+1]);
		elev_set_button_lamp(BUTTON_CALL_UP,floor,inputmap.orders[BUTTON_CALL_UP][floor]);
	}
	







	#if PRINTOUT
	int updatelights = 0;
	for(int type = 0; type < N_BUTTONTYPES; type++){
		for(int floor = 0; floor < N_FLOORS; floor++){
			if(is_updated.orders[type][floor] != inputmap.orders[type][floor]){
				is_updated.orders[type][floor] = inputmap.orders[type][floor];
				updatelights = 1;
			}
		}
	}
	if(is_updated.stop != inputmap.stop){
		is_updated.stop = inputmap.stop;
		updatelights = 1;	
	}
	if(is_updated.floor != inputmap.floor){
		is_updated.floor = inputmap.floor;
		updatelights = 1;
	}
	if(updatelights){	
		panel_print(inputmap);
	}
	#endif
}


#if PRINTOUT


void panel_print(struct elevator_data inputmap){
	printf("#########################################\n");
	printf("|\tDOWN\tUP\t\tFLOOR\t|\n");
	printf("#########################################\n");
	for(int i = N_BUTTONTYPES; i >= 0; i--){
		printf("|\t%i\t%i\t|\t",inputmap.orders[BUTTON_CALL_DOWN][i],inputmap.orders[BUTTON_CALL_UP][i]);
		if(inputmap.floor >= 0 && inputmap.floor < N_FLOORS){
			printf("%i\t|\n",(inputmap.floor + 1));
		}else{
			printf("\t|\n");		
		}
	}
	printf("#########################################\n");
	printf("COMMAND\t%i\t%i\t%i\t%i\n",inputmap.orders[BUTTON_COMMAND][0],inputmap.orders[BUTTON_COMMAND][1],inputmap.orders[BUTTON_COMMAND][2],inputmap.orders[BUTTON_COMMAND][3]);
	printf("STOP:\t%i\t\n",inputmap.stop);
}
#endif

