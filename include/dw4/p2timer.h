/* p2timer.h - the p2 renderer's clock, alarms and wait-time statistics.
 *
 * Timer 1 counts at BUSCLK/16 (9.216 MHz); its overflow interrupt extends the 16-bit count to 64
 * bits, which is the renderer's clock. Timer 0 counts at BUSCLK/256 (576 ticks a millisecond) and
 * drives the alarms: a thread that sleeps takes an alarm, which holds its semaphore and a delay in
 * milliseconds relative to the alarm before it, and the timer 0 compare interrupt signals each alarm
 * as its delay runs out. The waiting code of the renderer adds the clock time it spends blocked to
 * the counters below, which the statistics block reports. */
#ifndef DW4_P2TIMER_H
#define DW4_P2TIMER_H

void p2InitTimer(void);
void p2ShutdownTimer(void);
void p2ReadClock(long long *time);
void p2ReadNanoseconds(long long *time);
void p2Sleep(int seconds);
void p2SleepMilliseconds(int milliseconds);

extern int p2DmaWaitTime;
extern int p2SwapWaitTime;
extern int p2FinishWaitTime;
extern int p2SleepTime;
extern int p2Vu0LockWaitTime;

#endif
