/* 0x0027db18 — FUN_0027db18 (80 bytes). Increments a use counter, running the one-time initialiser FUN_002736b8 when it is still zero. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_002736b8();
extern volatile int DAT_004ba478; /* read and discarded: the retail load survives, so it is volatile */
extern int DAT_004ba47c;          /* use count */

void FUN_0027db18(void) {
    DAT_004ba478;
    if (DAT_004ba47c == 0) {
        FUN_002736b8();
    }
    DAT_004ba47c++;
}
