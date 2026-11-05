/* 0x0027df80 — FUN_0027df80 (248 bytes). Creates an IOP-side SJX: takes a free slot of the 32-entry table, asks the IOP for a handle with request 0 through FUN_00273820, and reports "can't create SJX of IOP" on failure. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void *memset(void *, int, unsigned int);
int FUN_00273820();
int FUN_002659a0();

/* One 20-byte SJX slot. */
struct Sjx0027df80 {
    char used;      /* +0 */
    char pad1[3];
    int arg0;       /* +4 */
    int arg1;       /* +8 */
    int arg2;       /* +12 */
    int iopHandle;  /* +16: returned by the IOP, 0 on failure */
};

extern struct Sjx0027df80 DAT_004ba498[32];
extern char DAT_004f2520[]; /* "E0100401: can't create SJX of IOP\n" */

struct Sjx0027df80 *FUN_0027df80(int arg0, int arg1, int arg2) {
    int request[4];
    struct Sjx0027df80 *sjx;
    int i;

    for (i = 0; i < 32; i++) {
        sjx = &DAT_004ba498[i];
        if (sjx->used == 0) {
            break;
        }
    }
    if (i == 32) {
        return 0;
    }
    memset(sjx, 0, sizeof(*sjx));
    sjx->arg0 = arg0;
    sjx->arg2 = arg2;
    sjx->arg1 = arg1;
    request[0] = arg0;
    request[1] = arg1;
    request[2] = arg2;
    request[3] = (int)sjx;
    sjx->iopHandle = FUN_00273820(0, request, 4, request, 1);
    if (sjx->iopHandle == 0) {
        FUN_002659a0(DAT_004f2520);
        return 0;
    }
    sjx->used = 1;
    return sjx;
}
