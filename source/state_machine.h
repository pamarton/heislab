#ifndef __INCLUDE_STATE_MACHINE_H__
#define __INCLUDE_STATE_MACHINE_H__

#include "elev.h"
#include <stdio.h>
#include "panel_handler.h"
#include "stop_handler.h"
#include "floor_handler.h"
#define N_STATES "SKRIVNOEHER"

void new_state(void);
void func_state_init(void);
int func_check_floor(int floor);
void func_clear_current_floor(void);
void func_state_door(void);
void func_state_wait(void);
void func_state_drive(void);

int func_order_in_front(void);
int func_check_floor_directional(int floor);
#endif //__INCLUDE_STATE_MACHINE_H__
