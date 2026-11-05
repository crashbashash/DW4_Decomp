extern "C" {
int FUN_00100610(void **);
int igObject_Destroy(int *);
void **FUN_00357b90(void **arg0, short arg1);
}

void **FUN_00357b90(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}
