/* 0x002936a8 — FUN_002936a8 (92 bytes). Walks the 32 handle slots at +532..+656 from last to first, releasing each live one through FUN_00293618 and clearing the slot. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_00293618(void *owner, int handle);

void FUN_002936a8(char *owner) {
    int *slot = (int *)(owner + 656); /* last of 32 slots */
    int i;

    for (i = 31; i >= 0; i--) {
        if (*slot != 0) {
            FUN_00293618(owner, *slot);
            *slot = 0;
        }
        slot--;
    }
}
