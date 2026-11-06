extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00345bc0();

void FUN_00345a00(int arg0) {
    FUN_00345bc0();
    igMetaObject_CreateInstance(*(int *)0x587F98, arg0);
}
}
