/* Unless mode DAT_004b1dc8 is 1 with no pending count in DAT_004b1dc0, opens channel id (0 or 1):
 * unless its slot in DAT_004b1e00 is already 1, sends command 16 with the id through FUN_00273820
 * and sets the slot. */
extern int DAT_004b1dc8;
extern int DAT_004b1dc0;
extern int DAT_004b1e00[2];
int FUN_00273820(int command, unsigned int *args, int count, int a3, int t0);

void FUN_0027a0e8(unsigned int id) {
    unsigned int args[4];

    if (DAT_004b1dc8 == 1 && DAT_004b1dc0 <= 0) {
        return;
    }
    if (id < 2 && DAT_004b1e00[id] != 1) {
        args[0] = id;
        FUN_00273820(16, args, 1, 0, 0);
        DAT_004b1e00[id] = 1;
    }
}

