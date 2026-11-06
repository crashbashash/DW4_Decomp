/* Checked getter (error 0xFF00011B): reports DAT_004f5060[rate index at +2336] through *rate, or
 * -1 when the index is 0 or the handle is rejected. */
int FUN_002a0bb8();
int FUN_002a0dd8();
extern int DAT_004f5060[];
struct Obj0920 {
    char pad[2336];
    int rateIndex;                        /* +2336 (0x920): index into DAT_004f5060 */
};
/* FUN_002a0dd8(handle) records the handle in a global and returns -1 when it is null or its word at +72 is clear (asm/FUN_002a0dd8.s). */
int FUN_002af580(struct Obj0920 *handle, int *rate) {
    int index;
    *rate = -1;
    if (FUN_002a0dd8(handle) != 0) {
        return FUN_002a0bb8(0, 0xFF00011B);
    }
    index = handle->rateIndex;
    if (index != 0) {
        *rate = DAT_004f5060[index];
    }
    return 0;
}
