#ifndef __TIMER_H
#define __TIMER_H		

#include "cw32l010.h"
#include "cw32l010_sysctrl.h"
#include "cw32l010_btim.h"
#include "system_cw32l010.h"

void Timer2_Init(void);
void Timer2_Enable(FunctionalState NewState);

#endif

