/* 0x003f5660 - FUN_003f5660. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int sprintf(int *, int *, int);
int FUN_003f5410(int, int, int, int *, int);
extern int DAT_00518728[4];
void FUN_003f5660(int arg0, int arg1, int arg2, int arg3, int arg4) {
    int sp50[4];
    sprintf(sp50, &DAT_00518728[0], arg3);
    FUN_003f5410(arg0, arg1, arg2, sp50, arg4);
}
} /* extern "C" */
