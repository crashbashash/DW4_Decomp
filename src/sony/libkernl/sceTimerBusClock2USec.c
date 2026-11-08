void sceTimerBusClock2USec(unsigned long clk, unsigned int *sec, unsigned int *usec) {
    unsigned int s;
    s = clk / 147456000;
    if (sec) *sec = s;
    if (usec) *usec = (clk - (unsigned long)s * 147456000) * 1000000 / 147456000;
}
