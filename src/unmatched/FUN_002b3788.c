/* 0x002b3788 — FUN_002b3788 (112 bytes). One-time module initialisation: unless DAT_004bec20 is already positive, stores FUN_002b37f8's result in DAT_005856a0, runs the sub-initialisers FUN_002b3808, FUN_002b4080, FUN_002b4210 and FUN_002b2ee8, clears DAT_004bec24 and bumps DAT_004bec20. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002b37f8(void);
void FUN_002b3808(void);
void FUN_002b4080(void);
void FUN_002b4210(void);
void FUN_002b2ee8(void);

extern int DAT_004bec20;
extern int DAT_004bec24;
extern volatile int DAT_005856a0; /* matching construct: volatile — stored through a materialised address */

void FUN_002b3788(void) {
    int *initialised = &DAT_004bec20;

    if (*initialised > 0) {
        return;
    }
    DAT_005856a0 = FUN_002b37f8();
    FUN_002b3808();
    FUN_002b4080();
    FUN_002b4210();
    FUN_002b2ee8();
    DAT_004bec24 = 0;
    (*initialised)++;
}
