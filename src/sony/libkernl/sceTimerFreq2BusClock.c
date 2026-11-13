#define BUS_CLOCK 147456000.0f

unsigned long sceTimerFreq2BusClock(float freq) {
    return BUS_CLOCK / freq;
}
