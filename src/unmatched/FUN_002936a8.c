/* Walks the 32 handle slots at +532..+656 from last to first, releasing each live one through
 * FUN_00293618 and clearing the slot. */
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
