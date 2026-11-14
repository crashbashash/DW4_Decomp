long long igPsx2LongTimer_GetCurrentTime(void) {
    long long rawTime;

    p2ReadNanoseconds(&rawTime);
    return rawTime;
}

int igPsx2LongTimer_GetResolution(void) {
    return 0x6C;
}

void igPsx2LongTimer_InitTimer(void) {
    g_igPsx2LongTimer_initialized = 1;
    p2InitTimer();
}

void igPsx2LongTimer_StaticInit(void) {
    igPsx2LongTimer_InitTimer();
}

