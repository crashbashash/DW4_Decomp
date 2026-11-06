/* Under the FUN_002a0e70/FUN_002a0e88 guard, toggles the flag at +0x950+28 when FUN_002aafb8 (set)
 * or FUN_002ab138 (clear) fires and reports it through FUN_002aa3d0. */
void FUN_002a0e70(void *guard);
void FUN_002a0e88(void *guard);
int FUN_002aafb8(int obj);
int FUN_002ab138(int obj);
int FUN_002aa3d0(int obj, int on);

struct Block950 {
    char pad0[28];
    int active;     /* +28 */
    int activations; /* +32 */
};

int FUN_002aaf08(int obj) {
    char guard[16];
    struct Block950 *b = (struct Block950 *)(obj + 0x950);
    int result;

    FUN_002a0e70(guard);
    result = 0;
    if (b->active == 0) {
        if (FUN_002aafb8(obj) != 0) {
            b->active = 1;
            b->activations++;
            result = FUN_002aa3d0(obj, 1);
        }
    } else if (FUN_002ab138(obj) != 0) {
        b->active = 0;
        result = FUN_002aa3d0(obj, 0);
    }
    FUN_002a0e88(guard);
    return result;
}
