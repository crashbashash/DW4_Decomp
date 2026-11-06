extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00340e80();

void FUN_00340cc0(int arg0) {
    FUN_00340e80();
    igMetaObject_CreateInstance(*(int *)0x587BF8, arg0);
}
}
