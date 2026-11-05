int FUN_00118960();

typedef struct C { char pad[60]; int f60; int f64; char pad68[23]; unsigned char b91[6]; } C;

void Gap__Core__igPsx2Controller__vfunc_37(C *arg0, int arg1, float fparg0) {
    if ((arg1 >= 0) && (arg1 < 6)) {
        arg0->b91[arg1] = (unsigned char)(255.0f * fparg0);
        FUN_00118960(arg0->f64, arg0->f60, &arg0->b91[0]);
    }
}
