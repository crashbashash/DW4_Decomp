/* Looks up entry `index`: from the static table DAT_004be8d8 when handle is null, otherwise
 * through FUN_002adc40 (error 0xFF000113 when FUN_002a0dd8 refuses). */
int FUN_002a0bb8();
int FUN_002a0dd8(handle);
int FUN_002adc40();

extern int DAT_004be8d8[4];

int FUN_002adba0(int handle, int index, int *out) {
    if (handle == 0) {
        *out = DAT_004be8d8[index];
    } else {
        /* matching construct: manual — both paths fall through to one `return 0` */
        if (FUN_002a0dd8(handle) != 0) {
            return FUN_002a0bb8(0, 0xFF000113);
        }
        *out = FUN_002adc40(handle, index);
    }
    return 0;
}
