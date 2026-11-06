/* Destroys a handle: reports error 0xFF000131 if FUN_002a0dd8 refuses, otherwise tears it down
 * (FUN_002abef0, FUN_0029fed0 on +120, FUN_0029d790, FUN_002abdb8) and clears it from
 * DAT_004beadc. */
int FUN_002a0dd8(int handle);
int FUN_002a0bb8(int obj, int code);
void FUN_002abef0(int handle);
void FUN_0029fed0(int block);
void FUN_0029d790(int handle);
int FUN_002abdb8(int handle);

extern int DAT_004beadc[8];

int FUN_002abd18(int handle) {
    int result;
    int i;

    if (FUN_002a0dd8(handle) != 0) {
        return FUN_002a0bb8(0, 0xFF000131);
    }
    FUN_002abef0(handle);
    FUN_0029fed0(handle + 120);
    FUN_0029d790(handle);
    result = FUN_002abdb8(handle);
    for (i = 0; i < 8; i++) {
        if (DAT_004beadc[i] == handle) {
            DAT_004beadc[i] = 0;
        }
    }
    return result;
}
