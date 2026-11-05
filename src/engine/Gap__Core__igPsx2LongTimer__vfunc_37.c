/* 0x0032dab0 — Gap::Core::igPsx2LongTimer::vfunc_37.
 * Samples the raw 64-bit clock value (the "raw" the timer group subtracts
 * `_startTime` from; finding 772).  FUN_0020d290 writes it through a pointer:
 * it reads the EE timer count register at 0x10000800, scales it by a float
 * factor, adds a 64-bit base and multiplies by 100. */
int FUN_0020d290();

long long Gap__Core__igPsx2LongTimer__vfunc_37(void) {
    long long rawTime;

    FUN_0020d290(&rawTime);
    return rawTime;
}
