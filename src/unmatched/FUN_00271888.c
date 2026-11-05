/* 0x00271888 — FUN_00271888 (176 bytes). Queues a request on an idle SRD object (state 0, 3 or 9) inside the FUN_0027e1f0/FUN_0027e268 lock: stores the request (+48) and its parameters (+24, +32, +40), sets +1 to 2 and the state to 1 (busy) and clears +4. Returns 1 when queued, 0 when the object was busy. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Srd_271888 {
    signed char used;       /* 0x00 */
    signed char kind;       /* 0x01 */
    signed char state;      /* 0x02 */
    char pad3;
    int status;             /* 0x04 */
    char pad8[16];
    int f24;                 /* 0x18 */
    int pad28;
    long f32;                /* 0x20 */
    long f40;                /* 0x28 */
    int request;            /* 0x30 */
} Srd_271888;

void FUN_0027e1f0(void);
void FUN_0027e268(void);

int FUN_00271888(Srd_271888 *srd, int request, long value40, long value32, int value24) {
    int queued = 0;

    FUN_0027e1f0();
    /* matching construct: permuter — the request store follows the state bytes (register allocation) */
    if (srd->state == 0 || srd->state == 3 || srd->state == 9) {
        srd->kind = 2;
        srd->state = 1;
        queued = 1;
        srd->request = request;
        srd->f24 = value24;
        srd->f32 = value32;
        srd->f40 = value40;
        srd->status = 0;
    }
    FUN_0027e268();
    return queued;
}

