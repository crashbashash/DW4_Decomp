extern "C" {
int igMetaObject_CreateInstance(int, int);
int FUN_00342f30();

void FUN_00342ca0(int arg0) {
    FUN_00342f30();
    igMetaObject_CreateInstance(*(int *)0x587D08, arg0);
}
}
