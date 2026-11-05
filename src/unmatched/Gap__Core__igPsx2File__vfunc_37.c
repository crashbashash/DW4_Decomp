/* 0x0032be80 — Gap__Core__igPsx2File__vfunc_37. Retyped m2c draft, verified byte-identical to retail by tools/verify.py (wave5 shard 8). */
int memcpy();
int strlen();
int FUN_0032b5b0();
struct S { char pad[44]; char *f44; char pad2[4]; int f52; int f56; int f60; };

int Gap__Core__igPsx2File__vfunc_37(struct S *arg0, char *arg1) {
    int temp_a1;
    int temp_v0;

    if (arg1 == 0) {
        return -1;
    }
    if (arg0->f60 != 0) {
        return -1;
    }
    temp_v0 = strlen(arg1);
    temp_a1 = arg0->f52 + temp_v0;
    if (temp_a1 >= arg0->f56) {
        FUN_0032b5b0(arg0, temp_a1);
    }
    memcpy(arg0->f44 + arg0->f52, arg1, temp_v0);
    arg0->f52 = arg0->f52 + temp_v0;
    return temp_v0;
}
