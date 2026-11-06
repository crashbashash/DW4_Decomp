/* Claims the owner word 0x00570bb8 when it is free: stores the new owner and returns 1, or returns
 * 0 when it is already taken. */
extern int DAT_00570bb8;

int FUN_0027ed10(int owner) {
    if (DAT_00570bb8 != 0) {
        return 0;
    }
    DAT_00570bb8 = owner;
    return 1;
}
