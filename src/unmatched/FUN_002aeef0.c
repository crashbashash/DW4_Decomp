/* Runs FUN_002aef78 on one handle, or with a null handle on every handle in DAT_004beadc,
 * returning the last non-zero result. */
int FUN_002aef78(int handle);

extern int DAT_004beadc[8];

int FUN_002aeef0(int handle) {
    int result;
    int status;
    int i;

    if (handle == 0) {
        result = 0;
        for (i = 0; i < 8; i++) {
            if (DAT_004beadc[i] != 0) {
                status = FUN_002aef78(DAT_004beadc[i]);
                if (status != 0) {
                    result = status;
                }
            }
        }
        return result;
    }
    return FUN_002aef78(handle);
}
