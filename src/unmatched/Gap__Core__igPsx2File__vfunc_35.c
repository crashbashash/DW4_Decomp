typedef struct F { char pad[44]; char *f44; char pad2[4]; int f52; int f56; int f60; } F;
int FUN_0032b5b0();

int Gap__Core__igPsx2File__vfunc_35(F *arg0, unsigned char arg1) {
    int temp_a1;

    if (arg0->f60 != 0) {
        return -1;
    }
    temp_a1 = arg0->f52 + 1;
    if (temp_a1 >= arg0->f56) {
        FUN_0032b5b0(arg0, temp_a1);
    }
    arg0->f44[arg0->f52] = arg1;
    arg0->f52 = arg0->f52 + 1;
    return arg1;
}
