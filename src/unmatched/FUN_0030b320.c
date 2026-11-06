int memcpy();
int FUN_00300f50();
int igObject_AllocateStorage();
struct S { char pad[8]; char *f8; int f12; };

void FUN_0030b320(struct S *arg0, int arg1, int arg2) {
    char *temp_s0;

    temp_s0 = arg0->f8;
    if ((arg1 == 0) || (arg2 == 0)) {
        arg0->f8 = 0;
        arg0->f12 = 0;
    } else {
        arg0->f8 = (char *)igObject_AllocateStorage(arg0, arg2 + 1);
        memcpy(arg0->f8, arg1, arg2);
        arg0->f8[arg2] = 0;
        arg0->f12 = arg2;
    }
    if (temp_s0 != 0) {
        FUN_00300f50(arg0, temp_s0);
    }
}
