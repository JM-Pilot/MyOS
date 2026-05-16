#ifndef PIT_H
#define PIT_H

void timer_phase(int hz);
int pit_get_ticks();
void pit_install();

#endif