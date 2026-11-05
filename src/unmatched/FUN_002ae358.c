/* 0x002ae358 — FUN_002ae358 (60 bytes). Returns the next deadline for `now` from the interval statistics: last+estimate while before it, then last+largest, and 0x7FFFFFFF once that has passed too. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct IntervalStats {
    char pad0[660];
    int last;     /* +660 */
    int estimate; /* +664 */
    int largest;  /* +668 */
};

int FUN_002ae358(struct IntervalStats *stats, int now) {
    int last = stats->last;
    int soon = last + stats->estimate;
    int late = last + stats->largest;
    int deadline;

    if (now < soon) {
        deadline = soon;
    } else if (now < late) {
        deadline = late;
    } else {
        deadline = 0x7FFFFFFF;
    }
    return deadline;
}
