#include "state_machine.h"
struct elevator_data my_elev;


void new_state(){
	switch(my_elev.state){
		case state_init:
			//printf("init ");
			func_state_init();
			break;
		case state_stop:
			//printf("stop ");
			stop_emergency_stop(&my_elev);
			break;
		case state_wait:
			printf("wait ");
			func_state_wait();
			break;
		case state_drive:
			printf("drive ");
			func_state_drive();
			break;
		case state_door:
			//printf("door ");
			func_state_door();
			break;
	}
	panel_get(&my_elev);
	panel_set_lights(my_elev);
}


void func_state_wait(void){
	if(func_check_floor(my_elev.floor)){//if there are orders in this floor, open door
		my_elev.state = state_door; 		
	}	
	else if(func_check_floor(0) | func_check_floor(1) | func_check_floor(2) | func_check_floor(3)){
		my_elev.state = state_drive;	
	}
}

void func_state_drive(void){
	if(my_elev.stop_done == 0 && my_elev.floor != my_elev.last_floor && my_elev.floor != -1){
		my_elev.last_floor = my_elev.floor;
		if(func_check_floor_directional(my_elev.floor)){
			elev_set_motor_direction(DIRN_STOP);
			my_elev.state = state_wait;
		}
	}else{
/*		if(my_elev.stop_done){*/
/*			my_elev.floor = my_elev.last_floor;*/
/*			my_elev.stop_done = 0;		*/
/*		}	*/
		if(!func_order_in_front()){//if no order in the direction we are traveling
			my_elev.dir *= -1;
			printf("turn!%i\n",my_elev.dir);
		}
		elev_set_motor_direction(my_elev.dir);
		my_elev.temp_floor = (float)my_elev.floor + ((float)my_elev.dir)/2;
		printf("FLOAT%f",my_elev.temp_floor);
	}
}


void func_state_init(void){
	my_elev.stop = 0;
	#if OBSTRUCTION
	my_elev.obstruct = 0;
	#endif
	my_elev.floor = 1;
	my_elev.last_floor = -1;
	my_elev.stop_done = 1;
	my_elev.dir = 1;
	for(int type = 0; type < N_BUTTONTYPES; type++){//remove orders
		for(int floor = 0; floor < N_FLOORS; floor++){
			my_elev.orders[type][floor] = 0;
		}	
	}
	elev_set_motor_direction(DIRN_DOWN);
	while(elev_get_floor_sensor_signal() < 0);
	elev_set_motor_direction(DIRN_STOP);
	my_elev.state = state_wait;
}

void func_state_door(void){
	#if OBSTRUCTION
	if(my_elev.obstruct){
		door_open();
	}
	#endif
	if(my_elev.floor < N_FLOORS && my_elev.floor >= 0){
		if(func_check_floor(my_elev.floor)){
			door_open();
			func_clear_current_floor();//clear orders of the current floor
		}else if(door_close()){
			my_elev.state = state_wait;
		}	
	}
}

int func_check_floor_directional(int floor){//syntax to determine if the elevator should stop in the current floor
	if(my_elev.orders[BUTTON_COMMAND][floor]){
		return 1;
	}	
	if(my_elev.orders[BUTTON_CALL_UP][floor] && my_elev.dir == DIRN_UP){
		return 1;
	}
	if(my_elev.orders[BUTTON_CALL_DOWN][floor] && my_elev.dir == DIRN_DOWN){
		return 1;
	}
	if(my_elev.orders[BUTTON_CALL_UP][0] == 1 && floor == 0){
		return 1;
	}
	if(my_elev.orders[BUTTON_CALL_DOWN][N_FLOORS - 1] == 1 && floor == N_FLOORS - 1){
		return 1;
	}
	return 0;
}

int func_check_floor(int floor){
	if(floor < 0){
		return 0;
	}
	for(int type = 0; type < N_BUTTONTYPES; type++){
		if(my_elev.orders[type][floor]){
			return 1;
		}	
	}
	return 0;
}


void func_clear_current_floor(void){
	for(int type = 0; type < N_BUTTONTYPES; type++){
		my_elev.orders[type][my_elev.floor] = 0;
	}
}

int func_order_in_front(void){
	for(int check_floor = my_elev.last_floor; check_floor < N_FLOORS && check_floor >= 0; check_floor += my_elev.dir){
		//printf("\nChecking floor %i",check_floor);
		if(func_check_floor(check_floor)){
			//printf(" - YES");
			return 1;
		}
		//printf(" - NO, going to next");
	}
	//printf("NOTHING!\n");
	return 0;
}


