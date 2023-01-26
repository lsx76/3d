#ifndef __TRACK_TASK_H__
#define __TRACK_TASK_H__

#include "pid.h"
#include "bar.h"


extern float row_weight[9];
extern float vertical_weight[9];

void set_track_status(TRACKINGBOARD_t *trackboard,bool status);
void track_pid_data_init(pid_data_t *track_pid_data);
int track_pid(TRACKINGBOARD_t *trackboard,float weight[]);
int calculate_diviation(TRACKINGBOARD_t *trackboard,float weight[]);

#endif

