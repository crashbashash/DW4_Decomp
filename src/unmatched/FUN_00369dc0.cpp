extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00369f80();
void FUN_00369dc0(int arg0);
}

void FUN_00369dc0(int arg0) {
    FUN_00369f80();
    igMetaObject_CreateInstance(*(int *)0x589D10, arg0);
}
