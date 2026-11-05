/* 0x002abb48 — FUN_002abb48 (116 bytes). Clears a 40-byte header and its counters, then resets the four 24-byte sub-records at +48..+120. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdSub24 {
    char pad0[24];
} SfdSub24;

typedef struct SfdTimer {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
    int f20;
    int f24;
    int f28;
    int f32;
    int f36;
    int f40;
    int f44;
    SfdSub24 sub[4];        /* +48 */
} SfdTimer;

extern void FUN_0028b530(void *dst, int value, int size);
extern void FUN_002abbc0(SfdSub24 *sub);

void FUN_002abb48(SfdTimer *timer) {
    FUN_0028b530(timer, 0, 40);
    timer->f0 = 0;
    timer->f4 = 0;
    timer->f8 = 0;
    timer->f12 = 0;
    timer->f16 = 0;
    timer->f24 = 0;
    timer->f28 = 0;
    timer->f32 = 0;
    timer->f36 = 0;
    timer->f40 = 0;
    timer->f44 = 0;
    FUN_002abbc0(&timer->sub[0]);
    FUN_002abbc0(&timer->sub[1]);
    FUN_002abbc0(&timer->sub[2]);
    FUN_002abbc0(&timer->sub[3]);
}
