#ifndef __INCLUDE_PANEL_HANDLER_H__
#define __INCLUDE_PANEL_HANDLER_H__

#include "elev.h"
#include "common.h"
#include <stdio.h>
void panel_print(struct elevator_data inputmap);
int panel_get(struct elevator_data * inputmap);
void panel_set_lights(struct elevator_data inputmap);
#endif //__INCLUDE_PANEL_HANDLER_H__
