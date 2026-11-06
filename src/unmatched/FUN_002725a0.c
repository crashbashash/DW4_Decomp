/* Shifts the current value of 0x004a92f4 into the previous-value slot 0x004a92f0 and stores the
 * new value. */
extern volatile int DAT_004a92f0;
extern volatile int DAT_004a92f4;

void FUN_002725a0(int value) {
    DAT_004a92f0 = DAT_004a92f4;
    DAT_004a92f4 = value;
}
