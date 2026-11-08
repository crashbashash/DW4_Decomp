unsigned long sceTimerUSec2BusClock(unsigned int sec, unsigned int usec) {
    return (unsigned long)sec * 147456000 + (unsigned long)usec * 147456000 / 1000000;
}
