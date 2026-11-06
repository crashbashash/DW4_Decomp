/* Converts a non-drop timecode into thousandths of a frame at `rate` (frames per second times
 * 1000): hours, minutes and seconds scale by rate, frames by 1000, and the half-frame flag adds
 * 500; returns the rate alongside. */
struct Timecode {
    int f0, f4;
    int hours;   /* +8 */
    int minutes; /* +12 */
    int seconds; /* +16 */
    int frames;  /* +20 */
    int f24;     /* +24; added to frames */
    short f28;
    short half;  /* +30; half-frame flag */
};

/* matching construct: permuter — `rate` unsigned and the hour/minute products in locals fix the multiply order */
void FUN_002af110(unsigned int rate, struct Timecode *tc, int *ticks, int *out_rate) {
    int hours = tc->hours * rate;
    int minutes = tc->minutes * rate;
    int frames = tc->frames + tc->f24;

    *ticks = tc->seconds * rate + tc->half * 500 + (hours * 3600 + minutes * 60 + frames * 1000);
    *out_rate = rate;
}
