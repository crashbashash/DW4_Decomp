extern "C" int FUN_00100610(void *);
extern "C" int igObject_Destroy(void *);
struct RefHolderTarget { int vt; unsigned int rc; };

extern "C" struct RefHolderTarget **FUN_003bd940(struct RefHolderTarget **arg0, short arg1) {
    struct RefHolderTarget *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}
