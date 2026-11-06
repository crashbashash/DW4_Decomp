extern "C" {
int sprintf(int *, int *, int);
int FUN_003f5410(int, int, int, int *, int);
extern int DAT_00518728[4];
void FUN_003f5660(int arg0, int arg1, int arg2, int arg3, int arg4) {
    int sp50[4];
    sprintf(sp50, &DAT_00518728[0], arg3);
    FUN_003f5410(arg0, arg1, arg2, sp50, arg4);
}
}
