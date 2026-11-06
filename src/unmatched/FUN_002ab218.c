/* Returns 1 when slot 5 or 6 is set and its FUN_002b03d0 check (6 or 7) passes, or when
 * FUN_0029ea88 reports any of the eight channels; otherwise 0. */
int FUN_002adc40(int obj, int slot);
int FUN_002b03d0(int obj, int code);
int FUN_0029ea88(int obj, int channel);

int FUN_002ab218(int obj) {
    int result;
    unsigned int channel;

    if (FUN_002adc40(obj, 5) != 0 && FUN_002b03d0(obj, 6) != 0) {
        return 1;
    }
    if (FUN_002adc40(obj, 6) != 0 && FUN_002b03d0(obj, 7) != 0) {
        return 1;
    }
    for (channel = 0; channel < 8; channel++) {
        result = FUN_0029ea88(obj, channel);
        if (result != 0) {
            return 1;
        }
    }
    return result;
}
