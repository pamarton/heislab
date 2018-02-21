#include "source/state_machine.h"
#include <stdio.h>


int main() {
    	// Initialize hardware
    	if (!elev_init()) {
        	printf("Unable to initialize elevator hardware!\n");
        	return 1;
    	}
	


    	while (1) {
		new_state();
/*        	// Change direction when we reach top/bottom floor*/
/*		//floor_get_update();*/
/*		panel_get(&test_3);*/
/*		panel_set_lights(test_3);*/
/*		stop_emergency_stop(&test_3);*/
/*	*/

/*        	if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {*/
/*			test_3.dir = DIRN_DOWN;        	    	*/
/*        	} else if (elev_get_floor_sensor_signal() == 0) {*/
/*        	    	test_3.dir = DIRN_UP;   */
/*			*/
/*        	}*/


/*		elev_set_motor_direction(test_3.dir);*/
/*        	// Stop elevator and exit program if the stop button is pressed*/
        	
    	}
    	return 0;
}


