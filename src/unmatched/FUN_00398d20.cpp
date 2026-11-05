extern "C" {
int FUN_00100610(void **);
int igObject_Destroy(int *);
void **FUN_00398d20(void **arg0, short arg1);
}

void **FUN_00398d20(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}
