int memmove();
int Memory_ReallocateBuffer();
struct S { char pad[4]; volatile unsigned cnt; unsigned f8; int f12; char *f16; };

void StringTable_InsertAt(struct S *arg0, int arg1, int arg2) {
    int temp_v1;
    char *temp_a1;
    int temp_s0;
    unsigned int temp_a1_2;
    unsigned int var_a0;

    temp_v1 = arg0->f12;
    if (arg0->cnt == temp_v1) {
        int nc = temp_v1 * 2;
        arg0->f16 = (char *)Memory_ReallocateBuffer(arg0->f16, nc * 4);
        arg0->f12 = nc;
    }
    temp_s0 = arg2 * 4;
    temp_a1 = arg0->f16 + temp_s0;
    memmove(temp_a1 + 4, temp_a1, (arg0->cnt - arg2) * 4);
    *(int *)(arg0->f16 + temp_s0) = arg1;
    arg0->cnt = arg0->cnt + 1;
    temp_a1_2 = arg0->f8;
    var_a0 = temp_a1_2 * 2;
    if (var_a0 <= arg0->cnt) {
        var_a0 = (temp_a1_2 != 0) ? var_a0 : 1;
        arg0->f8 = var_a0;
    }
}
