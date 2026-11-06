extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00336f10();

void FUN_00336bd0(int arg0) {
    FUN_00336f10();
    igMetaObject_CreateInstance(*(int *)0x587870, arg0);
}
}
