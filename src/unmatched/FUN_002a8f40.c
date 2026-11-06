/* Under the record's semaphore, adds a byte count to its 32-bit (+20) and 64-bit (+72) totals. */
typedef struct SfdCounter {
    char pad0[20];
    int total32;            /* +20 */
    char pad24[40];
    int sema;               /* +64 */
    int pad68;
    long total64;           /* +72 */
} SfdCounter;

extern int WaitSema(int sema);
extern int SignalSema(int sema);

void FUN_002a8f40(SfdCounter *counter, int bytes) {
    WaitSema(counter->sema);
    counter->total32 += bytes;
    counter->total64 += bytes;
    SignalSema(counter->sema);
}
